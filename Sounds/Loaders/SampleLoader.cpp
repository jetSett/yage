#include "SoundLoaders.hpp"
#include "../SoundManager.hpp"
#include <Utils/Logger.hpp>
#include <Memory/NewInc.hpp>

Sound* SampleLoader::loadFromFile(const std::string& file){
    FMOD_SOUND* sample = SoundManagement::SoundManager::getInstance().createSample(file);
    Sound *s = new Sound(file, sample);
    return s;
}
