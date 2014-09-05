#include "Image.hpp"
#include <Memory/NewInc.hpp>

void Image::fill(const Graphics::Color& color) {
    setPixel(0, 0, color);

    unsigned int bpp = getBytesPerPixel(_format);
    std::vector<unsigned char>::iterator begin = _pixels.begin();
    for(auto it = begin + bpp; it != _pixels.end(); it+=bpp)
        std::copy(begin, begin+bpp, it);
}

void Image::setPixel(int x, int y, const unsigned char* pix) {
    std::copy(pix, pix + getBytesPerPixel(_format), &_pixels[(x+y*_size.x)*getBytesPerPixel(_format)]);
}

void Image::setPixel(int x, int y, const Graphics::Color& couleur) {
    unsigned char* pix = &_pixels[(x+y*_size.x)*getBytesPerPixel(_format)];
    unsigned char comp[4] = {couleur.getBlue(), couleur.getGreen(), couleur.getRed(), couleur.getAlpha()};
    convertPixel(PXF_A8R8G8B8, comp, _format, pix);
}

Graphics::Color Image::getPixel(int x, int y) const {
    unsigned char comp[4];
    const unsigned char* pix = &_pixels[(x+y*_size.x)*getBytesPerPixel(_format)];

    convertPixel(_format, pix, PXF_A8R8G8B8, comp);

    return Graphics::Color(comp[2], comp[1], comp[0], comp[3]);
}

void Image::getPixel(int x, int y, unsigned char* pix) const {
    const unsigned char* begin = &_pixels[(x+y*_size.x)*getBytesPerPixel(_format)];
    std::copy(begin, begin+getBytesPerPixel(_format), pix);
}

void Image::copyImage(const Image& src) {
    if(_size == src._size) {
        if(_format == src._format) {
            _pixels = src._pixels;
        } else {
            const unsigned char* srcPix = &src._pixels[0];
            unsigned char* destPix = &_pixels[0];
            unsigned int srcBpp = getBytesPerPixel(src._format);
            unsigned int destBpp = getBytesPerPixel(_format);
            for(int i = 0; i < _size.x; ++i) {
                for(int j = 0; j < _size.y; ++j) {
                    convertPixel(src._format, srcPix, _format, destPix);
                    srcPix += srcBpp;
                    destPix += destBpp;
                }
            }
        }
    } else {
        glm::ivec2 step;
        step.x = static_cast<float>(src._size.x)/_size.x;
        step.y = static_cast<float>(src._size.y)/_size.y;
        if(_format == src._format) {
            unsigned char pixel[16];
            for(int i = 0; i < _size.x; ++i) {
                for(int j = 0; j < _size.y; ++j) {
                    src.getPixel( (int)(i*step.x) , (int)(j*step.y) , pixel );
                    setPixel(i, j, pixel);
                }
            }
        } else {
            unsigned char srcPix[16], destPix[16];
            for(int i = 0; i < _size.x; ++i) {
                for(int j = 0; j < _size.y; ++j) {
                    src.getPixel( (int)(i*step.x) , (int)(j*step.y) , srcPix );
                    convertPixel(src._format, srcPix, _format, destPix);
                    setPixel(i, j, destPix);
                }
            }
        }
    }
}

Image Image::subImage(const Rect& rect) {
    Rect r = {0, 0, (int)_size.x, (int)_size.y};
    assert(r.intersect(rect) == INT_IN);

    glm::ivec2 v;
    v.x = rect.w;
    v.y = rect.h;
    Image img(v, _format);

    const unsigned char* src = &_pixels[(rect.x + rect.y + _size.x)*getBytesPerPixel(_format)];
    unsigned char* dest = &img._pixels[0];
    const unsigned int srcPitch = _size.x * getBytesPerPixel(_format);
    const unsigned int destPitch = img._size.x * getBytesPerPixel(img._format);

    for(int i = rect.x; i < rect.x+rect.w; ++i) {
        std::copy(src, src+destPitch, dest);
        src += srcPitch;
        dest += destPitch;
    }
    return img;
}

void Image::flip() {
    int bpp = getBytesPerPixel(_format);
    for(int j = 0; j < _size.y/2; ++j) {
        std::swap_ranges(&_pixels[j*_size.x*bpp],
                         &_pixels[(j+1)*_size.x*bpp-1],
                         &_pixels[(_size.y-j-1)*_size.x*bpp]);
    }
}

void Image::mirror() {
    int bpp = getBytesPerPixel(_format);
    for(int i = 0; i < _size.x/2; ++i)
        for(int j = 0; j < _size.y; ++j) {
            std::swap_ranges(&_pixels[(i+j*_size.x)*bpp],
                             &_pixels[(i+j*_size.x + 1)*bpp],
                             &_pixels[(_size.x-i-1+j*_size.x)*bpp]);
        }
}

void createFromSDL_BMP(const SDL_Surface* surf, Image& out){
    out = Image(glm::ivec2(surf->w, surf->h), PXF_R8G8B8, (unsigned char*)surf->pixels);
}
