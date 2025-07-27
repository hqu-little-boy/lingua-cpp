#include "lingua/language.h"

#include <algorithm>
#include <stdexcept>

namespace lingua {

std::unordered_set<Language> all_languages() {
    return {
        Language::AFRIKAANS, Language::ALBANIAN, Language::ARABIC, Language::ARMENIAN,
        Language::AZERBAIJANI, Language::BASQUE, Language::BELARUSIAN, Language::BENGALI,
        Language::BOKMAL, Language::BOSNIAN, Language::BULGARIAN, Language::CATALAN,
        Language::CHINESE, Language::CROATIAN, Language::CZECH, Language::DANISH,
        Language::DUTCH, Language::ENGLISH, Language::ESPERANTO, Language::ESTONIAN,
        Language::FINNISH, Language::FRENCH, Language::GANDA, Language::GEORGIAN,
        Language::GERMAN, Language::GREEK, Language::GUJARATI, Language::HEBREW,
        Language::HINDI, Language::HUNGARIAN, Language::ICELANDIC, Language::INDONESIAN,
        Language::IRISH, Language::ITALIAN, Language::JAPANESE, Language::KAZAKH,
        Language::KOREAN, Language::LATIN, Language::LATVIAN, Language::LITHUANIAN,
        Language::MACEDONIAN, Language::MALAY, Language::MAORI, Language::MARATHI,
        Language::MONGOLIAN, Language::NYNORSK, Language::PERSIAN, Language::POLISH,
        Language::PORTUGUESE, Language::PUNJABI, Language::ROMANIAN, Language::RUSSIAN,
        Language::SERBIAN, Language::SHONA, Language::SLOVAK, Language::SLOVENE,
        Language::SOMALI, Language::SOTHO, Language::SPANISH, Language::SWAHILI,
        Language::SWEDISH, Language::TAGALOG, Language::TAMIL, Language::TELUGU,
        Language::THAI, Language::TSONGA, Language::TSWANA, Language::TURKISH,
        Language::UKRAINIAN, Language::URDU, Language::VIETNAMESE, Language::WELSH,
        Language::XHOSA, Language::YORUBA, Language::ZULU
    };
}

std::unordered_set<Language> all_spoken_languages() {
    auto languages = all_languages();
    // Remove Latin if it exists
    languages.erase(Language::LATIN);
    return languages;
}

std::unordered_set<Language> all_with_arabic_script() {
    return {Language::ARABIC, Language::PERSIAN, Language::URDU};
}

std::unordered_set<Language> all_with_cyrillic_script() {
    return {
        Language::BELARUSIAN, Language::BULGARIAN, Language::KAZAKH,
        Language::MACEDONIAN, Language::MONGOLIAN, Language::RUSSIAN,
        Language::SERBIAN, Language::UKRAINIAN
    };
}

std::unordered_set<Language> all_with_devanagari_script() {
    return {Language::HINDI, Language::MARATHI};
}

std::unordered_set<Language> all_with_latin_script() {
    return {
        Language::AFRIKAANS, Language::ALBANIAN, Language::AZERBAIJANI,
        Language::BASQUE, Language::BOKMAL, Language::BOSNIAN,
        Language::CATALAN, Language::CROATIAN, Language::CZECH,
        Language::DANISH, Language::DUTCH, Language::ENGLISH,
        Language::ESPERANTO, Language::ESTONIAN, Language::FINNISH,
        Language::FRENCH, Language::GANDA, Language::GERMAN,
        Language::HUNGARIAN, Language::ICELANDIC, Language::INDONESIAN,
        Language::IRISH, Language::ITALIAN, Language::LATIN,
        Language::LATVIAN, Language::LITHUANIAN, Language::MALAY,
        Language::MAORI, Language::NYNORSK, Language::POLISH,
        Language::PORTUGUESE, Language::ROMANIAN, Language::SHONA,
        Language::SLOVAK, Language::SLOVENE, Language::SOMALI,
        Language::SOTHO, Language::SPANISH, Language::SWAHILI,
        Language::SWEDISH, Language::TAGALOG, Language::TSONGA,
        Language::TSWANA, Language::TURKISH, Language::VIETNAMESE,
        Language::WELSH, Language::XHOSA, Language::YORUBA,
        Language::ZULU
    };
}

std::string iso_code_639_1(Language language) {
    switch (language) {
        case Language::AFRIKAANS: return "af";
        case Language::ALBANIAN: return "sq";
        case Language::ARABIC: return "ar";
        case Language::ARMENIAN: return "hy";
        case Language::AZERBAIJANI: return "az";
        case Language::BASQUE: return "eu";
        case Language::BELARUSIAN: return "be";
        case Language::BENGALI: return "bn";
        case Language::BOKMAL: return "nb";
        case Language::BOSNIAN: return "bs";
        case Language::BULGARIAN: return "bg";
        case Language::CATALAN: return "ca";
        case Language::CHINESE: return "zh";
        case Language::CROATIAN: return "hr";
        case Language::CZECH: return "cs";
        case Language::DANISH: return "da";
        case Language::DUTCH: return "nl";
        case Language::ENGLISH: return "en";
        case Language::ESPERANTO: return "eo";
        case Language::ESTONIAN: return "et";
        case Language::FINNISH: return "fi";
        case Language::FRENCH: return "fr";
        case Language::GANDA: return "lg";
        case Language::GEORGIAN: return "ka";
        case Language::GERMAN: return "de";
        case Language::GREEK: return "el";
        case Language::GUJARATI: return "gu";
        case Language::HEBREW: return "he";
        case Language::HINDI: return "hi";
        case Language::HUNGARIAN: return "hu";
        case Language::ICELANDIC: return "is";
        case Language::INDONESIAN: return "id";
        case Language::IRISH: return "ga";
        case Language::ITALIAN: return "it";
        case Language::JAPANESE: return "ja";
        case Language::KAZAKH: return "kk";
        case Language::KOREAN: return "ko";
        case Language::LATIN: return "la";
        case Language::LATVIAN: return "lv";
        case Language::LITHUANIAN: return "lt";
        case Language::MACEDONIAN: return "mk";
        case Language::MALAY: return "ms";
        case Language::MAORI: return "mi";
        case Language::MARATHI: return "mr";
        case Language::MONGOLIAN: return "mn";
        case Language::NYNORSK: return "nn";
        case Language::PERSIAN: return "fa";
        case Language::POLISH: return "pl";
        case Language::PORTUGUESE: return "pt";
        case Language::PUNJABI: return "pa";
        case Language::ROMANIAN: return "ro";
        case Language::RUSSIAN: return "ru";
        case Language::SERBIAN: return "sr";
        case Language::SHONA: return "sn";
        case Language::SLOVAK: return "sk";
        case Language::SLOVENE: return "sl";
        case Language::SOMALI: return "so";
        case Language::SOTHO: return "st";
        case Language::SPANISH: return "es";
        case Language::SWAHILI: return "sw";
        case Language::SWEDISH: return "sv";
        case Language::TAGALOG: return "tl";
        case Language::TAMIL: return "ta";
        case Language::TELUGU: return "te";
        case Language::THAI: return "th";
        case Language::TSONGA: return "ts";
        case Language::TSWANA: return "tn";
        case Language::TURKISH: return "tr";
        case Language::UKRAINIAN: return "uk";
        case Language::URDU: return "ur";
        case Language::VIETNAMESE: return "vi";
        case Language::WELSH: return "cy";
        case Language::XHOSA: return "xh";
        case Language::YORUBA: return "yo";
        case Language::ZULU: return "zu";
    }
    return ""; // Should never reach here
}

std::string iso_code_639_3(Language language) {
    switch (language) {
        case Language::AFRIKAANS: return "afr";
        case Language::ALBANIAN: return "sqi";
        case Language::ARABIC: return "ara";
        case Language::ARMENIAN: return "hye";
        case Language::AZERBAIJANI: return "aze";
        case Language::BASQUE: return "eus";
        case Language::BELARUSIAN: return "bel";
        case Language::BENGALI: return "ben";
        case Language::BOKMAL: return "nob";
        case Language::BOSNIAN: return "bos";
        case Language::BULGARIAN: return "bul";
        case Language::CATALAN: return "cat";
        case Language::CHINESE: return "zho";
        case Language::CROATIAN: return "hrv";
        case Language::CZECH: return "ces";
        case Language::DANISH: return "dan";
        case Language::DUTCH: return "nld";
        case Language::ENGLISH: return "eng";
        case Language::ESPERANTO: return "epo";
        case Language::ESTONIAN: return "est";
        case Language::FINNISH: return "fin";
        case Language::FRENCH: return "fra";
        case Language::GANDA: return "lug";
        case Language::GEORGIAN: return "kat";
        case Language::GERMAN: return "deu";
        case Language::GREEK: return "ell";
        case Language::GUJARATI: return "guj";
        case Language::HEBREW: return "heb";
        case Language::HINDI: return "hin";
        case Language::HUNGARIAN: return "hun";
        case Language::ICELANDIC: return "isl";
        case Language::INDONESIAN: return "ind";
        case Language::IRISH: return "gle";
        case Language::ITALIAN: return "ita";
        case Language::JAPANESE: return "jpn";
        case Language::KAZAKH: return "kaz";
        case Language::KOREAN: return "kor";
        case Language::LATIN: return "lat";
        case Language::LATVIAN: return "lav";
        case Language::LITHUANIAN: return "lit";
        case Language::MACEDONIAN: return "mkd";
        case Language::MALAY: return "msa";
        case Language::MAORI: return "mri";
        case Language::MARATHI: return "mar";
        case Language::MONGOLIAN: return "mon";
        case Language::NYNORSK: return "nno";
        case Language::PERSIAN: return "fas";
        case Language::POLISH: return "pol";
        case Language::PORTUGUESE: return "por";
        case Language::PUNJABI: return "pan";
        case Language::ROMANIAN: return "ron";
        case Language::RUSSIAN: return "rus";
        case Language::SERBIAN: return "srp";
        case Language::SHONA: return "sna";
        case Language::SLOVAK: return "slk";
        case Language::SLOVENE: return "slv";
        case Language::SOMALI: return "som";
        case Language::SOTHO: return "sot";
        case Language::SPANISH: return "spa";
        case Language::SWAHILI: return "swa";
        case Language::SWEDISH: return "swe";
        case Language::TAGALOG: return "tgl";
        case Language::TAMIL: return "tam";
        case Language::TELUGU: return "tel";
        case Language::THAI: return "tha";
        case Language::TSONGA: return "tso";
        case Language::TSWANA: return "tsn";
        case Language::TURKISH: return "tur";
        case Language::UKRAINIAN: return "ukr";
        case Language::URDU: return "urd";
        case Language::VIETNAMESE: return "vie";
        case Language::WELSH: return "cym";
        case Language::XHOSA: return "xho";
        case Language::YORUBA: return "yor";
        case Language::ZULU: return "zul";
    }
    return ""; // Should never reach here
}

Language from_iso_code_639_1(const std::string& iso_code) {
    // Convert to lowercase for case-insensitive comparison
    std::string code = iso_code;
    std::transform(code.begin(), code.end(), code.begin(), ::tolower);
    
    for (const auto& lang : all_languages()) {
        if (iso_code_639_1(lang) == code) {
            return lang;
        }
    }
    
    throw std::invalid_argument("Invalid ISO 639-1 code: " + iso_code);
}

Language from_iso_code_639_3(const std::string& iso_code) {
    // Convert to lowercase for case-insensitive comparison
    std::string code = iso_code;
    std::transform(code.begin(), code.end(), code.begin(), ::tolower);
    
    for (const auto& lang : all_languages()) {
        if (iso_code_639_3(lang) == code) {
            return lang;
        }
    }
    
    throw std::invalid_argument("Invalid ISO 639-3 code: " + iso_code);
}

std::string to_string(Language language) {
    switch (language) {
        case Language::AFRIKAANS: return "AFRIKAANS";
        case Language::ALBANIAN: return "ALBANIAN";
        case Language::ARABIC: return "ARABIC";
        case Language::ARMENIAN: return "ARMENIAN";
        case Language::AZERBAIJANI: return "AZERBAIJANI";
        case Language::BASQUE: return "BASQUE";
        case Language::BELARUSIAN: return "BELARUSIAN";
        case Language::BENGALI: return "BENGALI";
        case Language::BOKMAL: return "BOKMAL";
        case Language::BOSNIAN: return "BOSNIAN";
        case Language::BULGARIAN: return "BULGARIAN";
        case Language::CATALAN: return "CATALAN";
        case Language::CHINESE: return "CHINESE";
        case Language::CROATIAN: return "CROATIAN";
        case Language::CZECH: return "CZECH";
        case Language::DANISH: return "DANISH";
        case Language::DUTCH: return "DUTCH";
        case Language::ENGLISH: return "ENGLISH";
        case Language::ESPERANTO: return "ESPERANTO";
        case Language::ESTONIAN: return "ESTONIAN";
        case Language::FINNISH: return "FINNISH";
        case Language::FRENCH: return "FRENCH";
        case Language::GANDA: return "GANDA";
        case Language::GEORGIAN: return "GEORGIAN";
        case Language::GERMAN: return "GERMAN";
        case Language::GREEK: return "GREEK";
        case Language::GUJARATI: return "GUJARATI";
        case Language::HEBREW: return "HEBREW";
        case Language::HINDI: return "HINDI";
        case Language::HUNGARIAN: return "HUNGARIAN";
        case Language::ICELANDIC: return "ICELANDIC";
        case Language::INDONESIAN: return "INDONESIAN";
        case Language::IRISH: return "IRISH";
        case Language::ITALIAN: return "ITALIAN";
        case Language::JAPANESE: return "JAPANESE";
        case Language::KAZAKH: return "KAZAKH";
        case Language::KOREAN: return "KOREAN";
        case Language::LATIN: return "LATIN";
        case Language::LATVIAN: return "LATVIAN";
        case Language::LITHUANIAN: return "LITHUANIAN";
        case Language::MACEDONIAN: return "MACEDONIAN";
        case Language::MALAY: return "MALAY";
        case Language::MAORI: return "MAORI";
        case Language::MARATHI: return "MARATHI";
        case Language::MONGOLIAN: return "MONGOLIAN";
        case Language::NYNORSK: return "NYNORSK";
        case Language::PERSIAN: return "PERSIAN";
        case Language::POLISH: return "POLISH";
        case Language::PORTUGUESE: return "PORTUGUESE";
        case Language::PUNJABI: return "PUNJABI";
        case Language::ROMANIAN: return "ROMANIAN";
        case Language::RUSSIAN: return "RUSSIAN";
        case Language::SERBIAN: return "SERBIAN";
        case Language::SHONA: return "SHONA";
        case Language::SLOVAK: return "SLOVAK";
        case Language::SLOVENE: return "SLOVENE";
        case Language::SOMALI: return "SOMALI";
        case Language::SOTHO: return "SOTHO";
        case Language::SPANISH: return "SPANISH";
        case Language::SWAHILI: return "SWAHILI";
        case Language::SWEDISH: return "SWEDISH";
        case Language::TAGALOG: return "TAGALOG";
        case Language::TAMIL: return "TAMIL";
        case Language::TELUGU: return "TELUGU";
        case Language::THAI: return "THAI";
        case Language::TSONGA: return "TSONGA";
        case Language::TSWANA: return "TSWANA";
        case Language::TURKISH: return "TURKISH";
        case Language::UKRAINIAN: return "UKRAINIAN";
        case Language::URDU: return "URDU";
        case Language::VIETNAMESE: return "VIETNAMESE";
        case Language::WELSH: return "WELSH";
        case Language::XHOSA: return "XHOSA";
        case Language::YORUBA: return "YORUBA";
        case Language::ZULU: return "ZULU";
    }
    return ""; // Should never reach here
}

Language from_string(const std::string& language_str) {
    // Convert to uppercase for case-insensitive comparison
    std::string str = language_str;
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    
    for (const auto& lang : all_languages()) {
        if (to_string(lang) == str) {
            return lang;
        }
    }
    
    throw std::invalid_argument("Invalid language string: " + language_str);
}

} // namespace lingua