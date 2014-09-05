#include "SoundLoaders.hpp"
#include "../SoundManager.hpp"
#include <Utils/Logger.hpp>
#include <Memory/NewInc.hpp>

Sound* StreamLoader::loadFromFile(const std::string& file){
    FMOD_SOUND* stream = SoundManagement::SoundManager::getInstance().createStream(file);
    Sound* s = new Sound(file, stream);
    return s;
}
