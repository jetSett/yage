#include "Resource.hpp"
#include "ResourceManager.hpp"
#include "../Memory/NewInc.hpp"

Resource::Resource(const std::string& name) : _name(name), _refCount(1)
{
}

Resource::~Resource()
{
    if(_refCount == 0)
        ResourceManager::getInstance().remove(_name);
}

int Resource::getRefCount(){
    return _refCount;
}

int Resource::release(){
    _refCount--;
    if(_refCount == 0)
        delete this;
    return _refCount;
}
