#include "lingua/lingua.h"
#include <iostream>
#include <vector>

using namespace lingua;

int main() {
    // Example 1: Basic language detection
    std::cout << "=== Example 1: Basic Language Detection ===\n";
    auto detector = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::FRENCH, Language::GERMAN})
        .build();
    
    auto detected_language = detector.detect_language_of("languages are awesome");
    if (detected_language) {
        std::cout << "Detected language: " << to_string(*detected_language) << "\n\n";
    } else {
        std::cout << "Language could not be reliably detected\n\n";
    }
    
    // Example 2: Batch language detection
    std::cout << "=== Example 2: Batch Language Detection ===\n";
    std::vector<std::string> texts = {
        "languages are awesome",
        "les langues sont géniales",
        "Sprachen sind toll"
    };
    
    auto detected_languages = detector.detect_languages_of(texts);
    for (size_t i = 0; i < texts.size(); ++i) {
        std::cout << "\"" << texts[i] << "\" -> ";
        if (detected_languages[i]) {
            std::cout << to_string(*detected_languages[i]) << "\n";
        } else {
            std::cout << "Undetermined\n";
        }
    }
    std::cout << "\n";
    
    // Example 3: Computing confidence values
    std::cout << "=== Example 3: Computing Confidence Values ===\n";
    auto confidence_values = detector.compute_language_confidence_values("languages are awesome");
    std::cout << "Confidence values for \"languages are awesome\":\n";
    for (const auto& [language, confidence] : confidence_values) {
        std::cout << "  " << to_string(language) << ": " << (confidence * 100) << "%\n";
    }
    std::cout << "\n";
    
    // Example 4: Computing confidence for a specific language
    std::cout << "=== Example 4: Computing Confidence for a Specific Language ===\n";
    double confidence = detector.compute_language_confidence("languages are awesome", Language::FRENCH);
    std::cout << "Confidence that \"languages are awesome\" is French: " << (confidence * 100) << "%\n\n";
    
    // Example 5: Batch computing confidence values
    std::cout << "=== Example 5: Batch Computing Confidence Values ===\n";
    auto batch_confidence_values = detector.compute_language_confidence_values_of(texts);
    for (size_t i = 0; i < texts.size(); ++i) {
        std::cout << "Confidence values for \"" << texts[i] << "\":\n";
        for (const auto& [language, confidence] : batch_confidence_values[i]) {
            std::cout << "  " << to_string(language) << ": " << (confidence * 100) << "%\n";
        }
        std::cout << "\n";
    }
    
    // Example 6: Batch computing confidence for a specific language
    std::cout << "=== Example 6: Batch Computing Confidence for a Specific Language ===\n";
    auto french_confidences = detector.compute_language_confidence_of(texts, Language::FRENCH);
    for (size_t i = 0; i < texts.size(); ++i) {
        std::cout << "Confidence that \"" << texts[i] << "\" is French: " << (french_confidences[i] * 100) << "%\n";
    }
    std::cout << "\n";
    
    return 0;
}