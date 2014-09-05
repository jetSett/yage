#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

#include <string>
#include <fmode/fmod.h>

#include <Utils/Singleton.hpp>
#include <Memory/SmartPtr.hpp>
#include "Resources/Sound.hpp"

namespace SoundManagement{

    class SoundManager : public Singleton<SoundManager>
    {
        friend class Singleton<SoundManager>;

        public:
            ~SoundManager();
            FMOD_CHANNEL* playSound(FMOD_SOUND* sound); //do not use it
            FMOD_SOUND* createSample(const std::string& file);
            FMOD_SOUND* createStream(const std::string& file);
            bool isPlaying(FMOD_CHANNEL* chan);
            const unsigned int CHANNELS_COUNT = 4;
        private:

            SoundManager();
            FMOD_SYSTEM *_sys;
    };

}

#endif // SOUNDMANAGER_HPP
