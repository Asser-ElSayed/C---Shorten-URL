#include "ShortenerEngine.h"
#include <algorithm>

ShortenerEngine::ShortenerEngine() {
    base62Alphabet_ = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    saltPrime_ = 1588633;
}

std::string ShortenerEngine::GenerateLinguisticSlug(const std::string& url) const {

    std::string domain = url;
    size_t pos = domain.find("://");
    if (pos != std::string::npos) {
        domain = domain.substr(pos + 3);
    }


    if (domain.find("www.") == 0) {
        domain = domain.substr(4);
    }


    std::string slug = RemoveVowels(domain);


    if (slug.length() > 8) {
        slug = slug.substr(0, 8);
    }

    return slug;
}

unsigned long long ShortenerEngine::ApplySalt(unsigned long long counter) const {

    return counter * saltPrime_;
}

std::string ShortenerEngine::GenerateBase62Suffix(unsigned long long saltedId) const {
    if (saltedId == 0) return "0";

    std::string suffix = "";
    unsigned long long tempId = saltedId;


    while (tempId > 0) {
        suffix += base62Alphabet_[tempId % 62];
        tempId /= 62;
    }


    std::reverse(suffix.begin(), suffix.end());

    return suffix;
}

std::string ShortenerEngine::RemoveVowels(const std::string& input) const {
    std::string result = "";
    std::string vowels = "aeiouAEIOU";

    for (char c : input) {

        if (vowels.find(c) == std::string::npos) {
            result += c;
        }
    }
    return result;
}
