#include "ModelObject.hpp"
#include <Memory/NewInc.hpp>

namespace Graphics{
namespace D3{

    ModelObject::ModelObject(ResourcePtr<Model> mod) : _model(mod)
    {
        //ctor
    }

    ModelObject::~ModelObject()
    {
        //dtor
    }

    void ModelObject::rend(){
        _model->rend();
    }

}
}
