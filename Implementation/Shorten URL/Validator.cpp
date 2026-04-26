#include "Validator.h"

Validator::Validator() {

    longUrlPattern_ = std::regex(R"(^https?://[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}.*$)");

    shortUrlPattern_ = std::regex(R"(^[a-zA-Z0-9./]+-[a-zA-Z0-9]+$)");

}

bool Validator::ValidateLongUrl(const std::string& url) const {

    if (url.find(' ') != std::string::npos) {
        return false;
    }

    return std::regex_match(url, longUrlPattern_);
}

bool Validator::ValidateShortUrl(const std::string& url) const {

    if (url.length() < 3 || url.length() > 50) {
        return false;
    }

    return std::regex_match(url, shortUrlPattern_);
}
