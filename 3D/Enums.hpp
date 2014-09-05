#ifndef ENUM_HPP_INCLUDED
#define ENUM_HPP_INCLUDED

#include <string>

namespace Graphics{
namespace D3{

    enum MatrixType{
        MAT_MODELVIEW,
        MAT_PROJECTION,
        MAT_TEXTURE_0,
        MAT_TEXTURE_1,
        MAT_TEXTURE_2,
        MAT_TEXTURE_3
    };

    enum PrimitiveType{
        PT_TRIANGLELIST,
        PT_TRIANGLESTRIP,
        PT_TRIANGLEFAN,
        PT_LINELIST,
        PT_LINESTRIP,
        PT_POINTLIST
    };

    enum{
        BUF_STATIC = 1 << 0,
        BUF_DYNAMIC = 1 << 1
    };
    enum{
        LOCK_READONLY = 1 << 0,
        LOCK_WRITEONLY = 1 << 1
    };

    enum{
        WND_FULLSCREEN = 1 << 0
    };

    enum{
        TEX_NOMIPMAP = 1 << 0
    };

    enum Capabilities{
        CAP_HW_MIPMAPPING,
        CAP_DXT_COMPRESSION,
        CAP_TEX_NON_POWER_2
    };

}
}

#endif // ENUM_HPP_INCLUDED
