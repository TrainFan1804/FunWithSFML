#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

template<typename Resource>
class ResourceManager
{
public:
    /**
        Load resource from a resource.

        @return true if resource could load sucessfully otherwise false. 
                Also returns false when resource is already loaded!
     */
    bool loadResource(int id, const std::string &resource_path);
    Resource &getResource(int id);
    /**
        Unload resource from memory.

        @return true if resource could be reloaded otherwise false.
                Only returns false when there is no resource with given id
     */
    bool unloadResource(int id);
private:
     std::unordered_map<int, std::unique_ptr<Resource>> _resource_map;
};

#endif // RESOURCEMANAGER_H
