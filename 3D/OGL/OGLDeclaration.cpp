#include "OGLDeclaration.hpp"
#include <Memory/NewInc.hpp>

namespace Graphics{
namespace D3{

    OGLDeclaration::OGLDeclaration()
    {
        _elements.clear();
    }

    OGLDeclaration::~OGLDeclaration()
    {
        _elements.clear();
    }

    void OGLDeclaration::addElement(unsigned int stream, const Element& elem){
        if(stream >= _elements.size())
            _elements.resize(stream+1);
        _elements[stream].push_back(elem);
    }

    const OGLDeclaration::ElementArray& OGLDeclaration::getStreamElements(unsigned int stream) const{
        return _elements.at(stream);
    }

}
}
