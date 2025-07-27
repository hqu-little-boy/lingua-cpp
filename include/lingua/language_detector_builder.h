#ifndef LINGUA_LANGUAGE_DETECTOR_BUILDER_H_
#define LINGUA_LANGUAGE_DETECTOR_BUILDER_H_

#include "language.h"
#include "language_detector.h"

#include <unordered_set>
#include <vector>

namespace lingua {

/**
 * @brief This class configures and creates an instance of LanguageDetector.
 */
class LanguageDetectorBuilder {
public:
    /** 
     * @brief Creates and returns an instance of LanguageDetectorBuilder with all built-in languages.
     */
    static LanguageDetectorBuilder from_all_languages();

    /** 
     * @brief Creates and returns an instance of LanguageDetectorBuilder
     * with all built-in spoken languages.
     */
    static LanguageDetectorBuilder from_all_spoken_languages();

    /** 
     * @brief Creates and returns an instance of LanguageDetectorBuilder
     * with all built-in languages supporting the Arabic script.
     */
    static LanguageDetectorBuilder from_all_languages_with_arabic_script();

    /** 
     * @brief Creates and returns an instance of LanguageDetectorBuilder
     * with all built-in languages supporting the Cyrillic script.
     */
    static LanguageDetectorBuilder from_all_languages_with_cyrillic_script();

    /** 
     * @brief Creates and returns an instance of LanguageDetectorBuilder
     * with all built-in languages supporting the Devanagari script.
     */
    static LanguageDetectorBuilder from_all_languages_with_devanagari_script();

    /** 
     * @brief Creates and returns an instance of LanguageDetectorBuilder
     * with all built-in languages supporting the Latin script.
     */
    static LanguageDetectorBuilder from_all_languages_with_latin_script();

    /** 
     * @brief Creates and returns an instance of LanguageDetectorBuilder
     * with all built-in languages except those specified in languages.
     *
     * @param languages Languages to exclude
     * @throws InvalidConfigurationException if no language is specified
     */
    static LanguageDetectorBuilder from_all_languages_without(const std::vector<Language>& languages);

    /** 
     * @brief Creates and returns an instance of LanguageDetectorBuilder
     * with the specified languages.
     *
     * @param languages Languages to include
     * @throws InvalidConfigurationException if no language is specified
     */
    static LanguageDetectorBuilder from_languages(const std::vector<Language>& languages);

    /** 
     * @brief Creates and returns an instance of LanguageDetectorBuilder
     * with the languages specified by the respective ISO 639-1 codes.
     *
     * @param iso_codes ISO 639-1 codes of languages to include
     * @throws InvalidConfigurationException if no ISO code is specified
     */
    static LanguageDetectorBuilder from_iso_codes_639_1(const std::vector<std::string>& iso_codes);

    /** 
     * @brief Creates and returns an instance of LanguageDetectorBuilder
     * with the languages specified by the respective ISO 639-3 codes.
     *
     * @param iso_codes ISO 639-3 codes of languages to include
     * @throws InvalidConfigurationException if no ISO code is specified
     */
    static LanguageDetectorBuilder from_iso_codes_639_3(const std::vector<std::string>& iso_codes);

    /** 
     * @brief Sets the desired value for the minimum relative distance measure.
     *
     * @param distance Minimum relative distance (between 0.0 and 0.99)
     * @throws InvalidConfigurationException if distance is smaller than 0.0 or greater than 0.99
     */
    LanguageDetectorBuilder& with_minimum_relative_distance(double distance);

    /** 
     * @brief Configures LanguageDetectorBuilder to preload all language models when creating
     * the instance of LanguageDetector.
     */
    LanguageDetectorBuilder& with_preloaded_language_models();

    /** 
     * @brief Disables the high accuracy mode in order to save memory and increase performance.
     */
    LanguageDetectorBuilder& with_low_accuracy_mode();

    /** 
     * @brief Creates and returns the configured instance of LanguageDetector.
     */
    LanguageDetector build();

private:
    LanguageDetectorBuilder() = default;
    
    std::unordered_set<Language> languages_;
    double minimum_relative_distance_ = 0.0;
    bool is_every_language_model_preloaded_ = false;
    bool is_low_accuracy_mode_enabled_ = false;
};

} // namespace lingua

#endif // LINGUA_LANGUAGE_DETECTOR_BUILDER_H_