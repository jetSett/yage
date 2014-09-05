#ifndef COMPONENT_HPP_INCLUDED
#define COMPONENT_HPP_INCLUDED

#include <string>
#include <sstream>
#include <Memory/SmartPtr.hpp>
#include <3D/RenderableObject.hpp>

class Component{
public:
    std::string name; /// \brief will be used to load the Component if this component use and complex type
    bool hasToBeUpdated = true;
    virtual std::string serialize(){
        return name+";";
    }
    virtual ~Component(){}
private:
};

class PositionComponent : public Component{
public:
    PositionComponent(){
        name = "Position";
    }
    float x, y, z;
    virtual std::string serialize(){
        std::ostringstream oss;
        oss << x << ";" << y << ";" << z << ";";
        return Component::serialize() + oss.str();
    }
private:
};

class RenderableComponent : public Component{
public:
    RenderableComponent(){
        name = "Renderable";
    }

    std::string renderableThing;
    std::string object;
    virtual std::string serialize(){
        return Component::serialize()  + renderableThing + ";";
    }
};

#endif // COMPONENT_HPP_INCLUDED
