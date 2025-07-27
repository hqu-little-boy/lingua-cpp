#ifndef LINGUA_TEXT_PROCESSOR_H_
#define LINGUA_TEXT_PROCESSOR_H_

#include <string>
#include <vector>
#include <functional>
#include <memory>

#include "lingua/ngram.h"

namespace lingua {

/**
 * @brief Utility class for text processing operations.
 * 
 * This class provides functions for tokenizing text, generating n-grams,
 * and performing Unicode normalization and validation.
 */
class TextProcessor {
public:
    /**
     * @brief Tokenizes the input text into individual words.
     * 
     * This function splits the text by whitespace and punctuation,
     * returning a vector of words.
     * 
     * @param text The input text to tokenize
     * @return A vector of words extracted from the text
     */
    static std::vector<std::string> tokenize(const std::string& text);

    /**
     * @brief Generates n-grams from the input text.
     * 
     * This function creates n-grams of the specified length from the input text.
     * 
     * @param text The input text to process
     * @param n The length of n-grams to generate (1-5)
     * @return A vector of Ngram objects representing the n-grams
     * @throws std::invalid_argument if n is not between 1 and 5
     */
    static std::vector<Ngram> generate_ngrams(const std::string& text, size_t n);

    /**
     * @brief Normalizes Unicode text.
     * 
     * This function performs Unicode normalization on the input text,
     * converting it to a consistent form.
     * 
     * @param text The input text to normalize
     * @return The normalized text
     */
    static std::string normalize_unicode(const std::string& text);

    /**
     * @brief Validates Unicode text.
     * 
     * This function checks if the input text contains only valid Unicode characters.
     * 
     * @param text The input text to validate
     * @return True if the text is valid Unicode, false otherwise
     */
    static bool validate_unicode(const std::string& text);

    /**
     * @brief Removes extra whitespace from text.
     * 
     * This function replaces multiple consecutive whitespace characters
     * with a single space and trims leading/trailing whitespace.
     * 
     * @param text The input text to process
     * @return The text with normalized whitespace
     */
    static std::string remove_extra_whitespace(const std::string& text);

    /**
     * @brief Converts text to lowercase.
     * 
     * This function converts all characters in the input text to lowercase.
     * 
     * @param text The input text to convert
     * @return The lowercase text
     */
    static std::string to_lowercase(const std::string& text);

    /**
     * @brief Removes punctuation from text.
     * 
     * This function removes all punctuation characters from the input text.
     * 
     * @param text The input text to process
     * @return The text without punctuation
     */
    static std::string remove_punctuation(const std::string& text);

    /**
     * @brief Removes numbers from text.
     * 
     * This function removes all numeric characters from the input text.
     * 
     * @param text The input text to process
     * @return The text without numbers
     */
    static std::string remove_numbers(const std::string& text);

private:
    /**
     * @brief Helper function to split text by a delimiter.
     * 
     * @param text The input text to split
     * @param delimiter The delimiter to split on
     * @return A vector of substrings
     */
    static std::vector<std::string> split(const std::string& text, char delimiter);

    /**
     * @brief Helper function to trim whitespace from text.
     * 
     * @param text The input text to trim
     * @return The trimmed text
     */
    static std::string trim(const std::string& text);
};

} // namespace lingua

#endif // LINGUA_TEXT_PROCESSOR_H_