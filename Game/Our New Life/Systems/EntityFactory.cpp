#include "EntityFactory.hpp"
#include <Memory/NewInc.hpp>

EntityFactory::EntityFactory()
{
    //ctor
}

std::list<Entity*> EntityFactory::load(const std::string& file){
    std::ifstream stream(file);
    std::list<Entity*> list;

    unsigned int size = 0;
    stream>>size;
    std::string buffer;
    std::getline(stream, buffer);
    buffer.clear();
    unsigned int i = 0;
    while(i<size){
        std::string temp;
        if(!std::getline(stream, temp) or (isDigit(temp) and !buffer.empty())){ // on est dans une nouvelle déclaration
            list.push_back(loadFromString(buffer));
            buffer.clear();
            i++;
        }
        buffer+=temp+"\n";
    }
    return list;
}

Entity* EntityFactory::loadFromString(const std::string& text){
    Entity* e = new Entity;

    _entityMutex.lock();
        e->id = _entityNumber;
        _entityNumber+=1;
    _entityMutex.unlock();

    unsigned int sze = 0;
    std::istringstream stream(text);
    stream>>sze;

    std::string str;
    std::getline(stream, str);
    for(unsigned int i = 0; i<sze; ++i){
        std::getline(stream, str);

        std::vector<std::string> args;
        split(str, args, ";\n");

        std::string name = args[0];
        try{
            e->components[name] = _systems[name]->loadComponent(args);
            _systems[name]->addEntity(e);
        }catch(const std::exception& exep){
            delete e;
            throw LoadingFailed(exep.what());
        }catch(...){
            delete e;
        }
    }
    return e;
}

void EntityFactory::saveEntity(const std::string& file, Entity& ent){

    std::ofstream stream(file);

    if(!stream)
        throw LoadingFailed(file);

    unsigned int size = ent.components.size();
    stream << size;
    stream << "\n";

    for(auto p : ent.components){
        stream << p.second->serialize() << "\n";
    }
}

void EntityFactory::registerSystem(const std::string& name, System* sys){
    _systems[name] = sys;
}
