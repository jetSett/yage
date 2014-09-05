#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Texture.hpp"

namespace Graphics{
namespace D2{

    class Shape
    {
        public:
            Shape(TexturePtr tex, SDL_Rect pos);
            virtual ~Shape();

            void rend(SDL_Renderer*);

            void setPosition(SDL_Rect pos);
            void setTexture(TexturePtr tex);

        private:
            TexturePtr _text;
            SDL_Rect _pos;
    };
    typedef SmartPtr<Shape> ShapePtr;
}
}
#endif // SHAPE_HPP
