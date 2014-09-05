#include "MemoryManager.hpp"

inline void* operator new (std::size_t sz, const char* file, int line){
    return MemManaging::MemoryManager::instance().allocate(sz, file, line, false);
}

inline void* operator new[] (std::size_t sz, const char* file, int line){
    return MemManaging::MemoryManager::instance().allocate(sz, file, line, true);
}

inline void operator delete (void* ptr){
    MemManaging::MemoryManager::instance().free(ptr, false);
}

inline void operator delete[] (void* ptr){
    MemManaging::MemoryManager::instance().free(ptr, true);
}

inline void operator delete (void* ptr, const char* file, int line){
    MemManaging::MemoryManager::instance().free(ptr, false);
}

inline void operator delete[] (void* ptr, const char* file, int line){
    MemManaging::MemoryManager::instance().free(ptr, true);
}

#define new new(__FILE__, __LINE__)
//#define delete MemManaging::MemoryManager::instance().nextDelete(__FILE__, __LINE__), delete
