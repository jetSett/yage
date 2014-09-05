#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include "../Graphics/Utils/Color.hpp"
#include "Resources/ShaderBase.hpp"
#include <Memory/SmartPtr.hpp>
#include <ResourcesMgr/MediaManager.hpp>
#include <ResourcesMgr/ResourceManager.hpp>

namespace Graphics{
namespace D3{

    class Shader
    {
        public:
            void loadFromFile(const std::string name);
            void unload();
            ShaderBase* getShader();

            void setParameter(std::string name, float value);
            void setParameter(std::string name, glm::vec2 value);
            void setParameter(std::string name, glm::vec3 value);
            void setParameter(std::string name, glm::vec4 value);
            void setParameter(std::string name, glm::mat4 value);
            void setParameter(std::string name, Color value);
        private:
            ResourcePtr<ShaderBase> _shad;
    };

}
}

#endif // SHADER_HPP
