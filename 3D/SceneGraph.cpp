#include "SceneGraph.hpp"
#include <Memory/NewInc.hpp>

namespace Graphics{
namespace D3{

    SceneGraph::SceneGraph()
    {
        _graph.clear();
        SceneNode *root = new SceneNode;
        root->setName("Root");
        _graph[ROOTSNNAME] = root;
    }

    SceneGraph::~SceneGraph()
    {
    }

    void SceneGraph::addNode(const std::string& name, SceneNode* n){
        if(exist(name) and _graph[name] != n){ //si il existe et qu'il est différent du pointeur déja en mémoire
            throw BadIndex("SceneGraph::addNode");
        }else if(!exist(name)){ //s'il n 'existe pas
            n->setName(name);
            _graph[name] = n;
            Logger::Log() << "Register : " + name;
        }else{
            Logger::Log() << "Trying to register an existing node";
        //s'il existe et qu'il existe déjà, rien à faire
        }
    }

    SceneNode* SceneGraph::getNode(const std::string& n){
        if(!exist(n))
            throw BadIndex("SceneGraph::getNode");
        return _graph[n];
    }

    void SceneGraph::update(){
        _graph[ROOTSNNAME]->update();
    }

    SceneNode* SceneGraph::getRootSceneNode(){
        return _graph[ROOTSNNAME];
    }
}
}
