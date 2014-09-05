#include "Window2D.hpp"
#include <Memory/NewInc.hpp>

namespace Graphics{
namespace D2{

    Window2D::Window2D(WindowPtr ptr) : _ptr(ptr)
    {
        _rend = SDL_CreateRenderer(_ptr->getSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        Image img(glm::ivec2(ptr->getWidth(), ptr->getHeight()));
        SDL_SetRenderDrawColor(_rend, 0, 255, 255, 255);
        SDL_RenderClear(_rend);

    }

    Window2D::~Window2D()
    {
        SDL_DestroyRenderer(_rend);
    }

    void Window2D::update(){
        SDL_RenderClear(_rend);
        for(Shape* s : _shapes){
            s->rend(_rend);
        }
        SDL_RenderPresent(_rend);
    }

    void Window2D::addShape(ShapePtr ptr){
        _shapes.push_back(ptr);
    }

    void Window2D::clearShape(){
        _shapes.clear();
    }

}
}
