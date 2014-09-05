#include "ResourceManager.hpp"
#include "../Utils/Logger.hpp"
#include "../Memory/NewInc.hpp"

void ResourceManager::add(const std::string& name, Resource* res){
    Logger::Log() << "Adding resource : " + name;
    if(exist(name))
        throw ResourceError("Resource already exist", name);
    _resources[name] = res;
}

void ResourceManager::remove(const std::string& name){
    Logger::Log() << "Removing resource : " + name;
    if(exist(name)){
        _resources.erase(name);
    }else{
        throw ResourceError("Resource don't exist", name);
    }
}

void ResourceManager::clear(){
    _resources.clear();
}

ResourceManager::~ResourceManager(){
    for(auto p : _resources){
        remove(p.first);
    }
    clear();
}
