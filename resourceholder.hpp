#ifndef RESOURCEHOLDER_HPP
#define RESOURCEHOLDER_HPP

#include <string>
#include <map>
#include <memory>

// Szablon kalsy odpowiedzialnej za ładowanie zasobów do pamięci
template <typename Resource, typename Identifier>
class ResourceHolder
{
public:

    // Funkcja ładująca zasób do pamięci
    void load(Identifier id, const std::string &resourceName);

    // Funkcja zwracająca referencję do zasobu
    Resource & get(Identifier id);


    // Funkcja zwracająca referencję do zasobu ( wersja 'const' )
    const Resource & get(Identifier id) const;

private:

    std::map<Identifier, std::unique_ptr<Resource>> resourceMap;


};

// Funkcja ładująca zasób do pamięci
template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string &resourceName)
{
    std::unique_ptr<Resource> resource(new Resource);
    resource->loadFromFile(resourceName);
    resourceMap.insert(std::make_pair(id, std::move(resource)));
}

// Funkcja zwracająca referencję do zasobu
template <typename Resource, typename Identifier>
Resource & ResourceHolder<Resource, Identifier>::get(Identifier id)
{
    auto found = resourceMap.find(id);
    return *found->second;
}

// Funkcja zwracająca referencję do zasobu ( wersja 'const' )
template <typename Resource, typename Identifier>
const Resource & ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
    auto found = resourceMap.find(id);
    return *found->second;
}

#endif // RESOURCEHOLDER_HPP
