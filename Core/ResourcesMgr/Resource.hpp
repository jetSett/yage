#ifndef RESSOURCE_HPP
#define RESSOURCE_HPP

#include <string>

class ResourceManager;

class Resource
{
    public:
        virtual ~Resource();

        const std::string& getName() const{
            return _name;
        }

        void addRef(){
            _refCount ++;
        }
        int release();
        int getRefCount();
    protected:
        Resource(const std::string& name);
    private:
        std::string _name;
        int _refCount;
};

#endif // RESSOURCE_HPP
