#include <Cg/cgGL.h>
#include <glm/gtc/type_ptr.hpp>
#include "OGLShader.hpp"
#include <Memory/NewInc.hpp>

namespace Graphics{
namespace D3{

    OGLShader::OGLShader(const std::string& name, CGprogram prog, ShaderType type) : ShaderBase(name, prog, type){
        cgGLLoadProgram(_program);
    }

    void OGLShader::setParameter(const std::string name, const float* value){
        cgGLSetParameter4fv(getParameter(name), value);
    }

    void OGLShader::setParameter(const std::string name, const glm::mat4 value){
        cgGLSetMatrixParameterfc(getParameter(name), glm::value_ptr(value));
    }

}
}
