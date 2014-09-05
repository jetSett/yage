#ifndef SINGLETON_HPP_INCLUDED
#define SINGLETON_HPP_INCLUDED

#include "../Memory/MemoryManager.hpp"

template<class T>
class Singleton{
public:
    static T& getInstance(){
        if(!_instance){
//            _instance = new T;
            void* raw = MemManaging::MemoryManager::instance().allocate(sizeof(T), __FILE__, __LINE__, false);
            _instance = new(raw) T;
        }
        return *_instance;
    }
    static void destroy(){
        _instance->~T();
        MemManaging::MemoryManager::instance().free(_instance, false);
//        delete _instance;
        _instance = nullptr;
    }
protected:
    Singleton(){
    }
    ~Singleton(){
    }
private:
    static T* _instance;
    Singleton(const Singleton&);
    void operator=(const Singleton&);
};

template<class T>
T* Singleton<T>::_instance;

#endif // SINGLETON_HPP_INCLUDED
