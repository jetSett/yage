#ifndef IMAGE_HPP_INCLUDED
#define IMAGE_HPP_INCLUDED

#include <vector>

#include <SDL2/SDL_surface.h>

#include "../Graphics/Utils/Color.hpp"
#include <Utils/Exceptions.hpp>
#include <Utils/Logger.hpp>
#include <glm/glm.hpp>

#include "PixelUtils.hpp"
#include <Utils/Surfaces.hpp>

#include <ResourcesMgr/Resource.hpp>

class Image{
public:
    Image(glm::ivec2 size = glm::ivec2(1, 1), PixelFormat format = PXF_A8R8G8B8) : _size(size), _format(format),
    _pixels(size.x*size.y*getBytesPerPixel(_format), 0) {}
    Image(glm::ivec2 size, PixelFormat format, const unsigned char* pix) : _size(size), _format(format),
        _pixels(pix, (pix + (unsigned int)size.x*(unsigned int)size.y*getBytesPerPixel(_format))) {
    }
    const glm::ivec2& getSize() const {
        return _size;
    }

    PixelFormat getFormat() const {
        return _format;
    }

    const unsigned char* getData() const {
        return &(_pixels[0]);
    }

    void fill(const Graphics::Color& color);
    void copyImage(const Image& src);
    Image subImage(const Rect& rect);
    void flip();
    void mirror();

    void setPixel(int x, int y, const unsigned char* pix);
    void setPixel(int x, int y, const Graphics::Color& pix);
    void getPixel(int x, int y, unsigned char* pix) const;
    Graphics::Color getPixel(int x, int y) const;

private:
    glm::ivec2 _size;
    PixelFormat _format;
    std::vector<unsigned char> _pixels;
};

void createFromSDL_BMP(const SDL_Surface* surf, Image& out);

#endif // IMAGE_HPP_INCLUDED
