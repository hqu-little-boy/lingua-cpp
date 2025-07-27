#include "lingua/ngram.h"
#include <stdexcept>
#include <algorithm>

namespace lingua {

// Ngram implementation

Ngram::Ngram(const std::string& value) : value_(value), char_count_(value.length()) {
    validate_length(char_count_);
}

Ngram::Ngram(const char* value) : value_(value), char_count_(std::char_traits<char>::length(value)) {
    validate_length(char_count_);
}

const std::string& Ngram::get_value() const {
    return value_;
}

size_t Ngram::char_count() const {
    return char_count_;
}

const char* Ngram::get_ngram_name_by_length(size_t ngram_length) {
    switch (ngram_length) {
        case 1: return "unigram";
        case 2: return "bigram";
        case 3: return "trigram";
        case 4: return "quadrigram";
        case 5: return "fivegram";
        default:
            throw std::invalid_argument("ngram length " + std::to_string(ngram_length) + " is not in range 1..5");
    }
}

bool Ngram::operator==(const Ngram& other) const {
    return value_ == other.value_;
}

bool Ngram::operator!=(const Ngram& other) const {
    return !(*this == other);
}

void Ngram::validate_length(size_t length) const {
    if (length < 1 || length > 5) {
        throw std::invalid_argument("length " + std::to_string(length) + " of ngram '" + value_ + "' is not in range 1..5");
    }
}

// NgramRef implementation

NgramRef::NgramRef(std::string_view value) : value_(value), char_count_(value.length()) {
    validate_length(char_count_);
}

NgramRef::NgramRef(const char* value) : value_(value), char_count_(std::char_traits<char>::length(value)) {
    validate_length(char_count_);
}

std::string_view NgramRef::get_value() const {
    return value_;
}

size_t NgramRef::char_count() const {
    return char_count_;
}

bool NgramRef::operator==(const NgramRef& other) const {
    return value_ == other.value_;
}

bool NgramRef::operator!=(const NgramRef& other) const {
    return !(*this == other);
}

NgramRef::Range NgramRef::range_of_lower_order_ngrams() const {
    return Range(value_, char_count_);
}

void NgramRef::validate_length(size_t length) const {
    if (length < 1 || length > 5) {
        throw std::invalid_argument("length " + std::to_string(length) + " of ngram '" + std::string(value_) + "' is not in range 1..5");
    }
}

std::string_view NgramRef::get_prefix(std::string_view str, size_t char_count) {
    if (char_count >= str.length()) {
        return str;
    }
    
    // Count UTF-8 characters to properly truncate the string
    size_t byte_count = 0;
    size_t current_char_count = 0;
    
    for (size_t i = 0; i < str.length() && current_char_count < char_count; ) {
        byte_count = i + 1;
        current_char_count++;
        
        // Handle UTF-8 character boundaries
        unsigned char c = str[i];
        if ((c & 0x80) == 0) {
            // ASCII character (1 byte)
            i += 1;
        } else if ((c & 0xE0) == 0xC0) {
            // 2-byte character
            i += 2;
        } else if ((c & 0xF0) == 0xE0) {
            // 3-byte character
            i += 3;
        } else if ((c & 0xF8) == 0xF0) {
            // 4-byte character
            i += 4;
        } else {
            // Invalid UTF-8, treat as single byte
            i += 1;
        }
    }
    
    return str.substr(0, byte_count);
}

// NgramRef::Range::Iterator implementation

NgramRef::Range::Iterator::Iterator(std::string_view value, size_t char_count, bool is_end) 
    : value_(value), char_count_(char_count), is_end_(is_end) {}

NgramRef::Range::Iterator::reference NgramRef::Range::Iterator::operator*() const {
    return *(new NgramRef(value_));
}

NgramRef::Range::Iterator::pointer NgramRef::Range::Iterator::operator->() const {
    return new NgramRef(value_);
}

void NgramRef::Range::Iterator::update_to_prefix() {
    if (char_count_ <= 1) {
        is_end_ = true;
        return;
    }
    
    // Get prefix with one less character
    size_t new_char_count = char_count_ - 1;
    value_ = NgramRef::get_prefix(value_, new_char_count);
    char_count_ = new_char_count;
}

NgramRef::Range::Iterator& NgramRef::Range::Iterator::operator++() {
    if (!is_end_) {
        update_to_prefix();
    }
    return *this;
}

NgramRef::Range::Iterator NgramRef::Range::Iterator::operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

bool NgramRef::Range::Iterator::operator==(const Iterator& other) const {
    if (is_end_ && other.is_end_) return true;
    if (is_end_ || other.is_end_) return false;
    return value_ == other.value_ && char_count_ == other.char_count_;
}

bool NgramRef::Range::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

// NgramRef::Range implementation

NgramRef::Range::Range(std::string_view start_value, size_t start_char_count) 
    : start_value_(start_value), start_char_count_(start_char_count) {}

NgramRef::Range::Iterator NgramRef::Range::begin() const {
    return Iterator(start_value_, start_char_count_);
}

NgramRef::Range::Iterator NgramRef::Range::end() const {
    return Iterator(start_value_, start_char_count_, true);
}

} // namespace lingua