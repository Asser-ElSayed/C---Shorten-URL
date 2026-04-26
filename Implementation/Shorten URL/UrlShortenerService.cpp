#include "UrlShortenerService.h"


UrlShortenerService::UrlShortenerService(Validator& validator,
                                         ShortenerEngine& engine,
                                         PersistenceManager& storage)
    : validator_(validator), engine_(engine), storage_(storage) {}

std::string UrlShortenerService::ShortenUrl(const std::string& longUrl) {

     std::string cleanUrl = longUrl;

    if (!cleanUrl.empty() && cleanUrl.back() == '/') {
        cleanUrl.pop_back();
    }


    if (!validator_.ValidateLongUrl(cleanUrl)) {
        return "Error: Invalid URL format.";
    }


    std::string existingShort = storage_.FindByLongUrl(cleanUrl);
    if (!existingShort.empty()) {
        return "Error: This URL already exists in our database as: " + existingShort;
    }

    std::string slug = engine_.GenerateLinguisticSlug(cleanUrl);
    unsigned long long currentId = storage_.GetNextId();
    unsigned long long saltedId = engine_.ApplySalt(currentId);
    std::string suffix = engine_.GenerateBase62Suffix(saltedId);

    std::string shortUrl = slug + "-" + suffix;


    storage_.AddMapping(shortUrl, cleanUrl);
    storage_.IncrementCounter();
    storage_.SaveToFile();

    return shortUrl;
}

std::string UrlShortenerService::ResolveUrl(const std::string& shortUrl) {

    if (!validator_.ValidateShortUrl(shortUrl)) {
        return "Error: Malformed short link. Patterns must follow 'slug-suffix'.";
    }


    std::string originalUrl = storage_.GetOriginalUrl(shortUrl);

    if (originalUrl.empty()) {
        return "Error 404: Link not found in our database.";
    }

    return originalUrl;
}
