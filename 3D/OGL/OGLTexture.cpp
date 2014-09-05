#include "OGLTexture.hpp"
#include "OGLUtils.hpp"
#include "../OPENGL2/OGL2Renderer.hpp"
#include <Memory/NewInc.hpp>

namespace Graphics{
namespace D3{

    OGLTexture::OGLTexture(const std::string& name, const glm::ivec2& size, PixelFormat format,
                           bool hasMipmaps, bool autoMipmaps, unsigned int text) :
                               TextureBase(name, size, format, hasMipmaps, autoMipmaps){
        _texture = text;
    }

    OGLTexture::~OGLTexture(){}

    void OGLTexture::update(const Rect& r){
        assert(Rect({0, 0, (int)_size.x, (int)_size.y}).intersect(r) == INT_IN );
        OGLEnum::PixelFmt texFmt = OGLEnum::Get(_format);
        OGLEnum::PixelFmt imgFmt = OGLEnum::Get(_data.getFormat());

        glBindTexture(GL_TEXTURE_2D, _texture);

        if(isFormatCompressed(_data.getFormat())){
            unsigned long dataSize = r.w*r.h*getBytesPerPixel(_data.getFormat());
            if(r.w == _size.x && r.h == _size.y){
                OGL2Renderer::glCompressedTexImage2DARB(GL_TEXTURE_2D, 0, imgFmt.format, r.w, r.h,
                                                       0, dataSize, _data.getData());
            }else{
                Image subData = _data.subImage(r);
                OGL2Renderer::glCompressedTexSubImage2DARB(GL_TEXTURE_2D, 0, r.x, r.y, r.w, r.h,
                                                          imgFmt.format, dataSize, subData.getData());
            }
        }else{
            if(!_hasMipmaps || _autoMipmaps){
                if(r.w == _size.x && r.h == _size.y){
                    glTexSubImage2D(GL_TEXTURE_2D, 0, r.x, r.y, r.w, r.h, imgFmt.format, imgFmt.type, _data.getData());
                }else{
                Image subData = _data.subImage(r);
                glTexSubImage2D(GL_TEXTURE_2D, 0, r.x, r.y, r.w, r.h, imgFmt.format, imgFmt.type, subData.getData());                }
            }else{
                gluBuild2DMipmaps(GL_TEXTURE_2D, texFmt.internal, _size.x, _size.y,
                                  imgFmt.format, imgFmt.type, _data.getData());
            }
        }

        glBindTexture(GL_TEXTURE_2D, 0);

    }

}
}
