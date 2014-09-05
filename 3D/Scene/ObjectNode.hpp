#ifndef MODELNODE_HPP
#define MODELNODE_HPP

#include "SceneNode.hpp"
#include "../RenderableObject.hpp"

namespace Graphics{
namespace D3{

    class ObjectNode : public SceneNode
    {
        public:
            ObjectNode(SmartPtr<RenderableObject>);
            virtual ~ObjectNode();
            virtual void rend();
        protected:
            SmartPtr<RenderableObject> _object;
    };

}
}

#endif // MODELNODE_HPP
