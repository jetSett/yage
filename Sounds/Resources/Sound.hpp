#ifndef SOUND_HPP
#define SOUND_HPP

#include <fmode/fmod.h>

#include "ResourcesMgr/Resource.hpp"

class Sound : public Resource
{
    public:
        Sound(std::string, FMOD_SOUND*);
        ~Sound();
        FMOD_SOUND* getSound();
    private:
        FMOD_SOUND* _sound;
};

#endif // SOUND_HPP
