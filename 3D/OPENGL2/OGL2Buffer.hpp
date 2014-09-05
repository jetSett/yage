#ifndef OGL2BUFFER_HPP_INCLUDED
#define OGL2BUFFER_HPP_INCLUDED

#include "../OGL/OGLBuffer.hpp"

namespace Graphics{
namespace D3{

    template<int Type>
    class OGL2Buffer : public OGLBuffer<Type>{
    public:
        OGL2Buffer(unsigned long count, unsigned int buffer);
        ~OGL2Buffer();

    private:
        virtual void* lock(unsigned long offset, unsigned long size, unsigned long flags);
        virtual void unlock();
    };

    typedef OGL2Buffer<GL_ARRAY_BUFFER_ARB> OGL2VertexBuffer;
    typedef OGL2Buffer<GL_ELEMENT_ARRAY_BUFFER_ARB> OGL2IndexBuffer;

}
}

#include "OGL2Buffer.tcc"

#endif // OGL2BUFFER_HPP_INCLUDED
