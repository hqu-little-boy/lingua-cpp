#include "lingua/lingua.h"
#include <iostream>

using namespace lingua;

int main() {
    // Example 1: Basic usage with minimum relative distance
    std::cout << "Example 1: Setting minimum relative distance\n";
    auto detector1 = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::FRENCH, Language::GERMAN})
        .with_minimum_relative_distance(0.2)  // Set minimum relative distance to 0.2
        .build();
    
    auto result1 = detector1.detect_language_of("languages are awesome");
    if (result1) {
        std::cout << "Detected language: " << to_string(*result1) << "\n\n";
    } else {
        std::cout << "Language could not be reliably detected\n\n";
    }
    
    // Example 2: Using preloaded language models
    std::cout << "Example 2: Using preloaded language models\n";
    auto detector2 = LanguageDetectorBuilder::from_all_languages()
        .with_preloaded_language_models()  // Preload all language models
        .build();
    
    auto result2 = detector2.detect_language_of("computer programming");
    if (result2) {
        std::cout << "Detected language: " << to_string(*result2) << "\n\n";
    } else {
        std::cout << "Language could not be reliably detected\n\n";
    }
    
    // Example 3: Using low accuracy mode
    std::cout << "Example 3: Using low accuracy mode\n";
    auto detector3 = LanguageDetectorBuilder::from_all_languages()
        .with_low_accuracy_mode()  // Enable low accuracy mode
        .build();
    
    auto result3 = detector3.detect_language_of("hello world");
    if (result3) {
        std::cout << "Detected language: " << to_string(*result3) << "\n\n";
    } else {
        std::cout << "Language could not be reliably detected\n\n";
    }
    
    // Example 4: Combining all configuration options
    std::cout << "Example 4: Combining all configuration options\n";
    auto detector4 = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::SPANISH, Language::ITALIAN})
        .with_minimum_relative_distance(0.1)
        .with_preloaded_language_models()
        .with_low_accuracy_mode()
        .build();
    
    auto result4 = detector4.detect_language_of("programming languages");
    if (result4) {
        std::cout << "Detected language: " << to_string(*result4) << "\n\n";
    } else {
        std::cout << "Language could not be reliably detected\n\n";
    }
    
    return 0;
}