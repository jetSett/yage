#include "Renderer.hpp"
#include <Memory/NewInc.hpp>

namespace Graphics{
namespace D2{

    Renderer::Renderer()
    {
        //ctor
    }

    Renderer::~Renderer()
    {
        _wind.clear();
    }

    Window2DPtr Renderer::initialize(WindowPtr pt){
        Window2D* wind = new Window2D(pt);
        Window2DPtr ptr(wind);
        _wind.push_back(ptr);
        return ptr;
    }

    void Renderer::update(){
        for(Window2D* w : _wind){
            w->update();
        }
    }

}
}
