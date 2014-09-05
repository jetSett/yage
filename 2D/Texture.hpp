#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <Memory/SmartPtr.hpp>
#include <Graphics/Resources/Image.hpp>

#include "Utils.hpp"

namespace Graphics{
namespace D2{

    class Texture
    {
        public:
            Texture(Image& img, SDL_Renderer* rend);
            ~Texture();

            void update(Image& img, SDL_Renderer* rend);

            SDL_Texture* getTexture();

        private:
            SDL_Rect _pos;
            SDL_Texture* _text;
    };


    typedef SmartPtr<Texture> TexturePtr;
}
}

#endif // TEXTURE_H
