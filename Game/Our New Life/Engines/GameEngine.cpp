#include "GameEngine.hpp"

#include "../Systems/PositionSystem.hpp"
#include "../Systems/RenderableSystem.hpp"
#include <Memory/NewInc.hpp>


GameEngine::GameEngine(Game* p) : Engine(p)
{

    REGISTER_RECEIVER(&GameEngine::propagateReceiver);

    registerSystem("Position", new PositionSystem(this));
    registerSystem("Renderable", new RenderableSystem(this));
    std::list<Entity*> l = EntFact.load("sink.entity");
    for(Entity* e : l){
        registerEntity(e);
    }
}

GameEngine::~GameEngine()
{
    EntityFactory::destroy();
    Logger::Log() << "Destruct Game";
}

void GameEngine::frame(){
    for(auto p : _systems){
        p.second->update();
    }
}

void GameEngine::registerSystem(const std::string& name, System* sys){
    EntFact.registerSystem(name, sys);
    _systems[name] = sys;
}

int GameEngine::registerEntity(Entity* ent){
    _entities[ent->id] = ent;
    return ent->id;
}

SmartPtr<Entity> GameEngine::getEntity(unsigned long index){
    return _entities[index];
}

void GameEngine::propagateReceiver(Message& m){
    m.name = m.s_data["Name"];
    std::string to = m.s_data["To"];
    sendMessage(to, m);
}
