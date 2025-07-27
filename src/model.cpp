#include "lingua/model.h"
#include <stdexcept>

namespace lingua {

std::string to_string(NgramModelType model_type) {
    switch (model_type) {
        case NgramModelType::UNIQUE:
            return "unique";
        case NgramModelType::MOST_COMMON:
            return "most_common";
        default:
            throw std::invalid_argument("Unknown NgramModelType");
    }
}

// NgramProbabilityModel implementation

NgramProbabilityModel::NgramProbabilityModel(Language language) : language_(language) {}

Language NgramProbabilityModel::get_language() const {
    return language_;
}

double NgramProbabilityModel::get_probability(const Ngram& ngram) const {
    auto it = ngrams_.find(ngram.get_value());
    if (it != ngrams_.end()) {
        return it->second;
    }
    return 0.0;
}

void NgramProbabilityModel::set_probability(const Ngram& ngram, double probability) {
    ngrams_[ngram.get_value()] = probability;
}

bool NgramProbabilityModel::contains(const Ngram& ngram) const {
    return ngrams_.find(ngram.get_value()) != ngrams_.end();
}

size_t NgramProbabilityModel::size() const {
    return ngrams_.size();
}

// NgramCountModel implementation

NgramCountModel::NgramCountModel(Language language, NgramModelType model_type) 
    : language_(language), model_type_(model_type) {}

Language NgramCountModel::get_language() const {
    return language_;
}

NgramModelType NgramCountModel::get_model_type() const {
    return model_type_;
}

bool NgramCountModel::contains(const Ngram& ngram) const {
    return ngrams_.find(ngram.get_value()) != ngrams_.end();
}

void NgramCountModel::add_ngram(const Ngram& ngram) {
    ngrams_.insert(ngram.get_value());
}

bool NgramCountModel::remove_ngram(const Ngram& ngram) {
    auto it = ngrams_.find(ngram.get_value());
    if (it != ngrams_.end()) {
        ngrams_.erase(it);
        return true;
    }
    return false;
}

size_t NgramCountModel::size() const {
    return ngrams_.size();
}

} // namespace lingua