#ifndef PERSISTENCE_MANAGER_H
#define PERSISTENCE_MANAGER_H

#include <string>
#include <unordered_map>

class PersistenceManager {
public:
    PersistenceManager(const std::string& filePath);

    bool LoadFromFile();
    void SaveToFile() const;

    void AddMapping(const std::string& shortUrl, const std::string& longUrl);
    std::string GetOriginalUrl(const std::string& shortUrl) const;
    std::string FindByLongUrl(const std::string& longUrl) const;

    unsigned long long GetNextId() const;
    void IncrementCounter();

private:
    std::unordered_map<std::string, std::string> urlMap_;
    unsigned long long globalCounter_;
    std::string filePath_;
};

#endif
