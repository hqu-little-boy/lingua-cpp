#ifndef LINGUA_NGRAM_H
#define LINGUA_NGRAM_H

#include <string>
#include <string_view>
#include <stdexcept>
#include <iterator>

namespace lingua {

/**
 * @brief Class for storing n-gram strings with validation.
 * 
 * This class represents an n-gram as an owned string with validation
 * to ensure the length is between 1 and 5 characters.
 */
class Ngram {
public:
    /**
     * @brief Constructs an Ngram from a string.
     * 
     * @param value The string value for the n-gram
     * @throws std::invalid_argument if the string length is not between 1 and 5
     */
    explicit Ngram(const std::string& value);

    /**
     * @brief Constructs an Ngram from a C-string.
     * 
     * @param value The C-string value for the n-gram
     * @throws std::invalid_argument if the string length is not between 1 and 5
     */
    explicit Ngram(const char* value);

    /**
     * @brief Get the string value of the n-gram.
     * 
     * @return const std::string& The n-gram value
     */
    const std::string& get_value() const;

    /**
     * @brief Get the character count of the n-gram.
     * 
     * @return size_t The number of characters in the n-gram
     */
    size_t char_count() const;

    /**
     * @brief Get the name of an n-gram based on its length.
     * 
     * @param ngram_length The length of the n-gram (1-5)
     * @return const char* The name ("unigram", "bigram", etc.)
     * @throws std::invalid_argument if ngram_length is not between 1 and 5
     */
    static const char* get_ngram_name_by_length(size_t ngram_length);

    /**
     * @brief Equality operator.
     * 
     * @param other The other Ngram to compare with
     * @return true if the n-grams are equal
     * @return false if the n-grams are not equal
     */
    bool operator==(const Ngram& other) const;

    /**
     * @brief Inequality operator.
     * 
     * @param other The other Ngram to compare with
     * @return true if the n-grams are not equal
     * @return false if the n-grams are equal
     */
    bool operator!=(const Ngram& other) const;

private:
    std::string value_;
    size_t char_count_;

    void validate_length(size_t length) const;
};

/**
 * @brief Class for efficient string references to n-grams.
 * 
 * This class represents an n-gram as a string view with validation
 * to ensure the length is between 1 and 5 characters.
 */
class NgramRef {
public:
    /**
     * @brief Constructs an NgramRef from a string view.
     * 
     * @param value The string view for the n-gram
     * @throws std::invalid_argument if the string length is not between 1 and 5
     */
    explicit NgramRef(std::string_view value);

    /**
     * @brief Constructs an NgramRef from a C-string.
     * 
     * @param value The C-string for the n-gram
     * @throws std::invalid_argument if the string length is not between 1 and 5
     */
    explicit NgramRef(const char* value);

    /**
     * @brief Get the string view of the n-gram.
     * 
     * @return std::string_view The n-gram value
     */
    std::string_view get_value() const;

    /**
     * @brief Get the character count of the n-gram.
     * 
     * @return size_t The number of characters in the n-gram
     */
    size_t char_count() const;

    /**
     * @brief Equality operator.
     * 
     * @param other The other NgramRef to compare with
     * @return true if the n-grams are equal
     * @return false if the n-grams are not equal
     */
    bool operator==(const NgramRef& other) const;

    /**
     * @brief Inequality operator.
     * 
     * @param other The other NgramRef to compare with
     * @return true if the n-grams are not equal
     * @return false if the n-grams are equal
     */
    bool operator!=(const NgramRef& other) const;

    /**
     * @brief Range of lower order n-grams.
     * 
     * Returns an iterator that yields this n-gram and all its lower-order n-grams.
     * For example, for "abcde", it yields "abcde", "abcd", "abc", "ab", "a".
     * 
     * @return A range object for iterating over lower-order n-grams
     */
    class Range {
    public:
        class Iterator {
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = NgramRef;
            using difference_type = std::ptrdiff_t;
            using pointer = const NgramRef*;
            using reference = const NgramRef&;

            Iterator(std::string_view value, size_t char_count, bool is_end = false);
            
            reference operator*() const;
            pointer operator->() const;
            Iterator& operator++();
            Iterator operator++(int);
            bool operator==(const Iterator& other) const;
            bool operator!=(const Iterator& other) const;

        private:
            std::string_view value_;
            size_t char_count_;
            bool is_end_;
            
            void update_to_prefix();
        };

        explicit Range(std::string_view start_value, size_t start_char_count);

        Iterator begin() const;
        Iterator end() const;

    private:
        std::string_view start_value_;
        size_t start_char_count_;
    };

    Range range_of_lower_order_ngrams() const;

private:
    std::string_view value_;
    size_t char_count_;

    void validate_length(size_t length) const;
    
    // Helper function to get a prefix of an n-gram
    static std::string_view get_prefix(std::string_view str, size_t char_count);
};

} // namespace lingua

#endif // LINGUA_NGRAM_H