#include "lingua/alphabet.h"
#include "lingua/language.h"
#include <utf8.h>
#include <stdexcept>
#include <algorithm>
#include <cstdint>

namespace lingua {

namespace {
  // Simple character range definitions for major scripts
  // In a full implementation, these would come from Unicode data files
  struct UnicodeRange {
    char32_t start;
    char32_t end;
  };

  // Character ranges for different scripts
  const std::unordered_map<std::string, std::vector<UnicodeRange>> script_ranges = {
    {"Latin", {{0x0041, 0x005A}, {0x0061, 0x007A}, {0x00C0, 0x00FF}}},
    {"Cyrillic", {{0x0400, 0x04FF}}},
    {"Arabic", {{0x0600, 0x06FF}}},
    {"Armenian", {{0x0530, 0x058F}}},
    {"Bengali", {{0x0980, 0x09FF}}},
    {"Devanagari", {{0x0900, 0x097F}}},
    {"Georgian", {{0x10A0, 0x10FF}}},
    {"Greek", {{0x0370, 0x03FF}}},
    {"Gujarati", {{0x0A80, 0x0AFF}}},
    {"Gurmukhi", {{0x0A00, 0x0A7F}}},
    {"Han", {{0x4E00, 0x9FFF}, {0x3400, 0x4DBF}}},
    {"Hangul", {{0xAC00, 0xD7AF}}},
    {"Hebrew", {{0x0590, 0x05FF}}},
    {"Hiragana", {{0x3040, 0x309F}}},
    {"Katakana", {{0x30A0, 0x30FF}}},
    {"Tamil", {{0x0B80, 0x0BFF}}},
    {"Telugu", {{0x0C00, 0x0C7F}}},
    {"Thai", {{0x0E00, 0x0E7F}}}
  };

  // Character set mappings
  std::unordered_map<Alphabet, CharSet> alphabet_char_sets = {
    {Alphabet::ARABIC, CharSet("Arabic")},
    {Alphabet::ARMENIAN, CharSet("Armenian")},
    {Alphabet::BENGALI, CharSet("Bengali")},
    {Alphabet::CYRILLIC, CharSet("Cyrillic")},
    {Alphabet::DEVANAGARI, CharSet("Devanagari")},
    {Alphabet::GEORGIAN, CharSet("Georgian")},
    {Alphabet::GREEK, CharSet("Greek")},
    {Alphabet::GUJARATI, CharSet("Gujarati")},
    {Alphabet::GURMUKHI, CharSet("Gurmukhi")},
    {Alphabet::HAN, CharSet("Han")},
    {Alphabet::HANGUL, CharSet("Hangul")},
    {Alphabet::HEBREW, CharSet("Hebrew")},
    {Alphabet::HIRAGANA, CharSet("Hiragana")},
    {Alphabet::KATAKANA, CharSet("Katakana")},
    {Alphabet::LATIN, CharSet("Latin")},
    {Alphabet::TAMIL, CharSet("Tamil")},
    {Alphabet::TELUGU, CharSet("Telugu")},
    {Alphabet::THAI, CharSet("Thai")}
  };

  // Languages that use exactly one alphabet
  std::unordered_map<Alphabet, Language> single_language_alphabets = {
    {Alphabet::ARMENIAN, Language::ARMENIAN},
    {Alphabet::BENGALI, Language::BENGALI},
    {Alphabet::GEORGIAN, Language::GEORGIAN},
    {Alphabet::GREEK, Language::GREEK},
    {Alphabet::GUJARATI, Language::GUJARATI},
    {Alphabet::GURMUKHI, Language::PUNJABI},
    {Alphabet::HANGUL, Language::KOREAN},
    {Alphabet::HEBREW, Language::HEBREW},
    {Alphabet::HIRAGANA, Language::JAPANESE},
    {Alphabet::KATAKANA, Language::JAPANESE},
    {Alphabet::TAMIL, Language::TAMIL},
    {Alphabet::TELUGU, Language::TELUGU},
    {Alphabet::THAI, Language::THAI}
  };
}

CharSet::CharSet(const std::vector<std::string>& char_classes) {
  initialize_from_char_classes(char_classes);
}

CharSet::CharSet(const std::string& char_class) {
  initialize_from_char_classes({char_class});
}

void CharSet::initialize_from_char_classes(const std::vector<std::string>& char_classes) {
  for (const auto& char_class : char_classes) {
    auto it = script_ranges.find(char_class);
    if (it != script_ranges.end()) {
      for (const auto& range : it->second) {
        for (char32_t c = range.start; c <= range.end; ++c) {
          characters_.insert(c);
        }
      }
    }
  }
}

bool CharSet::is_match(const std::string& text) const {
  // Convert UTF-8 string to UTF-32 for character-by-character processing
  std::vector<char32_t> utf32_chars;
  try {
    utf8::utf8to32(text.begin(), text.end(), std::back_inserter(utf32_chars));
  } catch (const utf8::invalid_utf8&) {
    return false;
  }
  
  for (char32_t ch : utf32_chars) {
    if (!is_char_match(ch)) {
      return false;
    }
  }
  return true;
}

bool CharSet::is_char_match(char32_t ch) const {
  return characters_.find(ch) != characters_.end();
}

const std::unordered_set<char32_t>& CharSet::get_characters() const {
  return characters_;
}

bool matches(Alphabet alphabet, const std::string& text) {
  return get_char_set(alphabet).is_match(text);
}

bool matches_char(Alphabet alphabet, char32_t ch) {
  return get_char_set(alphabet).is_char_match(ch);
}

std::unordered_map<Alphabet, Language> all_supporting_single_language() {
  return single_language_alphabets;
}

const CharSet& get_char_set(Alphabet alphabet) {
  auto it = alphabet_char_sets.find(alphabet);
  if (it != alphabet_char_sets.end()) {
    return it->second;
  }
  throw std::runtime_error("Character set not found for alphabet");
}

} // namespace lingua