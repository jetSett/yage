#include "PositionSystem.hpp"
#include <Memory/NewInc.hpp>

PositionSystem::PositionSystem(GameEngine* p) : System(p)
{
}

bool PositionSystem::updateSystem(){
    return false;
}

Component* PositionSystem::loadComponent(const std::vector<std::string>& args){
    if(args.size()<4)
        throw LoadingFailed("PositionComponent");
    PositionComponent* comp = new PositionComponent;
    std::istringstream iss(args[1]);
    int a;
    iss>>a;
    comp->x = a;
    iss.str(args[2]);
    iss>>a;
    comp->y = a;
    iss.str(args[3]);
    iss>>a;
    comp->z = a;
    return comp;
}

