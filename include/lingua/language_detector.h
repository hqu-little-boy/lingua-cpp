#ifndef LINGUA_LANGUAGE_DETECTOR_H_
#define LINGUA_LANGUAGE_DETECTOR_H_

#include "language.h"
#include "detection_result.h"
#include "exception.h"

#include <optional>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

namespace lingua {

/**
 * @brief This class detects the language of given input text.
 *
 * A single instance of LanguageDetector can be used safely in multiple threads.
 * Multiple instances of LanguageDetector share thread-safe access to the language models,
 * so every language model is loaded into memory just once, no matter how many instances
 * of LanguageDetector have been created.
 */
class LanguageDetector {
public:
    /**
     * @brief Detects the language of given input text.
     * If the language cannot be reliably detected, std::nullopt is returned.
     *
     * @param text Input text to analyze
     * @return Detected language or std::nullopt if undetermined
     */
    std::optional<Language> detect_language_of(const std::string& text) const;

    /**
     * @brief Detects the languages of all given input texts.
     * If the language cannot be reliably detected for a text, std::nullopt is put into the result vector.
     *
     * @param texts Vector of input texts to analyze
     * @return Vector of detected languages or std::nullopt for each text
     */
    std::vector<std::optional<Language>> detect_languages_of(const std::vector<std::string>& texts) const;

    /**
     * @brief Attempts to detect multiple languages in mixed-language text.
     *
     * This feature is experimental and under continuous development.
     *
     * @param text Input text to analyze
     * @return Vector of DetectionResult objects describing identified language sections
     */
    std::vector<DetectionResult> detect_multiple_languages_of(const std::string& text) const;

    /**
     * @brief Computes confidence values for each language supported by this detector for the given
     * input text. These values denote how likely it is that the given text has been written
     * in any of the languages supported by this detector.
     *
     * @param text Input text to analyze
     * @return Vector of language-confidence pairs sorted by confidence in descending order
     */
    std::vector<std::pair<Language, double>> compute_language_confidence_values(const std::string& text) const;

    /**
     * @brief Computes confidence values for each language supported by this detector for all the given
     * input texts.
     *
     * @param texts Vector of input texts to analyze
     * @return Vector of vectors of language-confidence pairs for each text
     */
    std::vector<std::vector<std::pair<Language, double>>> compute_language_confidence_values_of(
        const std::vector<std::string>& texts) const;

    /**
     * @brief Computes the confidence value for the given language and input text.
     *
     * @param text Input text to analyze
     * @param language Language to compute confidence for
     * @return Confidence value between 0.0 and 1.0
     */
    double compute_language_confidence(const std::string& text, Language language) const;

    /**
     * @brief Computes the confidence values of all input texts for the given language.
     *
     * @param texts Vector of input texts to analyze
     * @param language Language to compute confidence for
     * @return Vector of confidence values for each text
     */
    std::vector<double> compute_language_confidence_of(
        const std::vector<std::string>& texts, Language language) const;

    /**
     * @brief Clears all language models loaded by this LanguageDetector instance
     * and frees allocated memory previously consumed by the models.
     */
    void unload_language_models();

private:
    friend class LanguageDetectorBuilder;
    
    LanguageDetector(
        std::unordered_set<Language> languages,
        double minimum_relative_distance,
        bool is_every_language_model_preloaded,
        bool is_low_accuracy_mode_enabled);

    std::unordered_set<Language> languages_;
    double minimum_relative_distance_;
    bool is_low_accuracy_mode_enabled_;
    bool is_built_from_one_language_;
    // Language model storage would be added here
};

} // namespace lingua

#endif // LINGUA_LANGUAGE_DETECTOR_H_