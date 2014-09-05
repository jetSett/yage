namespace Graphics{
namespace D3{

    template<int Type>
    OGLBuffer<Type>::OGLBuffer(unsigned long count, unsigned int buffer) : BufferBase(count), _buffer(buffer){}

    template<int Type>
    unsigned int OGLBuffer<Type>::getBuffer() const{
        return _buffer;
    }

    template<int Type>
    OGLBuffer<Type>::~OGLBuffer(){}



}
}
