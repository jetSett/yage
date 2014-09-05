#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include <list>

#include <Memory/SmartPtr.hpp>

#include "../Systems/System.hpp"
#include "../Systems/EntityFactory.hpp"

#include "Engine.hpp"

class PositionSystem;
class RenderableSystem;

class GameEngine : public Engine
{
    public:
        GameEngine(Game*);
        ~GameEngine();
        virtual void frame();
        int registerEntity(Entity*);
        void registerSystem(const std::string& name, System*);
        SmartPtr<Entity> getEntity(unsigned long index);

    private:

        void propagateReceiver(Message&);

        ///alias :
        EntityFactory& EntFact = EntityFactory::getInstance();

        ///attributes :
        std::map<std::string, SmartPtr<System>> _systems;///\brief all the registered systems
        std::map<unsigned long, SmartPtr<Entity>> _entities;///\brief all the registered entities
};

#endif // GAMEENGINE_HPP
