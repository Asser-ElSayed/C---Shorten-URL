#ifndef CLIAPP_H
#define CLIAPP_H
#include "UrlShortenerService.h"
#include <string>



class CliApp
{
    public:

    explicit CliApp(UrlShortenerService& service);

    void Start();

private:

    void DisplayHeader() const;
    void DisplayMenu() const;
    void HandleShortenRequest();
    void HandleResolveRequest();
    void DisplayFooter() const;
    void DisplayError(const std::string& message) const;
    void DisplaySuccess(const std::string& message) const;


    UrlShortenerService& urlService_;
    bool isRunning_;

};

#endif
