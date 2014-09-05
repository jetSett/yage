#ifndef WINDOW2D_H
#define WINDOW2D_H

#include <list>
#include <SDL2/SDL.h>
#include <Graphics/WindowsManager.hpp>
#include "Shape.hpp"

namespace Graphics{
namespace D2{

    class Window2D
    {
        public:
            Window2D(WindowPtr ptr);

            ~Window2D();

            void update();

            SDL_Renderer* getRenderer(){
                return _rend;
            }

            void addShape(ShapePtr ptr);

            void clearShape();

        protected:
        private:
            TexturePtr fond;
            std::list<ShapePtr> _shapes;
            WindowPtr _ptr;
            SDL_Renderer* _rend;
    };

    typedef SmartPtr<Window2D> Window2DPtr;

}
}
#endif // WINDOW2D_H
