#include "Shader.hpp"
#include <Memory/NewInc.hpp>

namespace Graphics{
namespace D3{

    void Shader::loadFromFile(const std::string name){
        _shad = ResourceManager::getInstance().get<ShaderBase>(name);
        if(!_shad){
            /// \warning mettre tout à niveau : cette ligne provoquait des bugs
            //_shad = MediaManager::getInstance().loadMediaFromFile<ShaderBase>(name);
            ResourceManager::getInstance().add(name, _shad);
        }
    }

    void Shader::setParameter(std::string name, float value){
        float arg[4] = {value, 0.0f, 0.0f, 0.0f};
        _shad->setParameter(name, arg);
    }

    void Shader::setParameter(std::string name, glm::vec2 value){
        float arg[4] = {value.x, value.y, 0.0f, 0.0f};
        _shad->setParameter(name, arg);
    }

    void Shader::setParameter(std::string name, glm::vec3 value){
        float arg[4] = {value.x, value.y, value.z, 0.0f};
        _shad->setParameter(name, arg);
    }

    void Shader::setParameter(std::string name, glm::vec4 value){
        float arg[4] = {value.x, value.y, value.z, value.w};
        _shad->setParameter(name, arg);
    }

    void Shader::setParameter(std::string name, glm::mat4 value){
        _shad->setParameter(name, value);
    }

    void Shader::setParameter(std::string name, Color value){
        float arg[4];
        value.toFloats(arg);
        _shad->setParameter(name, arg);
    }

    ShaderBase* Shader::getShader(){
        return _shad;
    }

}
}
