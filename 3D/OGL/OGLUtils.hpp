#ifndef OGLUTILS_H
#define OGLUTILS_H

#include <exception>
#include <string>

#include <GL/glew.h>

#include <GL/glx.h>

#include <GL/glext.h>
#include <GL/glxext.h>

#include "../Enums.hpp"
#include <Utils/Exceptions.hpp>
#include "../../Graphics/Resources/PixelUtils.hpp"

namespace Graphics{
namespace D3{

    class OGLException : public PersoException{
    public:
        OGLException(std::string op, std::string f) : PersoException(std::string("OGL Error : ") + f +
                                                                     std::string(" -> ") + op){
        }
    private:
    };



    class OGLEnum{
    public:
        struct PixelFmt{GLenum format, internal, type;};
        static GLenum Get(MatrixType v){
            return matrixTypes[v];
        }

        static PixelFmt Get(PixelFormat v){
            return pixelFormat[v];
        }

        static unsigned long BufferFlag(unsigned long flag);

        static unsigned long LockFlags(unsigned long flag);

    private:
        static GLenum matrixTypes[];
        static PixelFmt pixelFormat[];
    };
}
}

#endif // OGLENUM_H
