#ifndef BUFFER_HPP_INCLUDED
#define BUFFER_HPP_INCLUDED

#include <Memory/SmartPtr.hpp>
#include "BufferBase.hpp"

namespace Graphics{
namespace D3{
    template<class T>
    class Buffer{
    public:
        Buffer(BufferBase* buffer = nullptr) : _buffer(buffer){}
        T* lock(unsigned long offset = 0, unsigned long size = 0, unsigned long flags = 0){
            return reinterpret_cast<T*>(_buffer->lock(offset*sizeof(T), size*sizeof(T), flags));
        }

        void unlock(){
            _buffer->unlock();
        }

        void fill(const T* data, std::size_t count){
            assert(data != nullptr);
            T* mData = lock();
            std::copy(data, data+count, mData);
            unlock();
        }

        void release(){
            _buffer = nullptr;
        }

        const BufferBase* getBuffer() const{
            return _buffer;
        }

        unsigned long getCount() const{
            return _buffer->_count;
        }
    private:
        SmartPtr<BufferBase> _buffer;
    };

}
}
#endif // BUFFER_HPP_INCLUDED
