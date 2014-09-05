#ifndef OGLBUFFER_HPP_INCLUDED
#define OGLBUFFER_HPP_INCLUDED

#include "../BufferBase.hpp"
#include "OGLUtils.hpp"

namespace Graphics{
namespace D3{

    template<int Type>
    class OGLBuffer : public BufferBase{
    public:
        OGLBuffer(unsigned long count, unsigned int buffer);
        virtual ~OGLBuffer();

        unsigned int getBuffer() const;
    protected:
        virtual void* lock(unsigned long offset, unsigned long size, unsigned long flags) = 0;
        virtual void unlock() = 0;
        unsigned int _buffer;
    };
}
}


#include "OGLBuffer.tcc"

#endif // OGLBUFFER_HPP_INCLUDED
