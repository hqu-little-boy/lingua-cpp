#ifndef LINGUA_ALPHABET_H_
#define LINGUA_ALPHABET_H_

#include "language.h"
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>

namespace lingua {

/**
 * @brief Enum representing different writing systems/alphabet scripts.
 */
enum class Alphabet {
  ARABIC,
  ARMENIAN,
  BENGALI,
  CYRILLIC,
  DEVANAGARI,
  GEORGIAN,
  GREEK,
  GUJARATI,
  GURMUKHI,
  HAN,
  HANGUL,
  HEBREW,
  HIRAGANA,
  KATAKANA,
  LATIN,
  TAMIL,
  TELUGU,
  THAI
};

/**
 * @brief Class representing a character set for an alphabet.
 * 
 * This class stores the characters belonging to a specific alphabet/script
 * and provides methods to check if text or characters match this alphabet.
 */
class CharSet {
public:
  /**
   * @brief Construct a CharSet from character classes.
   * 
   * @param char_classes Vector of character class names (e.g., "Latin", "Cyrillic")
   */
  explicit CharSet(const std::vector<std::string>& char_classes);
  
  /**
   * @brief Construct a CharSet from a single character class.
   * 
   * @param char_class The character class name
   */
  explicit CharSet(const std::string& char_class);
  
  /**
   * @brief Check if the entire text matches this character set.
   * 
   * @param text The text to check
   * @return true if all characters in the text belong to this character set
   * @return false otherwise
   */
  bool is_match(const std::string& text) const;
  
  /**
   * @brief Check if a single character matches this character set.
   * 
   * @param ch The character to check
   * @return true if the character belongs to this character set
   * @return false otherwise
   */
  bool is_char_match(char32_t ch) const;
  
  /**
   * @brief Get the set of characters in this character set.
   * 
   * @return const std::unordered_set<char32_t>& The character set
   */
  const std::unordered_set<char32_t>& get_characters() const;

private:
  std::unordered_set<char32_t> characters_;
  
  void initialize_from_char_classes(const std::vector<std::string>& char_classes);
};

/**
 * @brief Check if the text matches this alphabet.
 * 
 * @param alphabet The alphabet to check against
 * @param text The text to check
 * @return true if all characters in the text belong to this alphabet
 * @return false otherwise
 */
bool matches(Alphabet alphabet, const std::string& text);

/**
 * @brief Check if a single character matches this alphabet.
 * 
 * @param alphabet The alphabet to check against
 * @param ch The character to check
 * @return true if the character belongs to this alphabet
 * @return false otherwise
 */
bool matches_char(Alphabet alphabet, char32_t ch);

/**
 * @brief Get all alphabets that support exactly one language.
 * 
 * @return std::unordered_map<Alphabet, Language> Map of alphabets to their single supported language
 */
std::unordered_map<Alphabet, Language> all_supporting_single_language();

/**
 * @brief Get the character set for an alphabet.
 * 
 * @param alphabet The alphabet
 * @return const CharSet& The character set for the alphabet
 */
const CharSet& get_char_set(Alphabet alphabet);

} // namespace lingua

#endif // LINGUA_ALPHABET_H_