#ifndef LINGUA_MODEL_H
#define LINGUA_MODEL_H

#include "lingua/ngram.h"
#include "lingua/language.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace lingua {

/**
 * @brief Enum representing the type of n-gram model
 */
enum class NgramModelType {
    /**
     * @brief Model containing unique n-grams for a language
     */
    UNIQUE,
    
    /**
     * @brief Model containing most common n-grams for a language
     */
    MOST_COMMON
};

/**
 * @brief Converts NgramModelType to string representation
 * 
 * @param model_type The model type to convert
 * @return std::string The string representation
 */
std::string to_string(NgramModelType model_type);

/**
 * @brief Model for storing n-gram probabilities
 * 
 * This class represents a statistical language model based on n-gram probabilities.
 * It stores the probabilities of n-grams for a specific language.
 */
class NgramProbabilityModel {
public:
    /**
     * @brief Constructs an NgramProbabilityModel
     * 
     * @param language The language this model represents
     */
    explicit NgramProbabilityModel(Language language);
    
    /**
     * @brief Get the language this model represents
     * 
     * @return Language The language
     */
    Language get_language() const;
    
    /**
     * @brief Get the probability of an n-gram
     * 
     * @param ngram The n-gram to look up
     * @return double The probability, or 0.0 if not found
     */
    double get_probability(const Ngram& ngram) const;
    
    /**
     * @brief Add or update the probability of an n-gram
     * 
     * @param ngram The n-gram
     * @param probability The probability value
     */
    void set_probability(const Ngram& ngram, double probability);
    
    /**
     * @brief Check if the model contains a specific n-gram
     * 
     * @param ngram The n-gram to check
     * @return true if the n-gram exists in the model
     * @return false if the n-gram does not exist in the model
     */
    bool contains(const Ngram& ngram) const;
    
    /**
     * @brief Get the number of n-grams in the model
     * 
     * @return size_t The count of n-grams
     */
    size_t size() const;

private:
    Language language_;
    std::unordered_map<std::string, double> ngrams_;
};

/**
 * @brief Model for storing n-gram counts/sets
 * 
 * This class represents a language model based on sets of n-grams,
 * such as unique or most common n-grams for a language.
 */
class NgramCountModel {
public:
    /**
     * @brief Constructs an NgramCountModel
     * 
     * @param language The language this model represents
     * @param model_type The type of model (UNIQUE or MOST_COMMON)
     */
    NgramCountModel(Language language, NgramModelType model_type);
    
    /**
     * @brief Get the language this model represents
     * 
     * @return Language The language
     */
    Language get_language() const;
    
    /**
     * @brief Get the type of this model
     * 
     * @return NgramModelType The model type
     */
    NgramModelType get_model_type() const;
    
    /**
     * @brief Check if the model contains a specific n-gram
     * 
     * @param ngram The n-gram to check
     * @return true if the n-gram exists in the model
     * @return false if the n-gram does not exist in the model
     */
    bool contains(const Ngram& ngram) const;
    
    /**
     * @brief Add an n-gram to the model
     * 
     * @param ngram The n-gram to add
     */
    void add_ngram(const Ngram& ngram);
    
    /**
     * @brief Remove an n-gram from the model
     * 
     * @param ngram The n-gram to remove
     * @return true if the n-gram was present and removed
     * @return false if the n-gram was not present
     */
    bool remove_ngram(const Ngram& ngram);
    
    /**
     * @brief Get the number of n-grams in the model
     * 
     * @return size_t The count of n-grams
     */
    size_t size() const;

private:
    Language language_;
    NgramModelType model_type_;
    std::unordered_set<std::string> ngrams_;
};

} // namespace lingua

#endif // LINGUA_MODEL_H