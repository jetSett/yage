#include "Sound.hpp"
#include <Memory/NewInc.hpp>

Sound::Sound(std::string name, FMOD_SOUND* sound) : Resource(name), _sound(sound)
{
}

FMOD_SOUND* Sound::getSound(){
    return _sound;
}

Sound::~Sound()
{
    if(_sound)
        FMOD_Sound_Release(_sound);
}
