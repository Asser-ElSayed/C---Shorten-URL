#include "PersistenceManager.h"
#include <fstream>
#include <sstream>


PersistenceManager::PersistenceManager(const std::string& filePath)
    : globalCounter_(1000), filePath_(filePath) {
}

bool PersistenceManager::LoadFromFile() {
   std::ifstream file(filePath_);
    if (!file.is_open()) return false;

    std::string line;
    if (std::getline(file, line)) {

        if (!line.empty() && line.back() == '\r') line.pop_back();
        std::stringstream ss(line);
        ss >> globalCounter_;
    }

    while (std::getline(file, line)) {

        if (!line.empty() && line.back() == '\r') line.pop_back();

        size_t delimiterPos = line.find('|');
        if (delimiterPos != std::string::npos) {
            std::string shortUrl = line.substr(0, delimiterPos);
            std::string longUrl = line.substr(delimiterPos + 1);
            urlMap_[shortUrl] = longUrl;
        }
    }
    file.close();
    return true;
}

void PersistenceManager::SaveToFile() const {
    std::ofstream file(filePath_, std::ios::trunc);
    if (!file.is_open()) return;

    file << globalCounter_ << "\n";

    for (const auto& pair : urlMap_) {
        file << pair.first << "|" << pair.second << "\n";
    }

    file.close();
}

void PersistenceManager::AddMapping(const std::string& shortUrl, const std::string& longUrl) {
    urlMap_[shortUrl] = longUrl;
}

std::string PersistenceManager::GetOriginalUrl(const std::string& shortUrl) const {
    auto it = urlMap_.find(shortUrl);
    if (it != urlMap_.end()) {
        return it->second;
    }
    return "";
}

std::string PersistenceManager::FindByLongUrl(const std::string& longUrl) const {
    for (const auto& pair : urlMap_) {
        if (pair.second == longUrl) {
            return pair.first;
        }
    }
    return "";
}

unsigned long long PersistenceManager::GetNextId() const {
    return globalCounter_;
}

void PersistenceManager::IncrementCounter() {
    globalCounter_++;
}
