#ifndef SYSTEM_HPP_INCLUDED
#define SYSTEM_HPP_INCLUDED

#include <list>

#include <Entity.hpp>

#include "../Engines/MessageManaging.hpp"

class GameEngine;

class System : public MessageSender{
public:
    System(GameEngine* p);
    void update();
    void addEntity(Entity*);
    void removeEntity(int id);

    void updateNeeded();

    virtual ~System(){}
    virtual Component* loadComponent(const std::vector<std::string>& args) = 0;
private:
    bool _hasToBeUpdated;
protected:
    virtual bool updateSystem() = 0;
    std::map<int, Entity*> _entities;

};

#endif // SYSTEM_HPP_INCLUDED
