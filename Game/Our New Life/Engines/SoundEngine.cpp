#include "SoundEngine.hpp"
#include "ResourcesMgr/MediaManager.hpp"
#include <Memory/NewInc.hpp>

using namespace SoundManagement;

SoundEngine::SoundEngine(Game* p) : Engine(p)
{
    REGISTER_RECEIVER(&SoundEngine::playSoundReceiver);
}

SoundEngine::~SoundEngine()
{
    SoundManager::destroy();
    Logger::Log() << "Destruct Sound";
}

void SoundEngine::frame(){
    updatePlayingSounds();
}

void SoundEngine::playSound(Sound* s){
    PlayingSound pls;
    pls.name = s->getName();
    pls.sound = s;
    pls.channel = SoundMgr.playSound(s->getSound());
    _playingSounds.push_back(pls);
}

void SoundEngine::updatePlayingSounds(){
    for(auto it = _playingSounds.begin(); it != _playingSounds.end(); ++it){
        if(!SoundMgr.isPlaying(it->channel)){
            auto i2 = it;
            it++;
            _playingSounds.erase(i2);
            it--;
        }
    }
}

void SoundEngine::playSoundReceiver(Message& m){
    Sound* s = nullptr;
    if(!alreadyLoaded(m.s_data["name"])){
        s = MediaManager::getInstance().loadMediaFromFile<Sound>(m.s_data["name"]);
        _loadedSounds[m.s_data["name"]] = s;
    }else{
        s = _loadedSounds[m.s_data["name"]];
    }
    playSound(_loadedSounds[m.s_data["name"]]);
}

bool SoundEngine::alreadyLoaded(const std::string& name){
    return _loadedSounds.find(name) != _loadedSounds.end();
}
