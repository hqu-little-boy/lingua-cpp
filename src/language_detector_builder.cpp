#include "lingua/language_detector_builder.h"
#include "lingua/exception.h"

#include <algorithm>
#include <stdexcept>

namespace lingua {

LanguageDetectorBuilder LanguageDetectorBuilder::from_all_languages() {
    LanguageDetectorBuilder builder;
    builder.languages_ = all_languages();
    return builder;
}

LanguageDetectorBuilder LanguageDetectorBuilder::from_all_spoken_languages() {
    LanguageDetectorBuilder builder;
    builder.languages_ = all_spoken_languages();
    return builder;
}

LanguageDetectorBuilder LanguageDetectorBuilder::from_all_languages_with_arabic_script() {
    LanguageDetectorBuilder builder;
    builder.languages_ = all_with_arabic_script();
    return builder;
}

LanguageDetectorBuilder LanguageDetectorBuilder::from_all_languages_with_cyrillic_script() {
    LanguageDetectorBuilder builder;
    builder.languages_ = all_with_cyrillic_script();
    return builder;
}

LanguageDetectorBuilder LanguageDetectorBuilder::from_all_languages_with_devanagari_script() {
    LanguageDetectorBuilder builder;
    builder.languages_ = all_with_devanagari_script();
    return builder;
}

LanguageDetectorBuilder LanguageDetectorBuilder::from_all_languages_with_latin_script() {
    LanguageDetectorBuilder builder;
    builder.languages_ = all_with_latin_script();
    return builder;
}

LanguageDetectorBuilder LanguageDetectorBuilder::from_all_languages_without(const std::vector<Language>& languages) {
    if (languages.empty()) {
        throw InvalidConfigurationException("LanguageDetector needs at least 1 language to choose from");
    }
    
    auto all_langs = all_languages();
    for (const auto& lang : languages) {
        all_langs.erase(lang);
    }
    
    if (all_langs.empty()) {
        throw InvalidConfigurationException("LanguageDetector needs at least 1 language to choose from");
    }
    
    LanguageDetectorBuilder builder;
    builder.languages_ = all_langs;
    return builder;
}

LanguageDetectorBuilder LanguageDetectorBuilder::from_languages(const std::vector<Language>& languages) {
    if (languages.empty()) {
        throw InvalidConfigurationException("LanguageDetector needs at least 1 language to choose from");
    }
    
    LanguageDetectorBuilder builder;
    builder.languages_ = std::unordered_set<Language>(languages.begin(), languages.end());
    return builder;
}

LanguageDetectorBuilder LanguageDetectorBuilder::from_iso_codes_639_1(const std::vector<std::string>& iso_codes) {
    if (iso_codes.empty()) {
        throw InvalidConfigurationException("LanguageDetector needs at least 1 language to choose from");
    }
    
    std::vector<Language> languages;
    for (const auto& code : iso_codes) {
        languages.push_back(from_iso_code_639_1(code));
    }
    
    return from_languages(languages);
}

LanguageDetectorBuilder LanguageDetectorBuilder::from_iso_codes_639_3(const std::vector<std::string>& iso_codes) {
    if (iso_codes.empty()) {
        throw InvalidConfigurationException("LanguageDetector needs at least 1 language to choose from");
    }
    
    std::vector<Language> languages;
    for (const auto& code : iso_codes) {
        languages.push_back(from_iso_code_639_3(code));
    }
    
    return from_languages(languages);
}

LanguageDetectorBuilder& LanguageDetectorBuilder::with_minimum_relative_distance(double distance) {
    if (distance < 0.0 || distance > 0.99) {
        throw InvalidConfigurationException("Minimum relative distance must lie in between 0.0 and 0.99");
    }
    minimum_relative_distance_ = distance;
    return *this;
}

LanguageDetectorBuilder& LanguageDetectorBuilder::with_preloaded_language_models() {
    is_every_language_model_preloaded_ = true;
    return *this;
}

LanguageDetectorBuilder& LanguageDetectorBuilder::with_low_accuracy_mode() {
    is_low_accuracy_mode_enabled_ = true;
    return *this;
}

LanguageDetector LanguageDetectorBuilder::build() {
    if (languages_.empty()) {
        throw InvalidConfigurationException("LanguageDetector needs at least 1 language to choose from");
    }
    
    return LanguageDetector(
        languages_,
        minimum_relative_distance_,
        is_every_language_model_preloaded_,
        is_low_accuracy_mode_enabled_
    );
}

} // namespace lingua