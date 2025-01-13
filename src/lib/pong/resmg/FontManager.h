#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Graphics/Font.hpp>

#include <memory>
#include <string>
#include <unordered_map>

class FontManager
{
public:
    /**
        Load resource from a resource.

        @return true if resource could load sucessfully otherwise false. 
                Also returns false when resource is already loaded!
     */
    bool loadResource(int id, const std::string &resource_path);
    sf::Font &getResource(int id);
private:
     std::unordered_map<int, std::unique_ptr<sf::Font>> _resource_map;
};

#endif // RESOURCEMANAGER_H
