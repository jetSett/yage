#include "../Renderer.hpp"
#include "SceneNode.hpp"
#include "../SceneGraph.hpp"
#include <Memory/NewInc.hpp>

namespace Graphics{
namespace D3{

    SceneNode::SceneNode()
    {
        _updated = false;
    }

    SceneNode::~SceneNode()
    {
        //dtor
    }

    void SceneNode::addChild(const std::string n, SceneNode* c){
        SceneGraph::getInstance().addNode(n, c);
        _childrens.push_back(c);
    }

    void SceneNode::update(){
        _updated = true;
        Renderer::getInstance().setMatrixMult(MAT_MODELVIEW, _modelView);
        rend();
        for(SceneNode* c : _childrens){
            if(!c->_updated) //gestion cycles
                c->update();
        }
        Renderer::getInstance().setMatrixMult(MAT_MODELVIEW, glm::inverse(_modelView));
        _updated = false;
    }

    void SceneNode::setName(const std::string& n){
        _nom = n;
    }

//    void SceneNode::logChildrens(){
//        Logger::Log() << "Childs of " + nom;
//        for(SceneNode* s : _childrens){
//            Logger::Log() << s->nom;
//        }
//    }

    void SceneNode::translate(float x, float y, float z){
        _modelView*=glm::translate(glm::mat4(1.0),glm::vec3(x, y, z));
    }

    void SceneNode::scale(float x, float y, float z){
        _modelView*=glm::scale(glm::mat4(1.0),glm::vec3(x, y, z));
    }
}
}
