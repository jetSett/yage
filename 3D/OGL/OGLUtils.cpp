#include "OGLUtils.hpp"
#include <Memory/NewInc.hpp>
namespace Graphics{
namespace D3{

    GLenum OGLEnum::matrixTypes[] =
    {
        GL_MODELVIEW,
        GL_PROJECTION,
        GL_TEXTURE,
        GL_TEXTURE,
        GL_TEXTURE,
        GL_TEXTURE
    };

    OGLEnum::PixelFmt OGLEnum::pixelFormat[] =
    {
        {GL_LUMINANCE, GL_LUMINANCE8, GL_UNSIGNED_BYTE},
        {GL_LUMINANCE_ALPHA, GL_LUMINANCE8_ALPHA8, GL_UNSIGNED_BYTE},
        {GL_BGRA, GL_RGB5_A1, GL_UNSIGNED_SHORT_1_5_5_5_REV},
        {GL_BGRA, GL_RGBA4, GL_UNSIGNED_SHORT_4_4_4_4_REV},
        {GL_BGR, GL_RGB8, GL_UNSIGNED_BYTE},
        {GL_BGRA, GL_RGBA8, GL_UNSIGNED_BYTE},
        {GL_BGR, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, 0},
        {GL_BGRA, GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, 0},
        {GL_BGRA, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, 0}
    };

    unsigned long OGLEnum::BufferFlag(unsigned long flag){
        return (flag & BUF_DYNAMIC? GL_STATIC_DRAW_ARB: GL_DYNAMIC_DRAW_ARB);
    }

    unsigned long OGLEnum::LockFlags(unsigned long flag){
        unsigned long f = GL_READ_WRITE_ARB;
        if(flag & LOCK_READONLY) f = GL_WRITE_ONLY_ARB;
        if(flag & LOCK_WRITEONLY) f = GL_READ_ONLY_ARB;
        return f;
    }

}
}
