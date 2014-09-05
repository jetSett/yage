#ifndef SOUNDENGINE_HPP
#define SOUNDENGINE_HPP

#include <list>

#include "Engine.hpp"
#include "../Sounds/SoundManager.hpp"

class SoundEngine : public Engine
{
    public:

        SoundEngine(Game* p);
        virtual ~SoundEngine();
        virtual void frame();

        void playSound(Sound* s);

        void playSoundReceiver(Message&);


    private:
        struct PlayingSound{
            std::string name = "";
            Sound* sound = nullptr;
            FMOD_CHANNEL* channel = nullptr;
        };

        std::list<PlayingSound> _playingSounds;

        void updatePlayingSounds();

        std::map<std::string, ResourcePtr<Sound>> _loadedSounds;

        bool alreadyLoaded(const std::string& name);

        SoundManagement::SoundManager& SoundMgr = SoundManagement::SoundManager::getInstance();
};

#endif // SOUNDENGINE_HPP
