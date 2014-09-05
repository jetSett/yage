#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

#include <map>

#include "Components.hpp"

struct Entity{
    unsigned id; /// \brief identifier of the Entity
    std::map<std::string, SmartPtr<Component>> components;
};

#endif // ENTITY_HPP_INCLUDED
