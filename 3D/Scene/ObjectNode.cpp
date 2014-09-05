#include "ObjectNode.hpp"
#include <Memory/NewInc.hpp>

namespace Graphics{
namespace D3{

    ObjectNode::ObjectNode(SmartPtr<RenderableObject> mod) : _object(mod){
    }

    ObjectNode::~ObjectNode(){
    }

    void ObjectNode::rend(){
        _object->rend();
    }
}
}
