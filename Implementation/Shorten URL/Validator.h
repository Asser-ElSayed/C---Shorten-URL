#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <regex>


class Validator {
public:
    Validator();


    bool ValidateLongUrl(const std::string& url) const;
    bool ValidateShortUrl(const std::string& url) const;

private:

    std::regex longUrlPattern_;
    std::regex shortUrlPattern_;
};

#endif
