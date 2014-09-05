#include "Renderer.hpp"
#include <Memory/NewInc.hpp>

namespace Graphics{
namespace D3{

    Renderer* Renderer::_instance = nullptr;

    void Renderer::destroy(){
        delete _instance;
        _instance = nullptr;
    }

    Renderer& Renderer::getInstance(){
        assert(_instance != nullptr);
        return *_instance;
    }

    void Renderer::setInstance(Renderer* inst){
        destroy();
        _instance = inst;
    }

    bool Renderer::hasCapability(Capabilities cp){
        assert(_capabilities.find(cp) != _capabilities.end());
        return _capabilities[cp];
    }
}
}
