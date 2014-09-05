#include "Shape.hpp"

#include <Memory/NewInc.hpp>

namespace Graphics{
namespace D2{

    Shape::Shape(TexturePtr tex, SDL_Rect pos) : _text(tex), _pos(pos){
    }

    Shape::~Shape()
    {
    }

    void Shape::rend(SDL_Renderer* rend){
        SDL_RenderCopy(rend, _text->getTexture(), nullptr, &_pos);

    }

    void Shape::setPosition(SDL_Rect pos){
        _pos = pos;
    }

    void Shape::setTexture(TexturePtr tex){
        _text = tex;
    }

}
}
