#include "../Renderer.hpp"
#include "ShadersLoader.hpp"
#include <Memory/NewInc.hpp>

template<>
Shader* Loader<Shader>::load(const std::string& name){
    return loadFromFile(name);
}

ShadersLoader::ShadersLoader(ShaderType t) : _type(t){
    cgSetErrorCallback(onError);
    _context = cgCreateContext();
}

ShadersLoader::~ShadersLoader(){
    if(_context)
        cgDestroyContext(_context);
}

ShaderBase* ShadersLoader::loadFromFile(const std::string& file){
    CGprofile profile = Graphics::D3::Renderer::getInstance().getShaderProfile(_type);
    const char** options = const_cast<const char**>(Graphics::D3::Renderer::getInstance().getShaderOptions(_type));
    CGprogram program;
    try{
        program = cgCreateProgramFromFile(_context, CG_SOURCE, file.c_str(), profile, "main", options);
    }catch(PersoException& e) {
        throw LoadingFailed(file + " " + e.what() + " " + cgGetLastListing(_context));
    }
    return Graphics::D3::Renderer::getInstance().createShader(file, program, _type);
}

void ShadersLoader::onError(){
    throw ExternError("Cg", cgGetErrorString(cgGetError()));
}
