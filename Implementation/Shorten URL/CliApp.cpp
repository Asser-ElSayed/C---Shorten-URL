#include "CliApp.h"
#include <iostream>
#include <limits>

CliApp::CliApp(UrlShortenerService& service)
    : urlService_(service), isRunning_(true) {}

void CliApp::Start() {
    DisplayHeader();

    while (isRunning_) {
        DisplayMenu();
        int choice;
        std::cout << " [>] Select an option: ";

        if (!(std::cin >> choice)) {
            DisplayError("Invalid input. Please enter a number.");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                HandleShortenRequest();
                break;
            case 2:
                HandleResolveRequest();
                break;
            case 3:
                isRunning_ = false;
                break;
            default:
                DisplayError("Option not recognized. Try again.");
        }
    }

    DisplayFooter();
}

void CliApp::DisplayHeader() const {
    std::cout << "==============================================\n";
    std::cout << "        URL SHORTENER SERVICE v1.0       \n";
    std::cout << "         \n";
    std::cout << "==============================================\n";
}

void CliApp::DisplayMenu() const {
    std::cout << "\n MAIN MENU\n";
    std::cout << " [1] Shorten a new Long URL\n";
    std::cout << " [2] Resolve a Short Link\n";
    std::cout << " [3] Exit Application\n";
    std::cout << "----------------------------------------------\n";
}

void CliApp::HandleShortenRequest() {
    std::string longUrl;
    std::cout << "\n [SHORTEN] Enter Long URL: ";
    std::cin >> longUrl;

    std::string result = urlService_.ShortenUrl(longUrl);


    if (result.find("Error") == 0) {
        DisplayError(result);
    } else {
        DisplaySuccess("Link generated successfully!");
        std::cout << " [+] Shortened Address: " << result << "\n";
    }
}

void CliApp::HandleResolveRequest() {
    std::string shortUrl;
    std::cout << "\n [RESOLVE] Enter Short Link : ";
    std::cin >> shortUrl;

    std::string result = urlService_.ResolveUrl(shortUrl);

    if (result.find("Error") == 0) {
        DisplayError(result);
    } else {
        DisplaySuccess("Destination Found!");
        std::cout << " [→] Redirecting to: " << result << "\n";
    }
}

void CliApp::DisplayError(const std::string& message) const {
    std::cout << "\n [!] " << message << "\n";
}

void CliApp::DisplaySuccess(const std::string& message) const {
    std::cout << "\n [*] " << message << "\n";
}

void CliApp::DisplayFooter() const {
    std::cout << "\n==============================================\n";
    std::cout << "     Thank you for using Shorten Service.       \n";
    std::cout << "        Session Closed Successfully.          \n";
    std::cout << "==============================================\n";
}
