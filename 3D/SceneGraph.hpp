#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <map>
#include <Utils/Singleton.hpp>
#include <Utils/Logger.hpp>
#include <Utils/Exceptions.hpp>
#include "Scene/SceneNode.hpp"

namespace Graphics{
namespace D3{

    const std::string ROOTSNNAME = "Root";

    /// \class SceneGraph
    /// \brief Manage all the gestion (desalocation, storage, indexing) of SceneNode
    class SceneGraph : public Singleton<SceneGraph>
    {
        public:
            friend class Singleton<SceneGraph>;
            ~SceneGraph();
            SceneNode* getRootSceneNode();

            ///\fn addNode
            ///\brief index a node
            void addNode(const std::string& name, SceneNode* n);

            /// \fn getNode
            /// \brief return the node with the name passed in argument
            /// \warning never destroy a node returned by this function
            SceneNode* getNode(const std::string& n);

            void update();
        private:

            bool exist(const std::string& n){
                return _graph.find(n) != _graph.end();
            }

            SceneGraph();
            std::map<std::string, SmartPtr<SceneNode>> _graph;
    };

}
}

#endif // SCENEGRAPH_H
