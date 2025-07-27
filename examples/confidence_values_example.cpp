#include "lingua/lingua.h"
#include <iostream>
#include <vector>

using namespace lingua;

int main() {
    // Create a language detector for English, French, and German
    auto detector = LanguageDetectorBuilder::from_languages({
        Language::CHINESE, Language::ENGLISH, Language::FRENCH, Language::GERMAN
    }).build();

    // Example 1: Compute language confidence values for a single text
    std::cout << "=== Example 1: Compute Language Confidence Values ===" << std::endl;
    auto confidence_values = detector.compute_language_confidence_values(
        "This is a sample text for language detection.");

    std::cout << "Confidence values:" << std::endl;
    for (const auto &[language, confidence]: confidence_values) {
        std::cout << "  " << to_string(language) << ": " << (confidence * 100.0) << "%" << std::endl;
    }
    std::cout << std::endl;

    // Example 2: Compute confidence for a specific language
    std::cout << "=== Example 2: Compute Confidence for a Specific Language ===" << std::endl;
    double french_confidence = detector.compute_language_confidence("Bonjour, comment allez-vous?", Language::FRENCH);
    std::cout << "Confidence that \"Bonjour, comment allez-vous?\" is French: " << (french_confidence * 100.0) << "%" <<
            std::endl;

    double german_confidence = detector.compute_language_confidence("Hallo, wie geht es Ihnen?", Language::GERMAN);
    std::cout << "Confidence that \"Hallo, wie geht es Ihnen?\" is German: " << (german_confidence * 100.0) << "%" <<
            std::endl;

    double english_confidence = detector.compute_language_confidence("Hello, how are you?", Language::ENGLISH);
    std::cout << "Confidence that \"Hello, how are you?\" is English: " << (english_confidence * 100.0) << "%" <<
            std::endl;
    std::cout << std::endl;

    // Example 3: Batch compute language confidence values
    std::cout << "=== Example 3: Batch Compute Language Confidence Values ===" << std::endl;
    std::vector<std::string> texts = {
        "This is English text.",
        "Ceci est du texte français.",
        "Das ist deutsche Text.",
        "互联网逆天新人设！瞒着父母假装上班，实际躲在衣柜吃喝拉撒？！"
    };

    auto batch_confidence_values = detector.compute_language_confidence_values_of(texts);

    for (size_t i = 0; i < texts.size(); ++i) {
        std::cout << "Confidence values for \"" << texts[i] << "\":" << std::endl;
        for (const auto &[language, confidence]: batch_confidence_values[i]) {
            std::cout << "  " << to_string(language) << ": " << (confidence * 100.0) << "%" << std::endl;
        }
        std::cout << std::endl;
    }

    // Example 4: Batch compute confidence for a specific language
    std::cout << "=== Example 4: Batch Compute Confidence for a Specific Language ===" << std::endl;
    auto french_confidences = detector.compute_language_confidence_of(texts, Language::FRENCH);

    for (size_t i = 0; i < texts.size(); ++i) {
        std::cout << "Confidence that \"" << texts[i] << "\" is French: " << (french_confidences[i] * 100.0) << "%" <<
                std::endl;
    }
    std::cout << std::endl;

    return 0;
}
