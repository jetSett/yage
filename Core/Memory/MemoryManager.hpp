#ifndef MEMORYMANAGER_HPP
#define MEMORYMANAGER_HPP

#include <cstdlib>
#include <map>
#include <stack>
#include <fstream>
#include "../Utils/Exceptions.hpp"
#include "../Utils/FilePath.hpp"

namespace MemManaging{

struct Block{
    std::size_t size;
    bool array;

    FilePath file;
    int line;
};

const int NONE = -1, LOW = 0, MID = 1, HIGH = 2;

class MemoryManager
{
    public:
        static MemoryManager& instance();

        void* allocate(std::size_t sz, const char* file, int line, bool array);

        void free(void* ptr, bool array);

        void allocSingleton();

        void desalocSingleton();

        void setLoggingLevel(int lvl);

        ~MemoryManager();

    private:

        static MemoryManager inst;

        void reportLeaks();

        MemoryManager();

        std::ofstream _stream;

        int _loggingLevel;

        typedef std::map<void*, Block> BlockMap;
        BlockMap _blockMap;

        std::map<void*, bool> _destroyed;

        unsigned long long _total = 0, _max = 0, _current = 0;
};

}
#endif // MEMORYMANAGER_HPP
