#ifndef URLSHORTENERSERVICE_H
#define URLSHORTENERSERVICE_H

#include <string>
#include "Validator.h"
#include "ShortenerEngine.h"
#include "PersistenceManager.h"



class UrlShortenerService
{
   public:

    UrlShortenerService(Validator& validator,
                        ShortenerEngine& engine,
                        PersistenceManager& storage);


    std::string ShortenUrl(const std::string& longUrl);
    std::string ResolveUrl(const std::string& shortUrl);

private:

    Validator& validator_;
    ShortenerEngine& engine_;
    PersistenceManager& storage_;
};

#endif
