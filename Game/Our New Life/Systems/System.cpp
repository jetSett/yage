#include "System.hpp"
#include "../Engines/GameEngine.hpp"
#include <Memory/NewInc.hpp>

System::System(GameEngine* p) : MessageSender(p), _hasToBeUpdated(true){
}

void System::update(){
    if(_hasToBeUpdated)
        _hasToBeUpdated = updateSystem();
}

void System::addEntity(Entity* ent){
    _entities[ent->id] = ent;
    updateNeeded();
}

void System::removeEntity(int id){
    _entities.erase(id);
    updateNeeded();
}

void System::updateNeeded(){
    _hasToBeUpdated = true;
}
