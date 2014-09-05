#include "MemoryManager.hpp"

namespace MemManaging{

MemoryManager MemoryManager::inst;

MemoryManager::MemoryManager() : _stream("outMem.log"), _loggingLevel(LOW)
{
}

MemoryManager::~MemoryManager(){
    if(_loggingLevel >= LOW){
        _stream << "Used (max/total) : " << _max << "/" << _total << std::endl;
        if(_blockMap.empty()){
            _stream << "No leaks detected" << std::endl;
        }else{
            _stream << "Leaks detected : " << std::endl;
            reportLeaks();
        }
    }
}

void MemoryManager::setLoggingLevel(int lvl){
    _loggingLevel = lvl;
}

void MemoryManager::reportLeaks(){
    std::size_t total = 0;
    for(auto p : _blockMap){
        total += p.second.size;
        _stream << "Leak : " << p.first;
        if(_loggingLevel >= MID){
            _stream << " | " << p.second.size << " | " << p.second.file.filename() << ":" << p.second.line;
        }
        _stream << std::endl;
    }
    _stream << "Total : " << total << "bytes" << std::endl;
}

MemoryManager& MemoryManager::instance(){
    return inst;
}

void* MemoryManager::allocate(std::size_t sz, const char* file, int line, bool array){
    void* ptr = std::malloc(sz);
    Block b;
    b.array = array;
    b.file = file;
    b.line = line;
    b.size = sz;
    _blockMap[ptr] = b;
    _destroyed[ptr] = false;

    if(_loggingLevel >= MID){
        _stream << "Aloc : " << ptr;
        if(_loggingLevel >= HIGH)
            _stream << " | " << sz << "bytes " << " | " << file << ":" << line;
        _stream << std::endl;
    }


    _total += sz;
    _current += sz;
    if(_current > _max)
        _max = _current;
    return ptr;
}

void MemoryManager::free(void* ptr, bool array){
    auto it = _blockMap.find(ptr);
    if(it == _blockMap.end()){
        if(_destroyed.find(ptr) == _destroyed.end())
            std::free(ptr);
        return;
    }

    if(it->second.array != array){
        throw BadDelete(ptr, it->second.file.fullname(), it->second.line);
    }

    if(_loggingLevel >= MID){
        _stream << "Desaloc : " << ptr;
        if(_loggingLevel >= HIGH)
            _stream << " | " << it->second.size << "bytes " << " | " << it->second.file.fullname() << ":" << it->second.line;
        _stream << std::endl;
    }
    _current -= it->second.size;

    _blockMap.erase(it);
    _destroyed[ptr] = true;

    std::free(ptr);
}


}

