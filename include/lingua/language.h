#ifndef LINGUA_LANGUAGE_H_
#define LINGUA_LANGUAGE_H_

#include <string>
#include <unordered_set>

namespace lingua {

enum class Language {
  AFRIKAANS,
  ALBANIAN,
  ARABIC,
  ARMENIAN,
  AZERBAIJANI,
  BASQUE,
  BELARUSIAN,
  BENGALI,
  BOKMAL,
  BOSNIAN,
  BULGARIAN,
  CATALAN,
  CHINESE,
  CROATIAN,
  CZECH,
  DANISH,
  DUTCH,
  ENGLISH,
  ESPERANTO,
  ESTONIAN,
  FINNISH,
  FRENCH,
  GANDA,
  GEORGIAN,
  GERMAN,
  GREEK,
  GUJARATI,
  HEBREW,
  HINDI,
  HUNGARIAN,
  ICELANDIC,
  INDONESIAN,
  IRISH,
  ITALIAN,
  JAPANESE,
  KAZAKH,
  KOREAN,
  LATIN,
  LATVIAN,
  LITHUANIAN,
  MACEDONIAN,
  MALAY,
  MAORI,
  MARATHI,
  MONGOLIAN,
  NYNORSK,
  PERSIAN,
  POLISH,
  PORTUGUESE,
  PUNJABI,
  ROMANIAN,
  RUSSIAN,
  SERBIAN,
  SHONA,
  SLOVAK,
  SLOVENE,
  SOMALI,
  SOTHO,
  SPANISH,
  SWAHILI,
  SWEDISH,
  TAGALOG,
  TAMIL,
  TELUGU,
  THAI,
  TSONGA,
  TSWANA,
  TURKISH,
  UKRAINIAN,
  URDU,
  VIETNAMESE,
  WELSH,
  XHOSA,
  YORUBA,
  ZULU
};

/**
 * @brief Returns a set of all supported languages.
 */
std::unordered_set<Language> all_languages();

/**
 * @brief Returns a set of all supported spoken languages.
 */
std::unordered_set<Language> all_spoken_languages();

/**
 * @brief Returns a set of all languages supporting the Arabic script.
 */
std::unordered_set<Language> all_with_arabic_script();

/**
 * @brief Returns a set of all languages supporting the Cyrillic script.
 */
std::unordered_set<Language> all_with_cyrillic_script();

/**
 * @brief Returns a set of all languages supporting the Devanagari script.
 */
std::unordered_set<Language> all_with_devanagari_script();

/**
 * @brief Returns a set of all languages supporting the Latin script.
 */
std::unordered_set<Language> all_with_latin_script();

/**
 * @brief Returns the ISO 639-1 code of this language.
 */
std::string iso_code_639_1(Language language);

/**
 * @brief Returns the ISO 639-3 code of this language.
 */
std::string iso_code_639_3(Language language);

/**
 * @brief Returns the language associated with the ISO 639-1 code.
 */
Language from_iso_code_639_1(const std::string& iso_code);

/**
 * @brief Returns the language associated with the ISO 639-3 code.
 */
Language from_iso_code_639_3(const std::string& iso_code);

/**
 * @brief Convert Language enum to string representation.
 */
std::string to_string(Language language);

/**
 * @brief Convert string representation to Language enum.
 */
Language from_string(const std::string& language_str);

} // namespace lingua

#endif // LINGUA_LANGUAGE_H_