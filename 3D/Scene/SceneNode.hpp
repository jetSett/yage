#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <list>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Memory/SmartPtr.hpp>

namespace Graphics{
namespace D3{

    class SceneNode
    {
        public:
            SceneNode();
            virtual ~SceneNode();
            virtual void update();
            virtual void rend(){}
            void addChild(const std::string, SceneNode*);
            void translate(float x, float y, float z);
            void setName(const std::string& n);
//            void logChildrens();
//            void rotate(float x, float y, float z);
            void scale(float x, float y, float z);
        protected:
            std::string _nom;
            glm::mat4 _modelView = glm::mat4(1.0f);
            bool _updated;
            std::list<SceneNode*> _childrens;
    };

}
}

#endif // SCENENODE_HPP
