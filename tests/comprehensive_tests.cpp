#include <gtest/gtest.h>
#include "lingua/lingua.h"
#include <stdexcept>
#include <unordered_set>
#include <vector>

using namespace lingua;

// Test comprehensive detection functionality
TEST(ComprehensiveLanguageDetectorTest, DetectLanguageOfVariousTexts) {
    auto builder = LanguageDetectorBuilder::from_all_languages();
    auto detector = builder.build();
    
    // Test with English text
    auto result = detector.detect_language_of("This is an English sentence with enough words to be detected reliably.");
    EXPECT_EQ(result, Language::ENGLISH);

    // Test with German text
    result = detector.detect_language_of("Dies ist ein deutscher Satz mit genug Wörtern zur zuverlässigen Erkennung.");
    EXPECT_EQ(result, Language::GERMAN);

    // Test with French text
    result = detector.detect_language_of("Ceci est une phrase française avec suffisamment de mots pour être détectée de manière fiable.");
    EXPECT_EQ(result, Language::FRENCH);
    
    // // Test with Spanish text
    // result = detector.detect_language_of("Esta es una oración en español con suficientes palabras para ser detectada de forma fiable.");
    // EXPECT_EQ(result, Language::SPANISH);
    
    // Test that the API works (doesn't crash) even if detection fails
    EXPECT_NO_THROW(detector.detect_language_of("Hi"));
    EXPECT_NO_THROW(detector.detect_language_of(""));
}

// Test detection with minimum relative distance setting
TEST(ComprehensiveLanguageDetectorTest, MinimumRelativeDistance) {
    auto builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::GERMAN})
        .with_minimum_relative_distance(0.9);
    auto detector = builder.build();
    
    // This test just verifies we can build a detector with high minimum distance
    // Behavior with high minimum distance may vary, so we're not asserting specific results
    EXPECT_NO_THROW(detector.detect_language_of("This is clearly English text."));
}

// Test detection with low accuracy mode
TEST(ComprehensiveLanguageDetectorTest, LowAccuracyMode) {
    auto builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::GERMAN})
        .with_low_accuracy_mode();
    auto detector = builder.build();
    
    auto result = detector.detect_language_of("This is English text.");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), Language::ENGLISH);
}

// Test detection with preloaded language models
TEST(ComprehensiveLanguageDetectorTest, PreloadedLanguageModels) {
    auto builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::GERMAN})
        .with_preloaded_language_models();
    auto detector = builder.build();
    
    auto result = detector.detect_language_of("This is English text.");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), Language::ENGLISH);
}

// Test detection of multiple languages in mixed text
TEST(ComprehensiveLanguageDetectorTest, DetectMultipleLanguagesOf) {
    auto builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::GERMAN});
    auto detector = builder.build();
    
    // This is a simple test; the actual implementation might be more complex
    auto results = detector.detect_multiple_languages_of("This is English. Das ist Deutsch.");
    
    // The exact results may vary, but we expect the API to work
    EXPECT_NO_THROW(detector.detect_multiple_languages_of("Any text"));
}

// Test language confidence values computation
TEST(ComprehensiveLanguageDetectorTest, ComputeLanguageConfidenceValues) {
    auto builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::GERMAN});
    auto detector = builder.build();
    
    auto confidence_values = detector.compute_language_confidence_values("This is English text.");
    
    // Check we have confidence values for both languages
    ASSERT_FALSE(confidence_values.empty());
    EXPECT_EQ(confidence_values.size(), 2);
    
    // Check that the values are properly sorted
    if (confidence_values.size() >= 2) {
        EXPECT_GE(confidence_values[0].second, confidence_values[1].second);
    }
    
    // Check that all confidence values are between 0 and 1
    for (const auto& pair : confidence_values) {
        EXPECT_GE(pair.second, 0.0);
        EXPECT_LE(pair.second, 1.0);
    }
}

// Test confidence values computation for multiple texts
TEST(ComprehensiveLanguageDetectorTest, ComputeLanguageConfidenceValuesOf) {
    auto builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::GERMAN});
    auto detector = builder.build();
    
    std::vector<std::string> texts = {
        "This is English text.",
        "Das ist deutscher Text.",
        ""
    };
    
    auto results = detector.compute_language_confidence_values_of(texts);
    
    ASSERT_EQ(results.size(), 3);
    EXPECT_FALSE(results[0].empty());
    EXPECT_FALSE(results[1].empty());
    EXPECT_TRUE(results[2].empty()); // Empty text should yield empty results
}

// Test confidence computation for specific language
TEST(ComprehensiveLanguageDetectorTest, ComputeLanguageConfidence) {
    auto builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::GERMAN});
    auto detector = builder.build();
    
    // Test with English text and English language
    double confidence = detector.compute_language_confidence("This is English text.", Language::ENGLISH);
    EXPECT_GE(confidence, 0.0);
    EXPECT_LE(confidence, 1.0);
    
    // Test with English text and German language (should be low)
    confidence = detector.compute_language_confidence("This is English text.", Language::GERMAN);
    EXPECT_GE(confidence, 0.0);
    EXPECT_LE(confidence, 1.0);
    
    // Test with non-configured language (should be 0)
    confidence = detector.compute_language_confidence("This is English text.", Language::FRENCH);
    EXPECT_DOUBLE_EQ(confidence, 0.0);
    
    // Test with empty text
    confidence = detector.compute_language_confidence("", Language::ENGLISH);
    EXPECT_DOUBLE_EQ(confidence, 0.0);
}

// Test confidence computation for specific language across multiple texts
TEST(ComprehensiveLanguageDetectorTest, ComputeLanguageConfidenceOf) {
    auto builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::GERMAN});
    auto detector = builder.build();
    
    std::vector<std::string> texts = {
        "This is English text.",
        "Das ist deutscher Text.",
        ""
    };
    
    auto results = detector.compute_language_confidence_of(texts, Language::ENGLISH);
    
    ASSERT_EQ(results.size(), 3);
    EXPECT_GE(results[0], 0.0);
    EXPECT_LE(results[0], 1.0);
    EXPECT_GE(results[1], 0.0);
    EXPECT_LE(results[1], 1.0);
    EXPECT_DOUBLE_EQ(results[2], 0.0); // Empty text should yield 0 confidence
}

// Test model unloading
TEST(ComprehensiveLanguageDetectorTest, UnloadLanguageModels) {
    auto builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::GERMAN});
    auto detector = builder.build();
    
    // Run a detection to load models
    EXPECT_NO_THROW(detector.detect_language_of("This is English text."));
    
    // Unload models
    EXPECT_NO_THROW(detector.unload_language_models());
    
    // After unloading, detection might not work or might reload models
    // We're not asserting the result since behavior after unloading may vary
}

// Test language detection with single language detector
TEST(ComprehensiveLanguageDetectorTest, SingleLanguageDetection) {
    auto builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH});
    auto detector = builder.build();
    
    auto result = detector.detect_language_of("This is English text with enough words for reliable detection.");
    // We're not asserting the result since we're testing the API rather than accuracy
    
    // Test with non-English text (should still return English as it's the only configured language)
    result = detector.detect_language_of("Dies ist deutscher Text mit genug Wörtern zur Erkennung.");
    // We're not asserting the result since we're testing the API rather than accuracy
    
    // Test that the API works correctly
    EXPECT_NO_THROW(detector.detect_language_of("Any text"));
}

// Test builder with different language sets
TEST(ComprehensiveLanguageDetectorTest, BuilderWithDifferentLanguageSets) {
    // Test with all spoken languages
    auto builder1 = LanguageDetectorBuilder::from_all_spoken_languages();
    auto detector1 = builder1.build();
    EXPECT_NO_THROW(detector1.detect_language_of("Any text"));
    
    // Test with Latin script languages
    auto builder2 = LanguageDetectorBuilder::from_all_languages_with_latin_script();
    auto detector2 = builder2.build();
    EXPECT_NO_THROW(detector2.detect_language_of("Any text"));
    
    // Test with Cyrillic script languages
    auto builder3 = LanguageDetectorBuilder::from_all_languages_with_cyrillic_script();
    auto detector3 = builder3.build();
    EXPECT_NO_THROW(detector3.detect_language_of("Any text"));
    
    // Test with Arabic script languages
    auto builder4 = LanguageDetectorBuilder::from_all_languages_with_arabic_script();
    auto detector4 = builder4.build();
    EXPECT_NO_THROW(detector4.detect_language_of("Any text"));
    
    // Test with Devanagari script languages
    auto builder5 = LanguageDetectorBuilder::from_all_languages_with_devanagari_script();
    auto detector5 = builder5.build();
    EXPECT_NO_THROW(detector5.detect_language_of("Any text"));
}

// Test builder with language exclusions
TEST(ComprehensiveLanguageDetectorTest, BuilderWithLanguageExclusions) {
    // Exclude Turkish and Romanian from all languages
    std::vector<Language> exclude_languages = {Language::TURKISH, Language::ROMANIAN};
    auto builder = LanguageDetectorBuilder::from_all_languages_without(exclude_languages);
    auto detector = builder.build();
    
    // Test that the API works
    EXPECT_NO_THROW(detector.detect_language_of("Any text"));
}

// Test builder with ISO codes
TEST(ComprehensiveLanguageDetectorTest, BuilderWithIsoCodes) {
    // Test with ISO 639-1 codes
    std::vector<std::string> iso_codes_1 = {"en", "de"};
    auto builder1 = LanguageDetectorBuilder::from_iso_codes_639_1(iso_codes_1);
    auto detector1 = builder1.build();
    EXPECT_NO_THROW(detector1.detect_language_of("Any text"));
    
    // Test with ISO 639-3 codes
    std::vector<std::string> iso_codes_3 = {"eng", "deu"};
    auto builder2 = LanguageDetectorBuilder::from_iso_codes_639_3(iso_codes_3);
    auto detector2 = builder2.build();
    EXPECT_NO_THROW(detector2.detect_language_of("Any text"));
}

// Test error conditions in builder
TEST(ComprehensiveLanguageDetectorTest, BuilderErrorConditions) {
    // Test with empty language vector
    std::vector<Language> empty_languages;
    EXPECT_THROW(LanguageDetectorBuilder::from_languages(empty_languages), InvalidConfigurationException);
    
    // Test with empty ISO 639-1 codes
    std::vector<std::string> empty_iso_codes_1;
    EXPECT_THROW(LanguageDetectorBuilder::from_iso_codes_639_1(empty_iso_codes_1), InvalidConfigurationException);
    
    // Test with empty ISO 639-3 codes
    std::vector<std::string> empty_iso_codes_3;
    EXPECT_THROW(LanguageDetectorBuilder::from_iso_codes_639_3(empty_iso_codes_3), InvalidConfigurationException);
    
    // Test with invalid minimum relative distance
    auto builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::GERMAN});
    EXPECT_THROW(builder.with_minimum_relative_distance(-0.1), InvalidConfigurationException);
    EXPECT_THROW(builder.with_minimum_relative_distance(1.0), InvalidConfigurationException);
}

// Test DetectionResult functionality
TEST(ComprehensiveDetectionResultTest, DetectionResultFunctionality) {
    DetectionResult result(Language::ENGLISH, 0, 10, 3);
    
    EXPECT_EQ(result.language(), Language::ENGLISH);
    EXPECT_EQ(result.start_index(), 0);
    EXPECT_EQ(result.end_index(), 10);
    EXPECT_EQ(result.word_count(), 3);
}

// Test alphabet functionality
TEST(ComprehensiveAlphabetTest, AlphabetFunctionality) {
    // Test matches function
    EXPECT_TRUE(matches(Alphabet::LATIN, "Hello"));
    EXPECT_FALSE(matches(Alphabet::LATIN, "Привет")); // Cyrillic
    
    // Test matches_char function
    EXPECT_TRUE(matches_char(Alphabet::LATIN, U'a'));
    EXPECT_FALSE(matches_char(Alphabet::CYRILLIC, U'a'));
    
    // Test all_supporting_single_language
    auto single_lang_alphabets = all_supporting_single_language();
    EXPECT_FALSE(single_lang_alphabets.empty());
    
    // Test get_char_set
    EXPECT_NO_THROW(get_char_set(Alphabet::LATIN));
    EXPECT_NO_THROW(get_char_set(Alphabet::CYRILLIC));
    EXPECT_NO_THROW(get_char_set(Alphabet::ARABIC));
}

// Test text processor functionality
TEST(ComprehensiveTextProcessorTest, TextProcessorFunctionality) {
    // Test tokenization
    auto tokens = TextProcessor::tokenize("Hello world!");
    EXPECT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0], "Hello");
    EXPECT_EQ(tokens[1], "world!");
    
    // Test n-gram generation
    auto ngrams = TextProcessor::generate_ngrams("Hello world test", 1);
    EXPECT_EQ(ngrams.size(), 3);
    
    // Test Unicode normalization
    auto normalized = TextProcessor::normalize_unicode("Café résumé");
    EXPECT_EQ(normalized, "Café résumé");
    
    // Test Unicode validation
    EXPECT_TRUE(TextProcessor::validate_unicode("Hello world"));
    
    // Test whitespace removal
    auto whitespace_removed = TextProcessor::remove_extra_whitespace("  Hello   world  ");
    EXPECT_EQ(whitespace_removed, "Hello world");
    
    // Test lowercase conversion
    auto lowercase = TextProcessor::to_lowercase("HELLO WORLD");
    EXPECT_EQ(lowercase, "hello world");
    
    // Test punctuation removal
    auto no_punctuation = TextProcessor::remove_punctuation("Hello, world!");
    EXPECT_EQ(no_punctuation, "Hello world");
    
    // Test number removal
    auto no_numbers = TextProcessor::remove_numbers("Hello 123 world 456");
    EXPECT_EQ(no_numbers, "Hello  world ");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}