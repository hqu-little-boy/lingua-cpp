# Lingua C++

[![License](https://img.shields.io/badge/license-Apache%202.0-blue.svg)](LICENSE)

A linguistic library for detecting and processing languages in C++, based on the [Lingua](https://github.com/pemistahl/lingua-rs) project.

## Overview

Lingua C++ is a powerful language detection library that can identify the language of given text with high accuracy. It is designed to be lightweight, efficient, and easy to integrate into C++ projects.

## Features

- Detect the language of given input text
- Compute confidence values for language detection
- Support for 75 languages
- Thread-safe language detection
- Efficient memory usage with model caching
- Unicode support
- Extensive test coverage

## Supported Languages

Lingua C++ supports 75 languages, including:
- Major world languages (English, Spanish, French, German, Chinese, Japanese, etc.)
- Regional languages (Afrikaans, Albanian, Basque, etc.)
- Languages with special scripts (Arabic, Cyrillic, Devanagari, etc.)

For a complete list of supported languages, see the [language.h](include/lingua/language.h) file.

## Installation

### Prerequisites

- C++20 compatible compiler (GCC 10+, Clang 10+, or MSVC 2019+)
- CMake 3.15 or higher
- Ninja build system (optional but recommended)

### Building from Source

```bash
git clone https://github.com/your-username/lingua-cpp.git
cd lingua-cpp
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --parallel
```

For faster builds with Ninja:

```bash
git clone https://github.com/your-username/lingua-cpp.git
cd lingua-cpp
cmake -GNinja -DCMAKE_BUILD_TYPE=Release -Bbuild
cmake --build build --parallel
```

## Usage

### Basic Language Detection

```cpp
#include "lingua/lingua.h"
#include <iostream>

using namespace lingua;

int main() {
    // Create a language detector for all languages
    auto builder = LanguageDetectorBuilder::from_all_languages();
    auto detector = builder.build();
    
    // Detect language
    std::string text = "This is an English sentence.";
    auto result = detector.detect_language_of(text);
    
    if (result.has_value()) {
        std::cout << "Detected language: " << to_string(result.value()) << std::endl;
    } else {
        std::cout << "Language could not be reliably detected." << std::endl;
    }
    
    return 0;
}
```

### Confidence Values

```cpp
#include "lingua/lingua.h"
#include <iostream>

using namespace lingua;

int main() {
    auto builder = LanguageDetectorBuilder::from_all_languages();
    auto detector = builder.build();
    
    std::string text = "This is an English sentence.";
    auto confidence_values = detector.compute_language_confidence_values(text);
    
    std::cout << "Language confidence values:" << std::endl;
    for (const auto& [language, confidence] : confidence_values) {
        std::cout << to_string(language) << ": " << confidence << std::endl;
    }
    
    return 0;
}
```

### Custom Language Selection

```cpp
#include "lingua/lingua.h"
#include <iostream>

using namespace lingua;

int main() {
    // Create a language detector for specific languages only
    std::vector<Language> languages = {Language::ENGLISH, Language::GERMAN, Language::FRENCH};
    auto builder = LanguageDetectorBuilder::from_languages(languages);
    auto detector = builder.build();
    
    std::string text = "Ceci est une phrase française.";
    auto result = detector.detect_language_of(text);
    
    if (result.has_value()) {
        std::cout << "Detected language: " << to_string(result.value()) << std::endl;
    }
    
    return 0;
}
```

### Advanced Configuration

```cpp
#include "lingua/lingua.h"
#include <iostream>

using namespace lingua;

int main() {
    // Create a language detector with advanced configuration
    auto builder = LanguageDetectorBuilder::from_all_languages()
        .with_minimum_relative_distance(0.5)  // Set minimum relative distance
        .with_preloaded_language_models()      // Preload all language models
        .with_low_accuracy_mode();             // Enable low accuracy mode for performance
    
    auto detector = builder.build();
    
    std::string text = "This is an English sentence.";
    auto result = detector.detect_language_of(text);
    
    if (result.has_value()) {
        std::cout << "Detected language: " << to_string(result.value()) << std::endl;
    }
    
    return 0;
}
```

## API Documentation

### LanguageDetectorBuilder

The `LanguageDetectorBuilder` class is used to configure and create instances of `LanguageDetector`.

#### Static Factory Methods

- `from_all_languages()` - Creates a builder with all 75 languages
- `from_all_spoken_languages()` - Creates a builder with all spoken languages (excludes Latin)
- `from_all_languages_with_arabic_script()` - Creates a builder with languages using Arabic script
- `from_all_languages_with_cyrillic_script()` - Creates a builder with languages using Cyrillic script
- `from_all_languages_with_devanagari_script()` - Creates a builder with languages using Devanagari script
- `from_all_languages_with_latin_script()` - Creates a builder with languages using Latin script
- `from_all_languages_without(const std::vector<Language>& languages)` - Creates a builder with all languages except those specified
- `from_languages(const std::vector<Language>& languages)` - Creates a builder with the specified languages
- `from_iso_codes_639_1(const std::vector<std::string>& iso_codes)` - Creates a builder with languages specified by ISO 639-1 codes
- `from_iso_codes_639_3(const std::vector<std::string>& iso_codes)` - Creates a builder with languages specified by ISO 639-3 codes

#### Configuration Methods

- `with_minimum_relative_distance(double distance)` - Sets the minimum relative distance measure (0.0 to 0.99)
- `with_preloaded_language_models()` - Configures the detector to preload all language models
- `with_low_accuracy_mode()` - Enables low accuracy mode to save memory and improve performance

#### Build Method

- `build()` - Creates and returns the configured instance of `LanguageDetector`

### LanguageDetector

The `LanguageDetector` class is used to detect languages in text.

#### Detection Methods

- `detect_language_of(const std::string& text)` - Detects the language of given input text
- `detect_languages_of(const std::vector<std::string>& texts)` - Detects the languages of all given input texts
- `detect_multiple_languages_of(const std::string& text)` - Attempts to detect multiple languages in mixed-language text (experimental)

#### Confidence Methods

- `compute_language_confidence_values(const std::string& text)` - Computes confidence values for each supported language
- `compute_language_confidence_values_of(const std::vector<std::string>& texts)` - Computes confidence values for multiple texts
- `compute_language_confidence(const std::string& text, Language language)` - Computes confidence value for a specific language
- `compute_language_confidence_of(const std::vector<std::string>& texts, Language language)` - Computes confidence values for a specific language across multiple texts

#### Model Management

- `unload_language_models()` - Clears all loaded language models and frees memory

### Language

The `Language` enum represents all supported languages. Helper functions are available for working with languages:

- `all_languages()` - Returns a set of all supported languages
- `all_spoken_languages()` - Returns a set of all supported spoken languages
- `all_with_arabic_script()` - Returns a set of languages supporting Arabic script
- `all_with_cyrillic_script()` - Returns a set of languages supporting Cyrillic script
- `all_with_devanagari_script()` - Returns a set of languages supporting Devanagari script
- `all_with_latin_script()` - Returns a set of languages supporting Latin script
- `iso_code_639_1(Language language)` - Returns the ISO 639-1 code for a language
- `iso_code_639_3(Language language)` - Returns the ISO 639-3 code for a language
- `from_iso_code_639_1(const std::string& iso_code)` - Returns the language for an ISO 639-1 code
- `from_iso_code_639_3(const std::string& iso_code)` - Returns the language for an ISO 639-3 code
- `to_string(Language language)` - Converts a language to its string representation
- `from_string(const std::string& language_str)` - Converts a string to a language

## Examples

See the [examples](examples/) directory for more usage examples:
- [builder_configurations.cpp](examples/builder_configurations.cpp) - Shows different builder configurations
- [detection_example.cpp](examples/detection_example.cpp) - Basic language detection
- [confidence_values_example.cpp](examples/confidence_values_example.cpp) - Computing confidence values

## Testing

The project includes comprehensive unit tests using Google Test. To run the tests:

```bash
cd build
ctest
```

Or run specific test executables:

```bash
cd build
./unit_tests
./comprehensive_tests
```

## Third-Party Libraries

This project uses the following third-party libraries:

- [Brotli](https://github.com/google/brotli) - For model compression/decompression
- [GoogleTest](https://github.com/google/googletest) - For unit testing
- [simdjson](https://github.com/simdjson/simdjson) - For fast JSON parsing
- [spdlog](https://github.com/gabime/spdlog) - For logging
- [utfcpp](https://github.com/nemtrif/utfcpp) - For UTF-8 handling

## License

This project is licensed under the Apache License, Version 2.0. See the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## Acknowledgments

This project is based on the excellent work of Peter M. Stahl in the [Lingua](https://github.com/pemistahl/lingua-rs) project for Rust.