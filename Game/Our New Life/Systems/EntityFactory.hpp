#ifndef ENTITYFACTORY_HPP
#define ENTITYFACTORY_HPP

#include <fstream>

#include <Utils/Exceptions.hpp>
#include <Utils/StringUtilities.hpp>
#include <Utils/Singleton.hpp>

#include <Entity.hpp>

#include "System.hpp"

class EntityFactory : public Singleton<EntityFactory>
{
    public:
        friend class Singleton<EntityFactory>;

        std::list<Entity*> load(const std::string& file); /// on charge des entités d'un fichier
        Entity* loadFromString(const std::string& buffer); /// on charge une entité (une ligne)

        void saveEntity(const std::string& file, Entity& ent); /// cas où on sauve une entité dans un fichier

        void registerSystem(const std::string& name, System* sys);

    private:
        EntityFactory();
        std::map<std::string, System*> _systems;

        unsigned long _entityNumber = 0;///\brief the actual count of entities
        std::mutex _entityMutex;///\brief used to increment the count of entities in threaded system

};

#endif // ENTITYFACTORY_HPP
