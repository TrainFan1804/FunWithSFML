#include "FontManager.h"

#include <SFML/Graphics/Font.hpp>

#include <stdexcept>

bool FontManager::loadResource(int id, const std::string &resource_path)
{
    if (resource_path.empty())
    {
        throw std::runtime_error("Path is empty");
    }

    auto res = _resource_map.find(id);
    if (res == _resource_map.end())
    {
        auto new_resource = std::make_unique<sf::Font>();
        if (!new_resource->loadFromFile(resource_path))
        {
            throw std::runtime_error("Failed to load resource: " + resource_path);
        }
        _resource_map.emplace(id, std::move(new_resource));
        return true;
    }
    return false;
}

sf::Font &FontManager::getResource(int id)
{
    auto res = _resource_map.find(id);
    if (res == _resource_map.end())
    {
        throw std::runtime_error("There is no resource with given id");
    }

    return *(res->second);
}
