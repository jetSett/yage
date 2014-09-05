#ifndef RESSOURCEMANAGER_H
#define RESSOURCEMANAGER_H

#include <string>
#include <map>
#include "../Utils/Singleton.hpp"
#include "../Utils/Exceptions.hpp"
#include "Resource.hpp"

class ResourceManager : public Singleton<ResourceManager>
{
    friend class Singleton<ResourceManager>;
    public:
        template<class T>
        T* get(const std::string& name) const{
            RessourcesMap::const_iterator it = _resources.find(name);
            if(it != _resources.end()){
                it->second->addRef();
                return static_cast<T*>(it->second);
            }else{
                return nullptr;
            }
        }

        void add(const std::string& name, Resource* res);

        void remove(const std::string& name);

        void clear();

        bool exist(const std::string& name) const{
            return _resources.find(name) != _resources.end();
        }

    private:
        ResourceManager(){}
        ~ResourceManager();
        typedef std::map<std::string, Resource*> RessourcesMap;
        RessourcesMap _resources;
};

#endif // RESSOURCEMANAGER_H
