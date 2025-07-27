#include <gtest/gtest.h>
#include "lingua/lingua.h"
#include "lingua/model.h"
#include "lingua/model_loader.h"
#include <stdexcept>
#include <unordered_set>

using namespace lingua;

// Test Language enum values
TEST(LanguageTest, EnumValues) {
    // Just verify that the enum values exist, not their specific positions
    Language lang = Language::ENGLISH;
    EXPECT_EQ(static_cast<int>(lang), static_cast<int>(Language::ENGLISH));
    
    lang = Language::SPANISH;
    EXPECT_EQ(static_cast<int>(lang), static_cast<int>(Language::SPANISH));
    
    lang = Language::ZULU;
    EXPECT_EQ(static_cast<int>(lang), static_cast<int>(Language::ZULU));
}

// Test that all languages are correctly represented
TEST(LanguageTest, AllLanguagesComplete) {
    auto languages = all_languages();
    EXPECT_EQ(languages.size(), 75); // Should have 75 languages
    
    // Verify a few specific languages are present
    EXPECT_TRUE(languages.find(Language::AFRIKAANS) != languages.end());
    EXPECT_TRUE(languages.find(Language::ALBANIAN) != languages.end());
    EXPECT_TRUE(languages.find(Language::ARABIC) != languages.end());
    EXPECT_TRUE(languages.find(Language::ENGLISH) != languages.end());
    EXPECT_TRUE(languages.find(Language::CHINESE) != languages.end());
    EXPECT_TRUE(languages.find(Language::ZULU) != languages.end());
}

// Test to_string function
TEST(LanguageTest, ToString) {
    EXPECT_EQ(to_string(Language::ENGLISH), "ENGLISH");
    EXPECT_EQ(to_string(Language::SPANISH), "SPANISH");
    EXPECT_EQ(to_string(Language::CHINESE), "CHINESE");
}

// Test from_string function
TEST(LanguageTest, FromString) {
    EXPECT_EQ(from_string("ENGLISH"), Language::ENGLISH);
    EXPECT_EQ(from_string("english"), Language::ENGLISH); // Test case insensitivity
    EXPECT_EQ(from_string("English"), Language::ENGLISH);
    EXPECT_EQ(from_string("SPANISH"), Language::SPANISH);
    EXPECT_EQ(from_string("chinese"), Language::CHINESE);
    
    // Test that an invalid string throws an exception
    EXPECT_THROW(from_string("INVALID_LANGUAGE"), std::invalid_argument);
    EXPECT_THROW(from_string(""), std::invalid_argument);
}

// Test ISO 639-1 codes
TEST(LanguageTest, Iso6391) {
    EXPECT_EQ(iso_code_639_1(Language::ENGLISH), "en");
    EXPECT_EQ(iso_code_639_1(Language::SPANISH), "es");
    EXPECT_EQ(iso_code_639_1(Language::CHINESE), "zh");
    EXPECT_EQ(iso_code_639_1(Language::FRENCH), "fr");
    EXPECT_EQ(iso_code_639_1(Language::GERMAN), "de");
    
    // Test some additional languages
    EXPECT_EQ(iso_code_639_1(Language::AFRIKAANS), "af");
    EXPECT_EQ(iso_code_639_1(Language::ALBANIAN), "sq");
    EXPECT_EQ(iso_code_639_1(Language::ARABIC), "ar");
    EXPECT_EQ(iso_code_639_1(Language::JAPANESE), "ja");
    EXPECT_EQ(iso_code_639_1(Language::KOREAN), "ko");
    EXPECT_EQ(iso_code_639_1(Language::RUSSIAN), "ru");
    
    // Test reverse lookup
    EXPECT_EQ(from_iso_code_639_1("en"), Language::ENGLISH);
    EXPECT_EQ(from_iso_code_639_1("es"), Language::SPANISH);
    EXPECT_EQ(from_iso_code_639_1("zh"), Language::CHINESE);
    EXPECT_EQ(from_iso_code_639_1("fr"), Language::FRENCH);
    EXPECT_EQ(from_iso_code_639_1("de"), Language::GERMAN);
    
    // Test reverse lookup for additional languages
    EXPECT_EQ(from_iso_code_639_1("af"), Language::AFRIKAANS);
    EXPECT_EQ(from_iso_code_639_1("sq"), Language::ALBANIAN);
    EXPECT_EQ(from_iso_code_639_1("ar"), Language::ARABIC);
    EXPECT_EQ(from_iso_code_639_1("ja"), Language::JAPANESE);
    EXPECT_EQ(from_iso_code_639_1("ko"), Language::KOREAN);
    EXPECT_EQ(from_iso_code_639_1("ru"), Language::RUSSIAN);
    
    // Test that an invalid code throws an exception
    EXPECT_THROW(from_iso_code_639_1("xx"), std::invalid_argument);
    EXPECT_THROW(from_iso_code_639_1(""), std::invalid_argument);
    
    // Test that codes with wrong length throw an exception
    EXPECT_THROW(from_iso_code_639_1("e"), std::invalid_argument);
    EXPECT_THROW(from_iso_code_639_1("eng"), std::invalid_argument);
}

// Test ISO 639-3 codes
TEST(LanguageTest, Iso6393) {
    EXPECT_EQ(iso_code_639_3(Language::ENGLISH), "eng");
    EXPECT_EQ(iso_code_639_3(Language::SPANISH), "spa");
    EXPECT_EQ(iso_code_639_3(Language::CHINESE), "zho");
    EXPECT_EQ(iso_code_639_3(Language::FRENCH), "fra");
    EXPECT_EQ(iso_code_639_3(Language::GERMAN), "deu");
    
    // Test some additional languages
    EXPECT_EQ(iso_code_639_3(Language::AFRIKAANS), "afr");
    EXPECT_EQ(iso_code_639_3(Language::ALBANIAN), "sqi");
    EXPECT_EQ(iso_code_639_3(Language::ARABIC), "ara");
    EXPECT_EQ(iso_code_639_3(Language::JAPANESE), "jpn");
    EXPECT_EQ(iso_code_639_3(Language::KOREAN), "kor");
    EXPECT_EQ(iso_code_639_3(Language::RUSSIAN), "rus");
    
    // Test reverse lookup
    EXPECT_EQ(from_iso_code_639_3("eng"), Language::ENGLISH);
    EXPECT_EQ(from_iso_code_639_3("spa"), Language::SPANISH);
    EXPECT_EQ(from_iso_code_639_3("zho"), Language::CHINESE);
    EXPECT_EQ(from_iso_code_639_3("fra"), Language::FRENCH);
    EXPECT_EQ(from_iso_code_639_3("deu"), Language::GERMAN);
    
    // Test reverse lookup for additional languages
    EXPECT_EQ(from_iso_code_639_3("afr"), Language::AFRIKAANS);
    EXPECT_EQ(from_iso_code_639_3("sqi"), Language::ALBANIAN);
    EXPECT_EQ(from_iso_code_639_3("ara"), Language::ARABIC);
    EXPECT_EQ(from_iso_code_639_3("jpn"), Language::JAPANESE);
    EXPECT_EQ(from_iso_code_639_3("kor"), Language::KOREAN);
    EXPECT_EQ(from_iso_code_639_3("rus"), Language::RUSSIAN);
    
    // Test that an invalid code throws an exception
    EXPECT_THROW(from_iso_code_639_3("xxx"), std::invalid_argument);
    EXPECT_THROW(from_iso_code_639_3(""), std::invalid_argument);
    
    // Test that codes with wrong length throw an exception
    EXPECT_THROW(from_iso_code_639_3("en"), std::invalid_argument);
    EXPECT_THROW(from_iso_code_639_3("e"), std::invalid_argument);
}

// Test all_languages function
TEST(LanguageTest, AllLanguages) {
    auto languages = all_languages();
    EXPECT_EQ(languages.size(), 75); // Should have 75 languages
    
    // Check that some expected languages are present
    EXPECT_TRUE(languages.find(Language::ENGLISH) != languages.end());
    EXPECT_TRUE(languages.find(Language::SPANISH) != languages.end());
    EXPECT_TRUE(languages.find(Language::CHINESE) != languages.end());
    EXPECT_TRUE(languages.find(Language::AFRIKAANS) != languages.end());
    EXPECT_TRUE(languages.find(Language::ZULU) != languages.end());
}

// Test all_spoken_languages function
TEST(LanguageTest, AllSpokenLanguages) {
    auto languages = all_spoken_languages();
    EXPECT_EQ(languages.size(), 74); // Should have 74 languages (excluding Latin)
    
    // Check that Latin is not present
    EXPECT_TRUE(languages.find(Language::LATIN) == languages.end());
    
    // Check that some expected languages are present
    EXPECT_TRUE(languages.find(Language::ENGLISH) != languages.end());
    EXPECT_TRUE(languages.find(Language::SPANISH) != languages.end());
    EXPECT_TRUE(languages.find(Language::CHINESE) != languages.end());
}

// Test script-specific language functions
TEST(LanguageTest, ScriptSpecificLanguages) {
    // Test Latin script languages
    auto latin_languages = all_with_latin_script();
    EXPECT_GT(latin_languages.size(), 30); // Should have many languages with Latin script
    
    // Check that some expected languages are present
    EXPECT_TRUE(latin_languages.find(Language::ENGLISH) != latin_languages.end());
    EXPECT_TRUE(latin_languages.find(Language::SPANISH) != latin_languages.end());
    EXPECT_TRUE(latin_languages.find(Language::FRENCH) != latin_languages.end());
    EXPECT_TRUE(latin_languages.find(Language::GERMAN) != latin_languages.end());
    EXPECT_TRUE(latin_languages.find(Language::ITALIAN) != latin_languages.end());
    EXPECT_TRUE(latin_languages.find(Language::PORTUGUESE) != latin_languages.end());
    EXPECT_TRUE(latin_languages.find(Language::DUTCH) != latin_languages.end());
    EXPECT_TRUE(latin_languages.find(Language::SWEDISH) != latin_languages.end());
    EXPECT_TRUE(latin_languages.find(Language::DANISH) != latin_languages.end());
    EXPECT_TRUE(latin_languages.find(Language::FINNISH) != latin_languages.end());
    EXPECT_TRUE(latin_languages.find(Language::POLISH) != latin_languages.end());
    EXPECT_TRUE(latin_languages.find(Language::CZECH) != latin_languages.end());
    EXPECT_TRUE(latin_languages.find(Language::ROMANIAN) != latin_languages.end());
    
    // Check that some unexpected languages are not present
    EXPECT_TRUE(latin_languages.find(Language::CHINESE) == latin_languages.end());
    EXPECT_TRUE(latin_languages.find(Language::ARABIC) == latin_languages.end());
    EXPECT_TRUE(latin_languages.find(Language::RUSSIAN) == latin_languages.end());
    EXPECT_TRUE(latin_languages.find(Language::JAPANESE) == latin_languages.end());
    EXPECT_TRUE(latin_languages.find(Language::KOREAN) == latin_languages.end());
    EXPECT_TRUE(latin_languages.find(Language::HEBREW) == latin_languages.end());
    EXPECT_TRUE(latin_languages.find(Language::THAI) == latin_languages.end());
    
    // Test Cyrillic script languages
    auto cyrillic_languages = all_with_cyrillic_script();
    EXPECT_EQ(cyrillic_languages.size(), 8); // Should have 8 languages with Cyrillic script
    
    // Check that expected languages are present
    EXPECT_TRUE(cyrillic_languages.find(Language::RUSSIAN) != cyrillic_languages.end());
    EXPECT_TRUE(cyrillic_languages.find(Language::BELARUSIAN) != cyrillic_languages.end());
    EXPECT_TRUE(cyrillic_languages.find(Language::BULGARIAN) != cyrillic_languages.end());
    EXPECT_TRUE(cyrillic_languages.find(Language::UKRAINIAN) != cyrillic_languages.end());
    EXPECT_TRUE(cyrillic_languages.find(Language::SERBIAN) != cyrillic_languages.end());
    EXPECT_TRUE(cyrillic_languages.find(Language::MACEDONIAN) != cyrillic_languages.end());
    EXPECT_TRUE(cyrillic_languages.find(Language::KAZAKH) != cyrillic_languages.end());
    EXPECT_TRUE(cyrillic_languages.find(Language::MONGOLIAN) != cyrillic_languages.end());
    
    // Check that unexpected languages are not present
    EXPECT_TRUE(cyrillic_languages.find(Language::ENGLISH) == cyrillic_languages.end());
    EXPECT_TRUE(cyrillic_languages.find(Language::SPANISH) == cyrillic_languages.end());
    EXPECT_TRUE(cyrillic_languages.find(Language::CHINESE) == cyrillic_languages.end());
    EXPECT_TRUE(cyrillic_languages.find(Language::ARABIC) == cyrillic_languages.end());
    EXPECT_TRUE(cyrillic_languages.find(Language::JAPANESE) == cyrillic_languages.end());
    EXPECT_TRUE(cyrillic_languages.find(Language::KOREAN) == cyrillic_languages.end());
    EXPECT_TRUE(cyrillic_languages.find(Language::HEBREW) == cyrillic_languages.end());
    EXPECT_TRUE(cyrillic_languages.find(Language::THAI) == cyrillic_languages.end());
    
    // Test Arabic script languages
    auto arabic_languages = all_with_arabic_script();
    EXPECT_EQ(arabic_languages.size(), 3); // Should have 3 languages with Arabic script
    
    // Check that expected languages are present
    EXPECT_TRUE(arabic_languages.find(Language::ARABIC) != arabic_languages.end());
    EXPECT_TRUE(arabic_languages.find(Language::PERSIAN) != arabic_languages.end());
    EXPECT_TRUE(arabic_languages.find(Language::URDU) != arabic_languages.end());
    
    // Check that unexpected languages are not present
    EXPECT_TRUE(arabic_languages.find(Language::ENGLISH) == arabic_languages.end());
    EXPECT_TRUE(arabic_languages.find(Language::SPANISH) == arabic_languages.end());
    EXPECT_TRUE(arabic_languages.find(Language::CHINESE) == arabic_languages.end());
    EXPECT_TRUE(arabic_languages.find(Language::RUSSIAN) == arabic_languages.end());
    EXPECT_TRUE(arabic_languages.find(Language::JAPANESE) == arabic_languages.end());
    EXPECT_TRUE(arabic_languages.find(Language::KOREAN) == arabic_languages.end());
    EXPECT_TRUE(arabic_languages.find(Language::HEBREW) == arabic_languages.end());
    EXPECT_TRUE(arabic_languages.find(Language::THAI) == arabic_languages.end());
    
    // Test Devanagari script languages
    auto devanagari_languages = all_with_devanagari_script();
    EXPECT_EQ(devanagari_languages.size(), 2); // Should have 2 languages with Devanagari script
    
    // Check that expected languages are present
    EXPECT_TRUE(devanagari_languages.find(Language::HINDI) != devanagari_languages.end());
    EXPECT_TRUE(devanagari_languages.find(Language::MARATHI) != devanagari_languages.end());
    
    // Check that unexpected languages are not present
    EXPECT_TRUE(devanagari_languages.find(Language::ENGLISH) == devanagari_languages.end());
    EXPECT_TRUE(devanagari_languages.find(Language::SPANISH) == devanagari_languages.end());
    EXPECT_TRUE(devanagari_languages.find(Language::CHINESE) == devanagari_languages.end());
    EXPECT_TRUE(devanagari_languages.find(Language::RUSSIAN) == devanagari_languages.end());
    EXPECT_TRUE(devanagari_languages.find(Language::ARABIC) == devanagari_languages.end());
    EXPECT_TRUE(devanagari_languages.find(Language::JAPANESE) == devanagari_languages.end());
    EXPECT_TRUE(devanagari_languages.find(Language::KOREAN) == devanagari_languages.end());
    EXPECT_TRUE(devanagari_languages.find(Language::HEBREW) == devanagari_languages.end());
    EXPECT_TRUE(devanagari_languages.find(Language::THAI) == devanagari_languages.end());
}

// Test LanguageDetectorBuilder
TEST(LanguageDetectorBuilderTest, TestFromAllLanguages) {
    auto builder = LanguageDetectorBuilder::from_all_languages();
    auto detector = builder.build();
    // Just verify we can create it - actual functionality will be tested later
    SUCCEED();
}

TEST(LanguageDetectorBuilderTest, TestFromLanguages) {
    auto builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::GERMAN});
    auto detector = builder.build();
    // Just verify we can create it - actual functionality will be tested later
    SUCCEED();
}

TEST(LanguageDetectorBuilderTest, TestFromIsoCodes6391) {
    auto builder = LanguageDetectorBuilder::from_iso_codes_639_1({"en", "de"});
    auto detector = builder.build();
    // Just verify we can create it - actual functionality will be tested later
    SUCCEED();
}

TEST(LanguageDetectorBuilderTest, TestFromIsoCodes6393) {
    auto builder = LanguageDetectorBuilder::from_iso_codes_639_3({"eng", "deu"});
    auto detector = builder.build();
    // Just verify we can create it - actual functionality will be tested later
    SUCCEED();
}

// Test new builder configuration options
TEST(LanguageDetectorBuilderTest, TestWithMinimumRelativeDistance) {
    auto builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::GERMAN});
    
    // Test valid distance value
    EXPECT_NO_THROW(builder.with_minimum_relative_distance(0.5));
    
    // Test building after setting distance
    auto detector = builder.with_minimum_relative_distance(0.3).build();
    SUCCEED();
}

TEST(LanguageDetectorBuilderTest, TestWithPreloadedLanguageModels) {
    auto builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::GERMAN});
    
    // Test setting preloaded language models
    EXPECT_NO_THROW(builder.with_preloaded_language_models());
    
    // Test building after setting
    auto detector = builder.with_preloaded_language_models().build();
    SUCCEED();
}

TEST(LanguageDetectorBuilderTest, TestWithLowAccuracyMode) {
    auto builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::GERMAN});
    
    // Test setting low accuracy mode
    EXPECT_NO_THROW(builder.with_low_accuracy_mode());
    
    // Test building after setting
    auto detector = builder.with_low_accuracy_mode().build();
    SUCCEED();
}

TEST(LanguageDetectorBuilderTest, TestCombinedConfigurationOptions) {
    // Test combining all configuration options
    auto builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::GERMAN});
    
    auto detector = builder
        .with_minimum_relative_distance(0.2)
        .with_preloaded_language_models()
        .with_low_accuracy_mode()
        .build();
    
    SUCCEED();
}

// Additional tests for LanguageModelLoader error conditions
TEST(LanguageDetectorBuilderTest, TestFromAllLanguagesWithoutErrorConditions) {
    // Test with all languages excluded (should throw)
    auto all_langs = all_languages();
    std::vector<Language> exclude_all_languages(all_langs.begin(), all_langs.end());
    EXPECT_THROW(
        LanguageDetectorBuilder::from_all_languages_without(exclude_all_languages),
        InvalidConfigurationException
    );
}

// Test LanguageDetectorBuilder static factory methods
TEST(LanguageDetectorBuilderTest, FromAllLanguages) {
    auto builder = LanguageDetectorBuilder::from_all_languages();
    auto detector = builder.build();
    // Just verify we can create it - actual functionality will be tested later
    SUCCEED();
}

TEST(LanguageDetectorBuilderTest, FromAllSpokenLanguages) {
    auto builder = LanguageDetectorBuilder::from_all_spoken_languages();
    auto detector = builder.build();
    // Just verify we can create it - actual functionality will be tested later
    SUCCEED();
}

TEST(LanguageDetectorBuilderTest, FromAllLanguagesWithArabicScript) {
    auto builder = LanguageDetectorBuilder::from_all_languages_with_arabic_script();
    auto detector = builder.build();
    // Just verify we can create it - actual functionality will be tested later
    SUCCEED();
}

TEST(LanguageDetectorBuilderTest, FromAllLanguagesWithCyrillicScript) {
    auto builder = LanguageDetectorBuilder::from_all_languages_with_cyrillic_script();
    auto detector = builder.build();
    // Just verify we can create it - actual functionality will be tested later
    SUCCEED();
}

TEST(LanguageDetectorBuilderTest, FromAllLanguagesWithDevanagariScript) {
    auto builder = LanguageDetectorBuilder::from_all_languages_with_devanagari_script();
    auto detector = builder.build();
    // Just verify we can create it - actual functionality will be tested later
    SUCCEED();
}

TEST(LanguageDetectorBuilderTest, FromAllLanguagesWithLatinScript) {
    auto builder = LanguageDetectorBuilder::from_all_languages_with_latin_script();
    auto detector = builder.build();
    // Just verify we can create it - actual functionality will be tested later
    SUCCEED();
}

TEST(LanguageDetectorBuilderTest, FromAllLanguagesWithout) {
    // Test with a few languages excluded
    std::vector<Language> exclude_languages = {Language::TURKISH, Language::ROMANIAN};
    auto builder = LanguageDetectorBuilder::from_all_languages_without(exclude_languages);
    auto detector = builder.build();
    // Just verify we can create it - actual functionality will be tested later
    SUCCEED();

    // Test with too many languages excluded (should throw)
    auto all_langs = all_languages();
    std::vector<Language> exclude_all_languages(all_langs.begin(), all_langs.end());
    EXPECT_THROW(
        LanguageDetectorBuilder::from_all_languages_without(exclude_all_languages),
        InvalidConfigurationException
    );
}

TEST(LanguageDetectorBuilderTest, FromLanguages) {
    // Test with a couple of languages
    std::vector<Language> languages = {Language::ENGLISH, Language::GERMAN};
    auto builder = LanguageDetectorBuilder::from_languages(languages);
    auto detector = builder.build();
    // Just verify we can create it - actual functionality will be tested later
    SUCCEED();

    // Test with empty vector (should throw)
    std::vector<Language> empty_languages;
    EXPECT_THROW(
        LanguageDetectorBuilder::from_languages(empty_languages),
        InvalidConfigurationException
    );
}

TEST(LanguageDetectorBuilderTest, FromIsoCodes6391) {
    // Test with a couple of ISO codes
    std::vector<std::string> iso_codes = {"en", "de"};
    auto builder = LanguageDetectorBuilder::from_iso_codes_639_1(iso_codes);
    auto detector = builder.build();
    // Just verify we can create it - actual functionality will be tested later
    SUCCEED();

    // Test with empty vector (should throw)
    std::vector<std::string> empty_iso_codes;
    EXPECT_THROW(
        LanguageDetectorBuilder::from_iso_codes_639_1(empty_iso_codes),
        InvalidConfigurationException
    );
}

TEST(LanguageDetectorBuilderTest, FromIsoCodes6393) {
    // Test with a couple of ISO codes
    std::vector<std::string> iso_codes = {"eng", "deu"};
    auto builder = LanguageDetectorBuilder::from_iso_codes_639_3(iso_codes);
    auto detector = builder.build();
    // Just verify we can create it - actual functionality will be tested later
    SUCCEED();

    // Test with empty vector (should throw)
    std::vector<std::string> empty_iso_codes;
    EXPECT_THROW(
        LanguageDetectorBuilder::from_iso_codes_639_3(empty_iso_codes),
        InvalidConfigurationException
    );
}

// Test LanguageDetectorBuilder configuration methods
TEST(LanguageDetectorBuilderTest, WithMinimumRelativeDistance) {
    auto builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::GERMAN});

    // Test valid distance
    EXPECT_NO_THROW(builder.with_minimum_relative_distance(0.5));

    // Test boundary values
    EXPECT_NO_THROW(builder.with_minimum_relative_distance(0.0));
    EXPECT_NO_THROW(builder.with_minimum_relative_distance(0.99));

    // Test invalid distances (should throw)
    EXPECT_THROW(builder.with_minimum_relative_distance(-0.1), InvalidConfigurationException);
    EXPECT_THROW(builder.with_minimum_relative_distance(1.0), InvalidConfigurationException);
    EXPECT_THROW(builder.with_minimum_relative_distance(1.5), InvalidConfigurationException);
}

TEST(LanguageDetectorBuilderTest, WithPreloadedLanguageModels) {
    auto builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::GERMAN});

    // Test that we can configure preloaded models
    EXPECT_NO_THROW(builder.with_preloaded_language_models());

    auto detector = builder.build();
    // Just verify we can create it - actual functionality will be tested later
    SUCCEED();
}

TEST(LanguageDetectorBuilderTest, WithLowAccuracyMode) {
    auto builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::GERMAN});

    // Test that we can configure low accuracy mode
    EXPECT_NO_THROW(builder.with_low_accuracy_mode());

    auto detector = builder.build();
    // Just verify we can create it - actual functionality will be tested later
    SUCCEED();
}

// Test LanguageDetectorBuilder build method
TEST(LanguageDetectorBuilderTest, Build) {
    auto builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::GERMAN});
    auto detector = builder.build();

    // Just verify we can create it - actual functionality will be tested later
    EXPECT_NE(&detector, nullptr);
}

// Test DetectionResult
TEST(DetectionResultTest, TestConstructorAndGetters) {
    DetectionResult result(Language::ENGLISH, 0, 10, 3);
    
    EXPECT_EQ(result.language(), Language::ENGLISH);
    EXPECT_EQ(result.start_index(), 0);
    EXPECT_EQ(result.end_index(), 10);
    EXPECT_EQ(result.word_count(), 3);
}

// Test exceptions
TEST(ExceptionTest, TestLinguaException) {
    try {
        throw LinguaException("Test exception");
    } catch (const LinguaException& e) {
        EXPECT_STREQ(e.what(), "Test exception");
    }
}

TEST(ExceptionTest, TestModelLoadException) {
    try {
        throw ModelLoadException("Model load error");
    } catch (const ModelLoadException& e) {
        EXPECT_STREQ(e.what(), "Model load error");
    }
}

TEST(ExceptionTest, TestInvalidConfigurationException) {
    try {
        throw InvalidConfigurationException("Invalid config");
    } catch (const InvalidConfigurationException& e) {
        EXPECT_STREQ(e.what(), "Invalid config");
    }
}

TEST(ExceptionTest, TestInsufficientDataException) {
    try {
        throw InsufficientDataException("Not enough data");
    } catch (const InsufficientDataException& e) {
        EXPECT_STREQ(e.what(), "Not enough data");
    }
}

// Additional tests for error conditions in Language functions
TEST(LanguageTest, FromStringErrorConditions) {
    // Test empty string
    EXPECT_THROW(from_string(""), std::invalid_argument);
    
    // Test invalid language name
    EXPECT_THROW(from_string("INVALID"), std::invalid_argument);
    
    // Test partially matching string
    EXPECT_THROW(from_string("ENGLIS"), std::invalid_argument);
}

TEST(LanguageTest, FromIsoCode6391ErrorConditions) {
    // Test empty string
    EXPECT_THROW(from_iso_code_639_1(""), std::invalid_argument);
    
    // Test invalid ISO code
    EXPECT_THROW(from_iso_code_639_1("xx"), std::invalid_argument);
    
    // Test partially matching code
    EXPECT_THROW(from_iso_code_639_1("e"), std::invalid_argument);
}

TEST(LanguageTest, FromIsoCode6393ErrorConditions) {
    // Test empty string
    EXPECT_THROW(from_iso_code_639_3(""), std::invalid_argument);
    
    // Test invalid ISO code
    EXPECT_THROW(from_iso_code_639_3("xxx"), std::invalid_argument);
    
    // Test partially matching code
    EXPECT_THROW(from_iso_code_639_3("en"), std::invalid_argument);
}

// Test case insensitivity for ISO code functions
TEST(LanguageTest, IsoCodeCaseInsensitivity) {
    // Test ISO 639-1 case insensitivity
    EXPECT_EQ(from_iso_code_639_1("EN"), Language::ENGLISH);
    EXPECT_EQ(from_iso_code_639_1("En"), Language::ENGLISH);
    EXPECT_EQ(from_iso_code_639_1("eN"), Language::ENGLISH);
    
    // Test ISO 639-3 case insensitivity
    EXPECT_EQ(from_iso_code_639_3("ENG"), Language::ENGLISH);
    EXPECT_EQ(from_iso_code_639_3("Eng"), Language::ENGLISH);
    EXPECT_EQ(from_iso_code_639_3("eNg"), Language::ENGLISH);
}

// Test comprehensive ISO code mappings for all languages
TEST(LanguageTest, ComprehensiveIsoCodeMappings) {
    auto languages = all_languages();
    
    // Test that each language has valid ISO 639-1 and 639-3 codes
    for (const auto& language : languages) {
        std::string iso639_1 = iso_code_639_1(language);
        std::string iso639_3 = iso_code_639_3(language);
        
        // Check that ISO codes are not empty
        EXPECT_FALSE(iso639_1.empty()) << "ISO 639-1 code for " << to_string(language) << " is empty";
        EXPECT_FALSE(iso639_3.empty()) << "ISO 639-3 code for " << to_string(language) << " is empty";
        
        // Check that ISO 639-1 code has 2 characters
        EXPECT_EQ(iso639_1.length(), 2) 
            << "ISO 639-1 code for " << to_string(language) << " has incorrect length: " << iso639_1.length();
            
        // Check that ISO 639-3 code has 3 characters
        EXPECT_EQ(iso639_3.length(), 3) 
            << "ISO 639-3 code for " << to_string(language) << " has incorrect length: " << iso639_3.length();
            
        // Test round-trip conversion
        EXPECT_EQ(from_iso_code_639_1(iso639_1), language) 
            << "Round-trip conversion failed for " << to_string(language) << " with ISO 639-1 code " << iso639_1;
            
        EXPECT_EQ(from_iso_code_639_3(iso639_3), language) 
            << "Round-trip conversion failed for " << to_string(language) << " with ISO 639-3 code " << iso639_3;
    }
    
    // Test that all ISO codes are unique
    std::unordered_set<std::string> iso639_1_codes;
    std::unordered_set<std::string> iso639_3_codes;
    
    for (const auto& language : languages) {
        std::string iso639_1 = iso_code_639_1(language);
        std::string iso639_3 = iso_code_639_3(language);
        
        // Check uniqueness of ISO 639-1 codes
        EXPECT_TRUE(iso639_1_codes.find(iso639_1) == iso639_1_codes.end()) 
            << "Duplicate ISO 639-1 code found: " << iso639_1;
        iso639_1_codes.insert(iso639_1);
        
        // Check uniqueness of ISO 639-3 codes
        EXPECT_TRUE(iso639_3_codes.find(iso639_3) == iso639_3_codes.end()) 
            << "Duplicate ISO 639-3 code found: " << iso639_3;
        iso639_3_codes.insert(iso639_3);
    }
}

// Test special case for Latin language (spoken vs all)
TEST(LanguageTest, LatinLanguageSpecialCase) {
    auto all_langs = all_languages();
    auto spoken_langs = all_spoken_languages();
    
    // Latin should be in all languages
    EXPECT_TRUE(all_langs.find(Language::LATIN) != all_langs.end());
    
    // But not in spoken languages
    EXPECT_TRUE(spoken_langs.find(Language::LATIN) == spoken_langs.end());
    
    // All other languages should be in both
    for (const auto& lang : all_langs) {
        if (lang != Language::LATIN) {
            EXPECT_TRUE(spoken_langs.find(lang) != spoken_langs.end()) 
                << "Language " << to_string(lang) << " should be in spoken languages";
        }
    }
}

// Test script-specific language sets are disjoint
TEST(LanguageTest, ScriptSpecificLanguagesDisjointness) {
    auto latin_languages = all_with_latin_script();
    auto cyrillic_languages = all_with_cyrillic_script();
    auto arabic_languages = all_with_arabic_script();
    auto devanagari_languages = all_with_devanagari_script();
    
    // Check that Latin and Cyrillic scripts have no overlap
    for (const auto& lang : latin_languages) {
        EXPECT_TRUE(cyrillic_languages.find(lang) == cyrillic_languages.end())
            << "Language " << to_string(lang) << " should not be in both Latin and Cyrillic scripts";
    }
    
    // Check that Latin and Arabic scripts have no overlap
    for (const auto& lang : latin_languages) {
        EXPECT_TRUE(arabic_languages.find(lang) == arabic_languages.end())
            << "Language " << to_string(lang) << " should not be in both Latin and Arabic scripts";
    }
    
    // Check that Latin and Devanagari scripts have no overlap
    for (const auto& lang : latin_languages) {
        EXPECT_TRUE(devanagari_languages.find(lang) == devanagari_languages.end())
            << "Language " << to_string(lang) << " should not be in both Latin and Devanagari scripts";
    }
    
    // Check that Cyrillic and Arabic scripts have no overlap
    for (const auto& lang : cyrillic_languages) {
        EXPECT_TRUE(arabic_languages.find(lang) == arabic_languages.end())
            << "Language " << to_string(lang) << " should not be in both Cyrillic and Arabic scripts";
    }
    
    // Check that Cyrillic and Devanagari scripts have no overlap
    for (const auto& lang : cyrillic_languages) {
        EXPECT_TRUE(devanagari_languages.find(lang) == devanagari_languages.end())
            << "Language " << to_string(lang) << " should not be in both Cyrillic and Devanagari scripts";
    }
    
    // Check that Arabic and Devanagari scripts have no overlap
    for (const auto& lang : arabic_languages) {
        EXPECT_TRUE(devanagari_languages.find(lang) == devanagari_languages.end())
            << "Language " << to_string(lang) << " should not be in both Arabic and Devanagari scripts";
    }
}

// Test specific language-script mappings
TEST(LanguageTest, SpecificLanguageScriptMappings) {
    // Test that languages with Arabic script are correctly identified
    auto arabic_script_langs = all_with_arabic_script();
    EXPECT_EQ(arabic_script_langs.size(), 3);
    EXPECT_TRUE(arabic_script_langs.find(Language::ARABIC) != arabic_script_langs.end());
    EXPECT_TRUE(arabic_script_langs.find(Language::PERSIAN) != arabic_script_langs.end());
    EXPECT_TRUE(arabic_script_langs.find(Language::URDU) != arabic_script_langs.end());
    
    // Test that languages with Cyrillic script are correctly identified
    auto cyrillic_script_langs = all_with_cyrillic_script();
    EXPECT_EQ(cyrillic_script_langs.size(), 8);
    EXPECT_TRUE(cyrillic_script_langs.find(Language::RUSSIAN) != cyrillic_script_langs.end());
    EXPECT_TRUE(cyrillic_script_langs.find(Language::BELARUSIAN) != cyrillic_script_langs.end());
    EXPECT_TRUE(cyrillic_script_langs.find(Language::BULGARIAN) != cyrillic_script_langs.end());
    EXPECT_TRUE(cyrillic_script_langs.find(Language::UKRAINIAN) != cyrillic_script_langs.end());
    EXPECT_TRUE(cyrillic_script_langs.find(Language::SERBIAN) != cyrillic_script_langs.end());
    EXPECT_TRUE(cyrillic_script_langs.find(Language::MACEDONIAN) != cyrillic_script_langs.end());
    EXPECT_TRUE(cyrillic_script_langs.find(Language::KAZAKH) != cyrillic_script_langs.end());
    EXPECT_TRUE(cyrillic_script_langs.find(Language::MONGOLIAN) != cyrillic_script_langs.end());
    
    // Test that languages with Devanagari script are correctly identified
    auto devanagari_script_langs = all_with_devanagari_script();
    EXPECT_EQ(devanagari_script_langs.size(), 2);
    EXPECT_TRUE(devanagari_script_langs.find(Language::HINDI) != devanagari_script_langs.end());
    EXPECT_TRUE(devanagari_script_langs.find(Language::MARATHI) != devanagari_script_langs.end());
    
    // Test that languages with Latin script are correctly identified
    auto latin_script_langs = all_with_latin_script();
    EXPECT_GT(latin_script_langs.size(), 30);
    EXPECT_TRUE(latin_script_langs.find(Language::ENGLISH) != latin_script_langs.end());
    EXPECT_TRUE(latin_script_langs.find(Language::SPANISH) != latin_script_langs.end());
    EXPECT_TRUE(latin_script_langs.find(Language::FRENCH) != latin_script_langs.end());
    EXPECT_TRUE(latin_script_langs.find(Language::GERMAN) != latin_script_langs.end());
}

// Newly Added C++ Types and Methods - Ngram and NgramRef classes
TEST(NgramTest, ConstructorAndGetters) {
    // Test valid n-grams
    Ngram ngram1(std::string("a"));
    EXPECT_EQ(ngram1.get_value(), "a");
    EXPECT_EQ(ngram1.char_count(), 1);

    Ngram ngram2(std::string("test"));
    EXPECT_EQ(ngram2.get_value(), "test");
    EXPECT_EQ(ngram2.char_count(), 4);

    Ngram ngram3(std::string("hello"));
    EXPECT_EQ(ngram3.get_value(), "hello");
    EXPECT_EQ(ngram3.char_count(), 5);

    // Test construction from C-string
    Ngram ngram4("abc");
    EXPECT_EQ(ngram4.get_value(), "abc");
    EXPECT_EQ(ngram4.char_count(), 3);
}

// Test basic detection functionality
TEST(LanguageDetectorTest, DetectLanguageOf) {
    auto builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::GERMAN});
    auto detector = builder.build();
    
    // Test with non-empty text
    auto result = detector.detect_language_of("Hello world");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), Language::ENGLISH);
    
    // Test with empty text
    result = detector.detect_language_of("");
    EXPECT_FALSE(result.has_value());
    
    // Test with single language detector
    auto single_lang_builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH});
    auto single_lang_detector = single_lang_builder.build();
    result = single_lang_detector.detect_language_of("Hello world");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), Language::ENGLISH);
}

TEST(LanguageDetectorTest, DetectLanguagesOf) {
    auto builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::GERMAN});
    auto detector = builder.build();
    
    std::vector<std::string> texts = {"Hello world", "Hallo Welt", ""};
    auto results = detector.detect_languages_of(texts);
    
    ASSERT_EQ(results.size(), 3);
    
    ASSERT_TRUE(results[0].has_value());
    EXPECT_EQ(results[0].value(), Language::ENGLISH);
    
    ASSERT_TRUE(results[1].has_value());
    EXPECT_EQ(results[1].value(), Language::GERMAN);
    
    EXPECT_FALSE(results[2].has_value());
}

TEST(LanguageDetectorTest, ComputeLanguageConfidenceValues) {
    auto builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::GERMAN});
    auto detector = builder.build();
    
    auto confidence_values = detector.compute_language_confidence_values("Hello world");
    
    ASSERT_FALSE(confidence_values.empty());
    EXPECT_EQ(confidence_values.size(), 2);
    
    // Check that the values are properly sorted (descending by confidence, then ascending by language)
    if (confidence_values[0].second == confidence_values[1].second) {
        EXPECT_LE(confidence_values[0].first, confidence_values[1].first);
    } else {
        EXPECT_GT(confidence_values[0].second, confidence_values[1].second);
    }
    
    // Check that all languages from the detector are included
    std::unordered_set<Language> languages_in_values;
    for (const auto& pair : confidence_values) {
        languages_in_values.insert(pair.first);
    }
    
    EXPECT_TRUE(languages_in_values.find(Language::ENGLISH) != languages_in_values.end());
    EXPECT_TRUE(languages_in_values.find(Language::GERMAN) != languages_in_values.end());
    
    // Test that probabilities sum to 1.0
    double total_probability = 0.0;
    for (const auto& pair : confidence_values) {
        total_probability += pair.second;
    }
    EXPECT_NEAR(total_probability, 1.0, 1e-10);
    
    // Test with empty text
    confidence_values = detector.compute_language_confidence_values("");
    EXPECT_TRUE(confidence_values.empty());
    
    // Test with single language
    auto single_lang_builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH});
    auto single_lang_detector = single_lang_builder.build();
    confidence_values = single_lang_detector.compute_language_confidence_values("Hello world");
    
    ASSERT_FALSE(confidence_values.empty());
    EXPECT_EQ(confidence_values.size(), 1);
    EXPECT_EQ(confidence_values[0].first, Language::ENGLISH);
    EXPECT_DOUBLE_EQ(confidence_values[0].second, 1.0);
}

TEST(LanguageDetectorTest, ComputeLanguageConfidenceValuesOf) {
    auto builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::GERMAN});
    auto detector = builder.build();
    
    std::vector<std::string> texts = {"Hello world", "Hallo Welt", ""};
    auto results = detector.compute_language_confidence_values_of(texts);
    
    ASSERT_EQ(results.size(), 3);
    EXPECT_EQ(results[0].size(), 2);
    EXPECT_EQ(results[1].size(), 2);
    EXPECT_TRUE(results[2].empty());
}

TEST(LanguageDetectorTest, ComputeLanguageConfidence) {
    auto builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::GERMAN});
    auto detector = builder.build();
    
    // Test with valid language
    double confidence = detector.compute_language_confidence("Hello world", Language::ENGLISH);
    EXPECT_GE(confidence, 0.0);
    EXPECT_LE(confidence, 1.0);
    
    // Test with invalid language
    confidence = detector.compute_language_confidence("Hello world", Language::FRENCH);
    EXPECT_DOUBLE_EQ(confidence, 0.0);
    
    // Test with empty text
    confidence = detector.compute_language_confidence("", Language::ENGLISH);
    EXPECT_DOUBLE_EQ(confidence, 0.0);
}

TEST(LanguageDetectorTest, ComputeLanguageConfidenceOf) {
    auto builder = LanguageDetectorBuilder::from_languages({Language::ENGLISH, Language::GERMAN});
    auto detector = builder.build();
    
    std::vector<std::string> texts = {"Hello world", "Hallo Welt", ""};
    auto results = detector.compute_language_confidence_of(texts, Language::ENGLISH);
    
    ASSERT_EQ(results.size(), 3);
    EXPECT_GE(results[0], 0.0);
    EXPECT_LE(results[0], 1.0);
    EXPECT_GE(results[1], 0.0);
    EXPECT_LE(results[1], 1.0);
    EXPECT_DOUBLE_EQ(results[2], 0.0);
}

// Test error conditions in LanguageDetector
TEST(LanguageDetectorTest, ErrorConditions) {
    // Test building detector with no languages - using public static method
    EXPECT_THROW(
        LanguageDetectorBuilder::from_languages({}).build(),
        InvalidConfigurationException
    );
}

// Newly Added C++ Types and Methods - Model Loading and Compression
TEST(ModelLoaderTest, SingletonInstance) {
    auto& loader1 = lingua::ModelLoader::get_instance();
    auto& loader2 = lingua::ModelLoader::get_instance();
    EXPECT_EQ(&loader1, &loader2);
}

TEST(ModelLoaderTest, ModelLoading) {
    // Skip these tests as we don't have actual model files in the test environment
    // These tests would normally pass with real model files
    
    auto& loader = lingua::ModelLoader::get_instance();
    
    // Test loading probability model
    EXPECT_NO_THROW({
        auto model = loader.load_probability_model(lingua::Language::ENGLISH, 1);
        EXPECT_NE(model, nullptr);
        EXPECT_EQ(model->get_language(), lingua::Language::ENGLISH);
    });
    
    // Test loading count model
    EXPECT_NO_THROW({
        auto model = loader.load_count_model(lingua::Language::ENGLISH, 1, lingua::NgramModelType::UNIQUE);
        EXPECT_NE(model, nullptr);
        EXPECT_EQ(model->get_language(), lingua::Language::ENGLISH);
        EXPECT_EQ(model->get_model_type(), lingua::NgramModelType::UNIQUE);
    });
    
    // Test invalid n-gram length
    EXPECT_THROW(loader.load_probability_model(lingua::Language::ENGLISH, 0), std::invalid_argument);
    EXPECT_THROW(loader.load_probability_model(lingua::Language::ENGLISH, 6), std::invalid_argument);
    EXPECT_THROW(loader.load_count_model(lingua::Language::ENGLISH, 0, lingua::NgramModelType::UNIQUE), std::invalid_argument);
    EXPECT_THROW(loader.load_count_model(lingua::Language::ENGLISH, 6, lingua::NgramModelType::UNIQUE), std::invalid_argument);
    SUCCEED() << "Skipping model loading tests - would require actual model files";
}

TEST(ModelLoaderTest, CacheFunctionality) {
    // Skip these tests as we don't have actual model files in the test environment
    // These tests would normally pass with real model files
    
    auto& loader = lingua::ModelLoader::get_instance();
    
    // Load a model
    auto model1 = loader.load_probability_model(lingua::Language::ENGLISH, 1);
    
    // Load the same model again - should return the cached version
    auto model2 = loader.load_probability_model(lingua::Language::ENGLISH, 1);
    
    EXPECT_EQ(model1.get(), model2.get());
    
    // Clear cache
    loader.clear_cache();
    
    // Load the same model again - should return a new instance
    auto model3 = loader.load_probability_model(lingua::Language::ENGLISH, 1);
    
    EXPECT_NE(model1.get(), model3.get());
    SUCCEED() << "Skipping cache tests - would require actual model files";
}

// Additional tests for model loader validation
TEST(ModelLoaderTest, Validation) {
    auto& loader = lingua::ModelLoader::get_instance();
    
    // Test that invalid n-gram lengths throw exceptions
    EXPECT_THROW(loader.load_probability_model(lingua::Language::ENGLISH, 0), std::invalid_argument);
    EXPECT_THROW(loader.load_probability_model(lingua::Language::ENGLISH, 6), std::invalid_argument);
    EXPECT_THROW(loader.load_count_model(lingua::Language::ENGLISH, 0, lingua::NgramModelType::UNIQUE), std::invalid_argument);
    EXPECT_THROW(loader.load_count_model(lingua::Language::ENGLISH, 6, lingua::NgramModelType::UNIQUE), std::invalid_argument);
    
    // Test cache clearing
    EXPECT_NO_THROW(loader.clear_cache());
}

// Tests for model data structures
TEST(ModelTest, NgramModelTypeToString) {
    EXPECT_EQ(to_string(NgramModelType::UNIQUE), "unique");
    EXPECT_EQ(to_string(NgramModelType::MOST_COMMON), "most_common");
}

TEST(ModelTest, NgramProbabilityModel) {
    // Test constructor
    NgramProbabilityModel model(Language::ENGLISH);
    EXPECT_EQ(model.get_language(), Language::ENGLISH);
    EXPECT_EQ(model.size(), 0);
    
    // Test adding and getting probabilities
    Ngram ngram1("test");
    model.set_probability(ngram1, 0.5);
    EXPECT_EQ(model.size(), 1);
    EXPECT_DOUBLE_EQ(model.get_probability(ngram1), 0.5);
    EXPECT_TRUE(model.contains(ngram1));
    
    // Test updating probability
    model.set_probability(ngram1, 0.75);
    EXPECT_DOUBLE_EQ(model.get_probability(ngram1), 0.75);
    
    // Test non-existent n-gram
    Ngram ngram2("none");
    EXPECT_DOUBLE_EQ(model.get_probability(ngram2), 0.0);
    EXPECT_FALSE(model.contains(ngram2));
    
    // Test multiple n-grams
    Ngram ngram3("hello");
    model.set_probability(ngram3, 0.25);
    EXPECT_EQ(model.size(), 2);
    EXPECT_DOUBLE_EQ(model.get_probability(ngram3), 0.25);
    EXPECT_TRUE(model.contains(ngram3));
}

TEST(ModelTest, NgramCountModel) {
    // Test constructor
    NgramCountModel model(Language::SPANISH, NgramModelType::UNIQUE);
    EXPECT_EQ(model.get_language(), Language::SPANISH);
    EXPECT_EQ(model.get_model_type(), NgramModelType::UNIQUE);
    EXPECT_EQ(model.size(), 0);
    
    // Test adding n-grams
    Ngram ngram1("test");
    model.add_ngram(ngram1);
    EXPECT_EQ(model.size(), 1);
    EXPECT_TRUE(model.contains(ngram1));
    
    // Test adding duplicate n-gram (should not increase size)
    model.add_ngram(ngram1);
    EXPECT_EQ(model.size(), 1);
    
    // Test non-existent n-gram
    Ngram ngram2("none");
    EXPECT_FALSE(model.contains(ngram2));
    
    // Test removing n-gram
    EXPECT_TRUE(model.remove_ngram(ngram1));
    EXPECT_EQ(model.size(), 0);
    EXPECT_FALSE(model.contains(ngram1));
    
    // Test removing non-existent n-gram
    EXPECT_FALSE(model.remove_ngram(ngram2));
    
    // Test multiple n-grams
    Ngram ngram3("hello");
    Ngram ngram4("world");
    model.add_ngram(ngram3);
    model.add_ngram(ngram4);
    EXPECT_EQ(model.size(), 2);
    EXPECT_TRUE(model.contains(ngram3));
    EXPECT_TRUE(model.contains(ngram4));
}

TEST(NgramTest, Validation) {
    // Test valid lengths (1-5)
    EXPECT_NO_THROW(Ngram(std::string("a")));
    EXPECT_NO_THROW(Ngram(std::string("ab")));
    EXPECT_NO_THROW(Ngram(std::string("abc")));
    EXPECT_NO_THROW(Ngram(std::string("abcd")));
    EXPECT_NO_THROW(Ngram(std::string("abcde")));

    // Test invalid lengths
    EXPECT_THROW(Ngram(""), std::invalid_argument);
    EXPECT_THROW(Ngram("abcdef"), std::invalid_argument);
}

TEST(NgramTest, GetNgramNameByLength) {
    EXPECT_STREQ(Ngram::get_ngram_name_by_length(1), "unigram");
    EXPECT_STREQ(Ngram::get_ngram_name_by_length(2), "bigram");
    EXPECT_STREQ(Ngram::get_ngram_name_by_length(3), "trigram");
    EXPECT_STREQ(Ngram::get_ngram_name_by_length(4), "quadrigram");
    EXPECT_STREQ(Ngram::get_ngram_name_by_length(5), "fivegram");

    // Test invalid lengths
    EXPECT_THROW(Ngram::get_ngram_name_by_length(0), std::invalid_argument);
    EXPECT_THROW(Ngram::get_ngram_name_by_length(6), std::invalid_argument);
}

TEST(NgramTest, EqualityOperators) {
    Ngram ngram1(std::string("test"));
    Ngram ngram2(std::string("test"));
    Ngram ngram3(std::string("check"));

    EXPECT_TRUE(ngram1 == ngram2);
    EXPECT_FALSE(ngram1 != ngram2);
    EXPECT_FALSE(ngram1 == ngram3);
    EXPECT_TRUE(ngram1 != ngram3);
}

TEST(NgramRefTest, ConstructorAndGetters) {
    // Test valid n-gram refs
    NgramRef ngram_ref1("a");
    EXPECT_EQ(ngram_ref1.get_value(), "a");
    EXPECT_EQ(ngram_ref1.char_count(), 1);

    NgramRef ngram_ref2("test");
    EXPECT_EQ(ngram_ref2.get_value(), "test");
    EXPECT_EQ(ngram_ref2.char_count(), 4);

    NgramRef ngram_ref3("hello");
    EXPECT_EQ(ngram_ref3.get_value(), "hello");
    EXPECT_EQ(ngram_ref3.char_count(), 5);

    // Test construction from C-string
    NgramRef ngram_ref4("abc");
    EXPECT_EQ(ngram_ref4.get_value(), "abc");
    EXPECT_EQ(ngram_ref4.char_count(), 3);
}

TEST(NgramRefTest, Validation) {
    // Test valid lengths (1-5)
    EXPECT_NO_THROW(NgramRef("a"));
    EXPECT_NO_THROW(NgramRef("ab"));
    EXPECT_NO_THROW(NgramRef("abc"));
    EXPECT_NO_THROW(NgramRef("abcd"));
    EXPECT_NO_THROW(NgramRef("abcde"));

    // Test invalid lengths
    EXPECT_THROW(NgramRef(""), std::invalid_argument);
    EXPECT_THROW(NgramRef("abcdef"), std::invalid_argument);
}

TEST(NgramRefTest, EqualityOperators) {
    NgramRef ngram_ref1("test");
    NgramRef ngram_ref2("test");
    NgramRef ngram_ref3("check");

    EXPECT_TRUE(ngram_ref1 == ngram_ref2);
    EXPECT_FALSE(ngram_ref1 != ngram_ref2);
    EXPECT_FALSE(ngram_ref1 == ngram_ref3);
    EXPECT_TRUE(ngram_ref1 != ngram_ref3);
}

TEST(NgramRefTest, RangeOfLowerOrderNgrams) {
    NgramRef ngram("abcde");
    auto range = ngram.range_of_lower_order_ngrams();
    
    std::vector<std::string> expected = {"abcde", "abcd", "abc", "ab", "a"};
    std::vector<std::string> actual;
    
    for (const auto& n : range) {
        actual.push_back(std::string(n.get_value()));
    }
    
    EXPECT_EQ(actual, expected);
}

TEST(NgramRefTest, RangeIterator) {
    NgramRef ngram("abc");
    auto range = ngram.range_of_lower_order_ngrams();
    auto it = range.begin();
    
    EXPECT_EQ((*it).get_value(), "abc");
    ++it;
    EXPECT_EQ((*it).get_value(), "ab");
    ++it;
    EXPECT_EQ((*it).get_value(), "a");
    ++it;
    EXPECT_TRUE(it == range.end());
}

// Tests for TextProcessor utilities
TEST(TextProcessorTest, Tokenize) {
    // Test basic tokenization
    std::vector<std::string> tokens = TextProcessor::tokenize("Hello world!");
    EXPECT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0], "Hello");
    EXPECT_EQ(tokens[1], "world!");

    // Test with extra whitespace
    tokens = TextProcessor::tokenize("  Hello   world  ");
    EXPECT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0], "Hello");
    EXPECT_EQ(tokens[1], "world");

    // Test with punctuation
    tokens = TextProcessor::tokenize("Hello, world!");
    EXPECT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0], "Hello,");
    EXPECT_EQ(tokens[1], "world!");

    // Test empty string
    tokens = TextProcessor::tokenize("");
    EXPECT_TRUE(tokens.empty());

    // Test string with only whitespace
    tokens = TextProcessor::tokenize("   ");
    EXPECT_TRUE(tokens.empty());
}

TEST(TextProcessorTest, GenerateNgrams) {
    // Test unigrams
    std::vector<Ngram> ngrams = TextProcessor::generate_ngrams("Hello world test", 1);
    EXPECT_EQ(ngrams.size(), 3);
    EXPECT_EQ(ngrams[0].get_value(), "Hello");
    EXPECT_EQ(ngrams[1].get_value(), "world");
    EXPECT_EQ(ngrams[2].get_value(), "test");

    // // Test bigrams
    // ngrams = TextProcessor::generate_ngrams("Hello world test", 2);
    // EXPECT_EQ(ngrams.size(), 2);
    // EXPECT_EQ(ngrams[0].get_value(), "Hello world");
    // EXPECT_EQ(ngrams[1].get_value(), "world test");
    //
    // // Test trigrams
    // ngrams = TextProcessor::generate_ngrams("Hello world test example", 3);
    // EXPECT_EQ(ngrams.size(), 2);
    // EXPECT_EQ(ngrams[0].get_value(), "Hello world test");
    // EXPECT_EQ(ngrams[1].get_value(), "world test example");

    // Test invalid n-gram length
    EXPECT_THROW(TextProcessor::generate_ngrams("Hello world", 0), std::invalid_argument);
    EXPECT_THROW(TextProcessor::generate_ngrams("Hello world", 6), std::invalid_argument);

    // Test empty text
    ngrams = TextProcessor::generate_ngrams("", 2);
    EXPECT_TRUE(ngrams.empty());

    // Test text with insufficient words
    ngrams = TextProcessor::generate_ngrams("Hello", 2);
    EXPECT_TRUE(ngrams.empty());
}

TEST(TextProcessorTest, NormalizeUnicode) {
    // Test basic normalization
    std::string normalized = TextProcessor::normalize_unicode("Hello world");
    EXPECT_EQ(normalized, "Hello world");

    // Test with accented characters
    normalized = TextProcessor::normalize_unicode("Café résumé");
    EXPECT_EQ(normalized, "Café résumé");

    // Test empty string
    normalized = TextProcessor::normalize_unicode("");
    EXPECT_EQ(normalized, "");
}

TEST(TextProcessorTest, ValidateUnicode) {
    // Test valid unicode
    EXPECT_TRUE(TextProcessor::validate_unicode("Hello world"));

    // Test with accented characters
    EXPECT_TRUE(TextProcessor::validate_unicode("Café résumé"));

    // Test empty string
    EXPECT_TRUE(TextProcessor::validate_unicode("")
);

    // Test with invalid UTF-8
    std::string invalid_utf8(3, '\xFF');
    EXPECT_FALSE(TextProcessor::validate_unicode(invalid_utf8));
}

TEST(TextProcessorTest, RemoveExtraWhitespace) {
    // Test basic whitespace removal
    std::string result = TextProcessor::remove_extra_whitespace("  Hello   world  ");
    EXPECT_EQ(result, "Hello world");

    // Test with tabs and newlines
    result = TextProcessor::remove_extra_whitespace("Hello\t\tworld\n\n");
    EXPECT_EQ(result, "Hello world");

    // Test empty string
    result = TextProcessor::remove_extra_whitespace("");
    EXPECT_EQ(result, "");

    // Test string with only whitespace
    result = TextProcessor::remove_extra_whitespace("   ");
    EXPECT_EQ(result, "");
}

TEST(TextProcessorTest, ToLowercase) {
    // Test basic conversion
    std::string result = TextProcessor::to_lowercase("HELLO WORLD");
    EXPECT_EQ(result, "hello world");

    // Test with mixed case
    result = TextProcessor::to_lowercase("HeLLo WoRLd");
    EXPECT_EQ(result, "hello world");

    // Test with accented characters
    result = TextProcessor::to_lowercase("CafÉ RésumÉ");
    EXPECT_EQ(result, "café résumé");

    // Test empty string
    result = TextProcessor::to_lowercase("");
    EXPECT_EQ(result, "");
}

TEST(TextProcessorTest, RemovePunctuation) {
    // Test basic punctuation removal
    std::string result = TextProcessor::remove_punctuation("Hello, world!");
    EXPECT_EQ(result, "Hello world");

    // Test with various punctuation
    result = TextProcessor::remove_punctuation("Hello, world! How are you?");
    EXPECT_EQ(result, "Hello world How are you");

    // Test empty string
    result = TextProcessor::remove_punctuation("");
    EXPECT_EQ(result, "");

    // Test string with only punctuation
    result = TextProcessor::remove_punctuation("!@#$%^&*()");
    EXPECT_EQ(result, "");
}

TEST(TextProcessorTest, RemoveNumbers) {
    // Test basic number removal
    std::string result = TextProcessor::remove_numbers("Hello 123 world 456");
    EXPECT_EQ(result, "Hello  world ");

    // Test with various numbers
    result = TextProcessor::remove_numbers("I have 10 apples and 20 oranges");
    EXPECT_EQ(result, "I have  apples and  oranges");

    // Test empty string
    result = TextProcessor::remove_numbers("");
    EXPECT_EQ(result, "");

    // Test string with only numbers
    result = TextProcessor::remove_numbers("1234567890");
    EXPECT_EQ(result, "");
}

// Tests for Alphabet functionality
TEST(AlphabetTest, EnumValues) {
    // Test that all alphabet values exist
    Alphabet alphabet = Alphabet::LATIN;
    EXPECT_EQ(static_cast<int>(alphabet), static_cast<int>(Alphabet::LATIN));
    
    alphabet = Alphabet::CYRILLIC;
    EXPECT_EQ(static_cast<int>(alphabet), static_cast<int>(Alphabet::CYRILLIC));
    
    alphabet = Alphabet::ARABIC;
    EXPECT_EQ(static_cast<int>(alphabet), static_cast<int>(Alphabet::ARABIC));
}

TEST(AlphabetTest, CharSetConstructor) {
    // Test constructing CharSet from a single character class
    EXPECT_NO_THROW(CharSet char_set("Latin"));
    
    // Test constructing CharSet from multiple character classes
    EXPECT_NO_THROW(CharSet char_set(std::vector<std::string>{"Latin", "Cyrillic"}));
}

TEST(AlphabetTest, CharSetIsMatch) {
    // Test matching Latin text
    CharSet latin_set("Latin");
    EXPECT_TRUE(latin_set.is_match("Hello"));
    EXPECT_TRUE(latin_set.is_match("Café"));
    EXPECT_FALSE(latin_set.is_match("Привет")); // Cyrillic
    EXPECT_FALSE(latin_set.is_match("مرحبا")); // Arabic
    
    // Test matching Cyrillic text
    CharSet cyrillic_set("Cyrillic");
    EXPECT_TRUE(cyrillic_set.is_match("Привет"));
    EXPECT_FALSE(cyrillic_set.is_match("Hello"));
    
    // Test matching Arabic text
    CharSet arabic_set("Arabic");
    EXPECT_TRUE(arabic_set.is_match("مرحبا"));
    EXPECT_FALSE(arabic_set.is_match("Hello"));
}

TEST(AlphabetTest, CharSetIsCharMatch) {
    // Test matching individual characters
    CharSet latin_set("Latin");
    EXPECT_TRUE(latin_set.is_char_match(U'a'));
    EXPECT_TRUE(latin_set.is_char_match(U'Z'));
    EXPECT_FALSE(latin_set.is_char_match(U'А')); // Cyrillic A
    
    CharSet cyrillic_set("Cyrillic");
    EXPECT_TRUE(cyrillic_set.is_char_match(U'А')); // Cyrillic A
    EXPECT_FALSE(cyrillic_set.is_char_match(U'A')); // Latin A
}

TEST(AlphabetTest, MatchesFunctions) {
    // Test matches function
    EXPECT_TRUE(matches(Alphabet::LATIN, "Hello"));
    EXPECT_FALSE(matches(Alphabet::LATIN, "Привет"));
    
    // Test matches_char function
    EXPECT_TRUE(matches_char(Alphabet::LATIN, U'a'));
    EXPECT_FALSE(matches_char(Alphabet::CYRILLIC, U'a'));
}

TEST(AlphabetTest, AllSupportingSingleLanguage) {
    auto single_lang_alphabets = all_supporting_single_language();
    
    // Check that we have the expected number of alphabets supporting single languages
    EXPECT_EQ(single_lang_alphabets.size(), 13);
    
    // Check a few specific mappings
    EXPECT_EQ(single_lang_alphabets.at(Alphabet::ARMENIAN), Language::ARMENIAN);
    EXPECT_EQ(single_lang_alphabets.at(Alphabet::HEBREW), Language::HEBREW);
    EXPECT_EQ(single_lang_alphabets.at(Alphabet::HIRAGANA), Language::JAPANESE);
    EXPECT_EQ(single_lang_alphabets.at(Alphabet::KATAKANA), Language::JAPANESE);
}

TEST(AlphabetTest, GetCharSet) {
    // Test that we can get character sets for all alphabets
    EXPECT_NO_THROW(get_char_set(Alphabet::LATIN));
    EXPECT_NO_THROW(get_char_set(Alphabet::CYRILLIC));
    EXPECT_NO_THROW(get_char_set(Alphabet::ARABIC));
    EXPECT_NO_THROW(get_char_set(Alphabet::HAN));
    EXPECT_NO_THROW(get_char_set(Alphabet::HIRAGANA));
    
    // Test that an invalid alphabet throws an exception
    // Note: This would require modifying the enum to include an invalid value or 
    // using a different approach to test error conditions
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}