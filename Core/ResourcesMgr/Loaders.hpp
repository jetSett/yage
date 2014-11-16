#ifndef LOADER_HPP
#define LOADER_HPP

#include <string>
#include <iostream>
#include <vector>

#include "../Utils/Exceptions.hpp"
#include "Resource.hpp"
#include "ResourceManager.hpp"

class Image;
class Model;
template<class T>
class Loader
{
    public:
        virtual ~Loader(){}
        virtual T* load(const std::string& name){
            T* res = nullptr;
            if(ResourceManager::getInstance().get<T>(name) == nullptr){
                res = loadFromFile(name);
                ResourceManager::getInstance().add(name, res);
            }else{
                res = ResourceManager::getInstance().get<T>(name);
            }
            return res;
        }

        virtual T* loadFromFile(const std::string&){
            throw UnemplementedFunction("Loader::loadFromFile");
        }
        virtual void saveToFile(const T*, const std::string&){
            throw UnemplementedFunction("Loader::saveToFile");
        }
    protected:
        Loader(){}
};

template<>
Image* Loader<Image>::load(const std::string& name);
//template<>
//Shader* Loader<Shader>::load(const std::string& name);


#endif // LOADER_HPP
