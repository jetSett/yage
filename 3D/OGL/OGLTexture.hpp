#ifndef OGLTEXTURE_HPP_INCLUDED
#define OGLTEXTURE_HPP_INCLUDED

#include "../TextureBase.hpp"

namespace Graphics{
namespace D3{

    class OGLTexture : public TextureBase{
    public:
        OGLTexture(const std::string& name, const glm::ivec2& size, PixelFormat format,
                   bool hasMipmaps, bool autoMipmaps, unsigned int text);
        ~OGLTexture();

        unsigned int getOGLTexture() const{
            return _texture;
        }

    protected:
        virtual void update(const Rect& r);
        unsigned int _texture;

    };

}
}

#endif // OGLTEXTURE_HPP_INCLUDED
