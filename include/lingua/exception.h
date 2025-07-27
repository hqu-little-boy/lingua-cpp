#ifndef LINGUA_EXCEPTION_H_
#define LINGUA_EXCEPTION_H_

#include <exception>
#include <string>

namespace lingua {

/**
 * @brief Base exception class for all lingua-related exceptions.
 */
class LinguaException : public std::exception {
public:
    explicit LinguaException(const std::string& message) : message_(message) {}
    
    const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

/**
 * @brief Exception thrown when language model files fail to load.
 */
class ModelLoadException : public LinguaException {
public:
    explicit ModelLoadException(const std::string& message) : LinguaException(message) {}
};

/**
 * @brief Exception thrown when invalid configuration is provided.
 */
class InvalidConfigurationException : public LinguaException {
public:
    explicit InvalidConfigurationException(const std::string& message) : LinguaException(message) {}
};

/**
 * @brief Exception thrown when insufficient data is available for detection.
 */
class InsufficientDataException : public LinguaException {
public:
    explicit InsufficientDataException(const std::string& message) : LinguaException(message) {}
};

} // namespace lingua

#endif // LINGUA_EXCEPTION_H_