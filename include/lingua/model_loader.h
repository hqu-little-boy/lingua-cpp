#ifndef LINGUA_MODEL_LOADER_H
#define LINGUA_MODEL_LOADER_H

#include "lingua/model.h"
#include "lingua/language.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <shared_mutex>

namespace lingua {

/**
 * @brief Thread-safe loader for language models with caching and brotli decompression.
 */
class ModelLoader {
public:
    /**
     * @brief Get the singleton instance of ModelLoader.
     * 
     * @return ModelLoader& Reference to the singleton instance
     */
    static ModelLoader& get_instance();

    /**
     * @brief Load an n-gram probability model for a language.
     * 
     * @param language The language for which to load the model
     * @param ngram_length The length of n-grams in the model (1-5)
     * @return std::shared_ptr<const NgramProbabilityModel> Shared pointer to the loaded model
     */
    std::shared_ptr<const NgramProbabilityModel> load_probability_model(
        Language language, 
        size_t ngram_length
    );

    /**
     * @brief Load an n-gram count model for a language.
     * 
     * @param language The language for which to load the model
     * @param ngram_length The length of n-grams in the model (1-5)
     * @param model_type The type of count model to load
     * @return std::shared_ptr<const NgramCountModel> Shared pointer to the loaded model
     */
    std::shared_ptr<const NgramCountModel> load_count_model(
        Language language, 
        size_t ngram_length, 
        NgramModelType model_type
    );

    /**
     * @brief Clear all cached models.
     */
    void clear_cache();

private:
    mutable std::shared_mutex cache_mutex_;
    std::unordered_map<std::string, std::shared_ptr<const NgramProbabilityModel>> probability_model_cache_;
    std::unordered_map<std::string, std::shared_ptr<const NgramCountModel>> count_model_cache_;

    ModelLoader() = default;
    ~ModelLoader() = default;

    // Delete copy constructor and assignment operator to enforce singleton
    ModelLoader(const ModelLoader&) = delete;
    ModelLoader& operator=(const ModelLoader&) = delete;

    /**
     * @brief Generate a cache key for a model.
     * 
     * @param language The language
     * @param ngram_length The n-gram length
     * @param model_type The model type (for count models)
     * @return std::string The cache key
     */
    std::string generate_cache_key(Language language, size_t ngram_length, const std::string& model_type) const;

    /**
     * @brief Load and decompress a model file.
     * 
     * @param file_path Path to the compressed model file
     * @return std::string Decompressed JSON content
     */
    std::string load_and_decompress_model(const std::string& file_path) const;

    /**
     * @brief Parse a probability model from JSON.
     * 
     * @param json_content The JSON content
     * @param language The language
     * @return std::shared_ptr<const NgramProbabilityModel> Shared pointer to the parsed model
     */
    std::shared_ptr<const NgramProbabilityModel> parse_probability_model(
        const std::string& json_content, 
        Language language
    ) const;

    /**
     * @brief Parse a count model from JSON.
     * 
     * @param json_content The JSON content
     * @param language The language
     * @param model_type The model type
     * @return std::shared_ptr<const NgramCountModel> Shared pointer to the parsed model
     */
    std::shared_ptr<const NgramCountModel> parse_count_model(
        const std::string& json_content, 
        Language language,
        NgramModelType model_type
    ) const;
};

} // namespace lingua

#endif // LINGUA_MODEL_LOADER_H