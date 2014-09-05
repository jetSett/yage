#ifndef BUFFERBASE_HPP_INCLUDED
#define BUFFERBASE_HPP_INCLUDED

namespace Graphics{
namespace D3{
    template<class T>
    class Buffer;

    class BufferBase{
        template<class T>
        friend class Buffer;
    public:
        virtual ~BufferBase(){}
    protected:
        BufferBase(unsigned long count) : _count(count){}

        virtual void* lock(unsigned long offset, unsigned long size, unsigned long flags) = 0;
        virtual void unlock() = 0;

        unsigned long _count;
    };

}
}
#endif // BUFFERBASE_HPP_INCLUDED
