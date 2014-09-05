#ifndef RENDERABLESYSTEM_HPP
#define RENDERABLESYSTEM_HPP

#include <Utils/Exceptions.hpp>
#include "System.hpp"

#include "../Engines/GameEngine.hpp"

class RenderableSystem : public System
{
    public:
        RenderableSystem(GameEngine* p);
        Component* loadComponent(const std::vector<std::string>& args);

        RenderableComponent* loadModelComponent(const std::vector<std::string>& args);
    private:
        bool updateSystem();
};

#endif // RENDERABLESYSTEM_HPP
