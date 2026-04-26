#include "Validator.h"
#include "ShortenerEngine.h"
#include "PersistenceManager.h"
#include "UrlShortenerService.h"
#include "CliApp.h"
#include <iostream>


int main() {
    try {

        Validator validator;
        ShortenerEngine engine;

        PersistenceManager storage("nexus_data.txt");

        if (!storage.LoadFromFile()) {
            std::cout << " [!] Starting fresh session (No existing database found).\n";
        } else {
            std::cout << " [*] Database loaded successfully.\n";
        }

        UrlShortenerService service(validator, engine, storage);


        CliApp app(service);


        app.Start();

    } catch (const std::exception& e) {

        std::cerr << " [FATAL ERROR] System encountered an issue: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
