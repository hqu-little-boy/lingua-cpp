#include "lingua/model_loader.h"
#include <brotli/decode.h>
#include <simdjson.h>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <format>

namespace lingua {
    ModelLoader &ModelLoader::get_instance() {
        static ModelLoader instance;
        return instance;
    }

    std::shared_ptr<const NgramProbabilityModel> ModelLoader::load_probability_model(
        Language language,
        size_t ngram_length
    ) {
        if (ngram_length < 1 || ngram_length > 5) {
            throw std::invalid_argument("n-gram length must be between 1 and 5");
        }

        const std::string cache_key = generate_cache_key(language, ngram_length, "probability");

        // Try to get from cache first
        {
            std::shared_lock<std::shared_mutex> lock(cache_mutex_);
            auto it = probability_model_cache_.find(cache_key);
            if (it != probability_model_cache_.end()) {
                return it->second;
            }
        }

        // Load model if not in cache
        const std::string ngram_name = Ngram::get_ngram_name_by_length(ngram_length);
        const std::string file_name = ngram_name + "s.json.br";
        // const std::string file_path = "models/" + iso_code_639_1(language) + "/" + file_name;
        const std::string file_path = std::format("models/{}/models/{}", iso_code_639_1(language), file_name);

        const std::string json_content = load_and_decompress_model(file_path);
        auto model = parse_probability_model(json_content, language);

        // Store in cache
        {
            std::unique_lock<std::shared_mutex> lock(cache_mutex_);
            probability_model_cache_[cache_key] = model;
        }

        return model;
    }

    std::shared_ptr<const NgramCountModel> ModelLoader::load_count_model(
        Language language,
        size_t ngram_length,
        NgramModelType model_type
    ) {
        if (ngram_length < 1 || ngram_length > 5) {
            throw std::invalid_argument("n-gram length must be between 1 and 5");
        }

        const std::string model_type_str = to_string(model_type);
        const std::string cache_key = generate_cache_key(language, ngram_length, model_type_str);

        // Try to get from cache first
        {
            std::shared_lock<std::shared_mutex> lock(cache_mutex_);
            auto it = count_model_cache_.find(cache_key);
            if (it != count_model_cache_.end()) {
                return it->second;
            }
        }

        // Load model if not in cache
        const std::string ngram_name = Ngram::get_ngram_name_by_length(ngram_length);
        const std::string file_name = model_type_str + "_" + ngram_name + "s.json.br";
        // const std::string file_path = "models/" + iso_code_639_1(language) + "/" + file_name;
        const std::string file_path = std::format("models/{}/models/{}", iso_code_639_1(language), file_name);

        const std::string json_content = load_and_decompress_model(file_path);
        auto model = parse_count_model(json_content, language, model_type);

        // Store in cache
        {
            std::unique_lock<std::shared_mutex> lock(cache_mutex_);
            count_model_cache_[cache_key] = model;
        }

        return model;
    }

    void ModelLoader::clear_cache() {
        std::unique_lock<std::shared_mutex> lock(cache_mutex_);
        probability_model_cache_.clear();
        count_model_cache_.clear();
    }

    std::string ModelLoader::generate_cache_key(Language language, size_t ngram_length,
                                                const std::string &model_type) const {
        return to_string(language) + "_" + std::to_string(ngram_length) + "_" + model_type;
    }

    std::string ModelLoader::load_and_decompress_model(const std::string &file_path) const {
        // Read compressed file
        std::ifstream file(file_path, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open model file: " + file_path);
        }

        std::ostringstream buffer;
        buffer << file.rdbuf();
        std::string compressed_data = buffer.str();
        file.close();

        // Decompress using brotli
        size_t decoded_size = compressed_data.size() * 10; // Initial estimate
        std::string decompressed_data(decoded_size, 0);

        BrotliDecoderResult result = BrotliDecoderDecompress(
            compressed_data.size(),
            reinterpret_cast<const uint8_t *>(compressed_data.data()),
            &decoded_size,
            reinterpret_cast<uint8_t *>(&decompressed_data[0])
        );

        if (result != BROTLI_DECODER_RESULT_SUCCESS) {
            throw std::runtime_error("Failed to decompress model file: " + file_path);
        }

        decompressed_data.resize(decoded_size);
        return decompressed_data;
    }

    std::shared_ptr<const NgramProbabilityModel> ModelLoader::parse_probability_model(
        const std::string &json_content,
        Language language
    ) const {
        using namespace simdjson;

        dom::parser parser;
        dom::object root_object = parser.parse(json_content).get<dom::object>();

        auto model = std::make_shared<NgramProbabilityModel>(language);

        // Parse n-grams
        dom::object ngrams_object = root_object["ngrams"].get<dom::object>();
        for (auto field: ngrams_object) {
            std::string fraction_str(field.key);
            std::string_view ngrams_view = field.value.get<std::string_view>();

            // Parse fraction (e.g., "1/2")
            size_t slash_pos = fraction_str.find('/');
            if (slash_pos == std::string::npos) {
                continue;
            }

            uint32_t numerator = std::stoi(fraction_str.substr(0, slash_pos));
            uint32_t denominator = std::stoi(fraction_str.substr(slash_pos + 1));
            double probability = static_cast<double>(numerator) / static_cast<double>(denominator);

            // Split n-grams by space
            std::istringstream iss{std::string(ngrams_view)};
            std::string ngram;
            while (iss >> ngram) {
                model->set_probability(Ngram(ngram), probability);
            }
        }

        return model;
    }

    std::shared_ptr<const NgramCountModel> ModelLoader::parse_count_model(
        const std::string &json_content,
        Language language,
        NgramModelType model_type
    ) const {
        using namespace simdjson;

        dom::parser parser;
        dom::object root_object = parser.parse(json_content).get<dom::object>();

        auto model = std::make_shared<NgramCountModel>(language, model_type);

        // Parse n-grams
        dom::array ngrams_object = root_object["ngrams"].get<dom::array>();
        for (auto field: ngrams_object) {
            std::string_view ngrams_view = field.get<std::string_view>();

            // Split n-grams by space
            std::istringstream iss{std::string(ngrams_view)};
            std::string ngram;
            while (iss >> ngram) {
                model->add_ngram(Ngram(ngram));
            }
        }

        return model;
    }
} // namespace lingua
