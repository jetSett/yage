#include "Texture.hpp"
#include <Memory/NewInc.hpp>


namespace Graphics{
namespace D2{

    Texture::Texture(Image& img, SDL_Renderer* rend)
    {

        _text = nullptr;
        update(img, rend);

    }

    Texture::~Texture()
    {
        SDL_DestroyTexture(_text);
    }

    void Texture::update(Image& img, SDL_Renderer* rend){
        if(_text != nullptr)
            SDL_DestroyTexture(_text);

        SDL_Texture* tex = SDL_CreateTexture(rend, convertEnum(img.getFormat()), SDL_TEXTUREACCESS_STREAMING, img.getSize().x, img.getSize().y);
        SDL_UpdateTexture(tex, nullptr, &(img.getData()[0]), img.getSize().x*getBytesPerPixel(img.getFormat()));
        _text = tex;
    }

    SDL_Texture* Texture::getTexture(){
        return _text;
    }

}
}
