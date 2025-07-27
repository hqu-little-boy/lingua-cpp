#ifndef LINGUA_DETECTION_RESULT_H_
#define LINGUA_DETECTION_RESULT_H_

#include "language.h"

#include <cstddef>

namespace lingua {

/**
 * @brief This class describes a contiguous single-language
 * text section within a possibly mixed-language text.
 */
class DetectionResult {
public:
    /**
     * @brief Constructs a DetectionResult.
     * @param language The detected language
     * @param start_index The start index of the identified single-language substring
     * @param end_index The end index of the identified single-language substring
     * @param word_count The number of words in the identified substring
     */
    DetectionResult(Language language, size_t start_index, size_t end_index, size_t word_count)
        : language_(language), start_index_(start_index), end_index_(end_index), word_count_(word_count) {}

    /**
     * @brief Returns the detected language of the identified single-language substring.
     */
    Language language() const { return language_; }

    /**
     * @brief Returns the start index of the identified single-language substring.
     */
    size_t start_index() const { return start_index_; }

    /**
     * @brief Returns the end index of the identified single-language substring.
     */
    size_t end_index() const { return end_index_; }

    /**
     * @brief Returns the number of words being part of the identified
     * single-language substring.
     */
    size_t word_count() const { return word_count_; }

private:
    Language language_;
    size_t start_index_;
    size_t end_index_;
    size_t word_count_;
};

} // namespace lingua

#endif // LINGUA_DETECTION_RESULT_H_