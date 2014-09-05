#include "RenderableSystem.hpp"
#include <Utils/StringUtilities.hpp>
#include <ResourcesMgr/MediaManager.hpp>
#include <3D/ModelObject.hpp>
#include <Memory/NewInc.hpp>

RenderableSystem::RenderableSystem(GameEngine* p) : System(p)
{
    //ctor
}

Component* RenderableSystem::loadComponent(const std::vector<std::string>& args){
    if(args.size()<2)
        throw LoadingFailed("Renderable");
    std::vector<std::string> tokens;

    RenderableComponent* comp = nullptr;

    if(args[1] == "Model"){
        std::vector<std::string> arguments;
        for(unsigned int i = 2; i<args.size(); ++i){
            arguments.push_back(args[i]);
        }
        comp = loadModelComponent(arguments);
    }else{
        throw LoadingFailed("Renderable");
    }

    return comp;
}

RenderableComponent* RenderableSystem::loadModelComponent(const std::vector<std::string>& args){
    using namespace Graphics::D3;
    RenderableComponent* rd = new RenderableComponent;
    rd->object = args[0];
    rd->renderableThing = "Model";
    return rd;
}

bool RenderableSystem::updateSystem(){
    for(auto p  : _entities){
        Entity* ent = p.second;
        if(ent->components.find("Position") != ent->components.end()){ /// si l'entité possède une position
            RenderableComponent* rend = static_cast<RenderableComponent*>((Component*)ent->components["Renderable"]);
            PositionComponent* pos = static_cast<PositionComponent*>((Component*)ent->components["Renderable"]);
            Message m;
            m.name = "propagate";
            m.s_data["To"] = "graphics";
            m.s_data["Name"] = "addModel";
            m.v_data["Position"] = glm::vec3(pos->x, pos->y, pos->z);
            m.s_data["name"] = rend->object;
            sendMessage(m);
        }
    }
    return false;
}
