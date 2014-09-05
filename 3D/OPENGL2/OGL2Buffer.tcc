namespace Graphics{
namespace D3{

    template<int Type>
    OGL2Buffer<Type>::OGL2Buffer(unsigned long count, unsigned int buffer) : OGLBuffer<Type>(count, buffer){
    }

    template<int Type>
    OGL2Buffer<Type>::~OGL2Buffer(){
        if(this->_buffer)
            OGL2Renderer::glDeleteBuffersARB(1, &(this->_buffer));
    }

    template<int Type>
    void* OGL2Buffer<Type>::lock(unsigned long offset, unsigned long, unsigned long flags){
        OGL2Renderer::glBindBufferARB(Type, this->_buffer);
        unsigned char* buffer = reinterpret_cast<unsigned char*>(OGL2Renderer::glMapBufferARB(Type, OGLEnum::LockFlags(flags)));
        return buffer+offset;
    }

    template<int Type>
    void OGL2Buffer<Type>::unlock(){
        OGL2Renderer::glUnmapBufferARB(Type);
    }
}
}

