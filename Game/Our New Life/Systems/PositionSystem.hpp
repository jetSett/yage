#ifndef POSITIONSYSTEM_H
#define POSITIONSYSTEM_H

#include <Utils/Exceptions.hpp>
#include "System.hpp"

class PositionSystem : public System
{
    public:
        PositionSystem(GameEngine* p);

        Component* loadComponent(const std::vector<std::string>& args);


    private:
        bool updateSystem();
};

#endif // POSITIONSYSTEM_H
