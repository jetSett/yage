#ifndef MODELOBJECT_HPP
#define MODELOBJECT_HPP

#include "RenderableObject.hpp"
#include "Resources/Model.hpp"

namespace Graphics{
namespace D3{

    class ModelObject : public RenderableObject
    {
        public:
            ModelObject(ResourcePtr<Model> mod);
            virtual ~ModelObject();
            virtual void rend();
        private:
            ResourcePtr<Model> _model;
    };

}
}

#endif // MODELOBJECT_HPP
