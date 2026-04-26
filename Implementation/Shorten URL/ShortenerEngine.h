#ifndef SHORTENER_ENGINE_H
#define SHORTENER_ENGINE_H

#include <string>


class ShortenerEngine {
public:
    ShortenerEngine();


    std::string GenerateLinguisticSlug(const std::string& url) const;
    std::string GenerateBase62Suffix(unsigned long long saltedId) const;
    unsigned long long ApplySalt(unsigned long long counter) const;

private:

    std::string RemoveVowels(const std::string& input) const;


    std::string base62Alphabet_;
    unsigned long long saltPrime_;
};

#endif
