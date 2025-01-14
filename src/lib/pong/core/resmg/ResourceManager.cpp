#include "ResourceManager.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <stdexcept>

template<typename Resource>
bool ResourceManager<Resource>::loadResource(int id, const std::string &resource_path)
{
    if (resource_path.empty())
    {
        throw std::runtime_error("Path is empty");
    }
    if(_resource_map.find(id) != _resource_map.end())
    {
        return false;
    }

    auto new_resource = std::make_unique<Resource>();
    if (!new_resource->loadFromFile(resource_path))
    {
        throw std::runtime_error("Failed to load resource: " + resource_path);
    }
    _resource_map.emplace(id, std::move(new_resource));
    return true;
}

template<typename Resource>
Resource &ResourceManager<Resource>::getResource(int id)
{
    auto res = _resource_map.find(id);
    if (res == _resource_map.end())
    {
        throw std::runtime_error("There is no resource with given id");
    }
    return *(res->second);
}

template<typename Resource>
bool ResourceManager<Resource>::unloadResource(int id)
{
    if (_resource_map.find(id) != _resource_map.end())
    {
        _resource_map.erase(id);
        return true;
    }
    return false;
}

template class ResourceManager<sf::Font>;
template class ResourceManager<sf::Texture>;
