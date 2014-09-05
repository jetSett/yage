#ifndef OGLSHADER_HPP_INCLUDED
#define OGLSHADER_HPP_INCLUDED

#include "../Resources/ShaderBase.hpp"

namespace Graphics{
namespace D3{

    class OGLShader: public ShaderBase{
        public:
        OGLShader(const std::string& name, CGprogram prog, ShaderType type);
        void setParameter(const std::string name, const glm::mat4 value);
        void setParameter(const std::string name, const float* value);
        private:
    };

}
}

#endif // OGLSHADER_HPP_INCLUDED
