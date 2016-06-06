#ifndef RESOURCE_HOLDER_HPP
#define RESOURCE_HOLDER_HPP

#include <string>
#include <map>
#include <memory>

// Szablon kalsy odpowiedzialnej za ładowanie zasobów do pamięci
template <typename Resource>
class ResourceHolder
{
public:

    // Funkcja ładująca zasób do pamięci
    void load(const std::string &resourceName, const std::string &pathToResource);

    // Funkcja zwracająca referencję do zasobu
    Resource & get(const std::string &resourceName);


    // Funkcja zwracająca referencję do zasobu ( wersja 'const' )
    const Resource & get(const std::string &resourceName) const;

private:

    std::map<std::string, std::unique_ptr<Resource>> resourceMap;


};

// Funkcja ładująca zasób do pamięci
template <typename Resource>
void ResourceHolder<Resource>::load(const std::string &resourceName, const std::string &pathToResource)
{
    std::unique_ptr<Resource> resource(new Resource);
    resource->loadFromFile(pathToResource);
    resourceMap.insert(std::make_pair(resourceName, std::move(resource)));
}

// Funkcja zwracająca referencję do zasobu
template <typename Resource>
Resource & ResourceHolder<Resource>::get(const std::string &resourceName)
{
    auto found = resourceMap.find(resourceName);
    return *found->second;
}

// Funkcja zwracająca referencję do zasobu ( wersja 'const' )
template <typename Resource>
const Resource & ResourceHolder<Resource>::get(const std::string &resourceName) const
{
    auto found = resourceMap.find(resourceName);
    return *found->second;
}

#endif // RESOURCE_HOLDER_HPP
