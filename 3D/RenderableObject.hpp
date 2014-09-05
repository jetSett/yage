#ifndef RENDERABLEOBJECT_H
#define RENDERABLEOBJECT_H

namespace Graphics{
namespace D3{

    class RenderableObject
    {
        public:
            virtual ~RenderableObject();
            virtual void rend() = 0;
        protected:
    };

}
}

#endif // RENDERABLEOBJECT_H
