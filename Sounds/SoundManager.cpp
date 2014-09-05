#include "SoundManager.hpp"
#include <Utils/Exceptions.hpp>
#include <Utils/Logger.hpp>
#include <Memory/NewInc.hpp>

namespace SoundManagement{

    SoundManager::SoundManager()
    {
        FMOD_System_Create(&_sys);
        FMOD_System_Init(_sys, CHANNELS_COUNT, FMOD_INIT_NORMAL, nullptr);
    }

    FMOD_SOUND* SoundManager::createSample(const std::string& file){
        FMOD_SOUND* sound = nullptr;
        if(FMOD_System_CreateSound(_sys, file.c_str(), FMOD_CREATESAMPLE | FMOD_HARDWARE, nullptr, &sound) == FMOD_OK)
            return sound;
        else
            throw LoadingFailed(file);
    }

    FMOD_SOUND* SoundManager::createStream(const std::string& file){
        FMOD_SOUND* sound = nullptr;
        if(FMOD_System_CreateStream(_sys, file.c_str(), FMOD_HARDWARE | FMOD_LOOP_OFF | FMOD_2D, nullptr, &sound) == FMOD_OK)
            return sound;
        else
            throw LoadingFailed(file);
    }

    FMOD_CHANNEL* SoundManager::playSound(FMOD_SOUND* sound){
        FMOD_CHANNEL* chan;
        FMOD_System_PlaySound(_sys, FMOD_CHANNEL_FREE, sound, false, &chan);
        return chan;
    }

    bool SoundManager::isPlaying(FMOD_CHANNEL* chan){
        FMOD_BOOL b;
        FMOD_Channel_IsPlaying(chan, &b);
        return b != 0;
    }


    SoundManager::~SoundManager()
    {
        FMOD_System_Close(_sys);
        FMOD_System_Release(_sys);
    }

}
