#ifndef SOUNDLOADERS_INC
#define SOUNDLOADERS_INC

#include "../Resources/Sound.hpp"
#include <ResourcesMgr/Loaders.hpp>

class SampleLoader : public Loader<Sound>{
public:
    virtual Sound* loadFromFile(const std::string&);
};

class StreamLoader : public Loader<Sound>{
public:
    virtual Sound* loadFromFile(const std::string&);
};

#endif // SOUNDLOADERS_INC
