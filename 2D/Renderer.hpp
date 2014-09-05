#ifndef RENDERER_H
#define RENDERER_H

#include <list>
#include <Graphics/WindowsManager.hpp>

#include "Window2D.hpp"

namespace Graphics{
namespace D2{
    class Renderer : public Singleton<Renderer>
    {
        friend class Singleton<Renderer>;
        public:
            virtual ~Renderer();
            Window2DPtr initialize(WindowPtr ptr);

            void update();

        private:
            Renderer();
            std::list<Window2DPtr> _wind;
    };
}
}
#endif // RENDERER_H
