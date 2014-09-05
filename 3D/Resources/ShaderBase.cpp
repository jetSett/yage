#include "../Renderer.hpp"
#include "ShaderBase.hpp"
#include <Memory/NewInc.hpp>

ShaderBase::ShaderBase(const std::string& name, CGprogram prog, ShaderType type) : Resource(name), _type(type), _program(prog){}

ShaderBase::~ShaderBase(){
    if(_program)
        cgDestroyProgram(_program);
}

CGparameter ShaderBase::getParameter(const std::string name) const{
    return cgGetNamedParameter(_program, name.c_str());
}
