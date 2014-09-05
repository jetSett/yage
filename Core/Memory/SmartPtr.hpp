#ifndef SMARTPTR_H
#define SMARTPTR_H

#include <algorithm>
#include <cassert>
#include "MemoryManager.hpp"

template<class T>
class RefCount{
public:

    RefCount(T* ptr){
        void* raw = MemManaging::MemoryManager::instance().allocate(sizeof(int), __FILE__, __LINE__, false);
        _count = new(raw) int(1);
    }

    T* clone(T* ptr){
        *_count += 1;
        return ptr;
    }

    void release(T* ptr){
        *_count -= 1;
        if(*_count <= 0){
            if(ptr != nullptr){
                ptr->~T();
            }
            MemManaging::MemoryManager::instance().free(_count, false);
            MemManaging::MemoryManager::instance().free(ptr, false);
        }
    }


    void swap(RefCount& ref){
        std::swap(ref._count, _count);
    }

private:
    int* _count;
};

template<class T>
class ResourcesPolicie{
public:
    ResourcesPolicie(T *){}
    static T* clone(T* ptr){
        if(ptr)
            ptr->addRef();
        return ptr;
    }
    static void release(T* ptr){
        if(ptr){
            ptr->release();
        }
    }
    static void swap(ResourcesPolicie&){}
};

template<class T, template <class> class Ownership = RefCount>
class SmartPtr : private Ownership<T>
{
    public:
        inline SmartPtr();
        inline SmartPtr(T* val);
        inline SmartPtr(const SmartPtr&);
        ~SmartPtr();

        inline T& operator*() const;
        inline T* operator->() const;

        inline operator T*() const;

        const SmartPtr& operator=(const SmartPtr&);
        const SmartPtr& operator=(T*);


    private:
        void swap(SmartPtr<T, Ownership>& ptr){
            Ownership<T>::swap(ptr);
            std::swap(_data, ptr._data);
        }

        T* _data;
};

template<class T>
using ResourcePtr = SmartPtr<T, ResourcesPolicie>;

#include "SmartPtr.tcc"

#endif // SMARTPTR_H
