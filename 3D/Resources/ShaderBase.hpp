#ifndef SHADER_HPP_INCLUDED
#define SHADER_HPP_INCLUDED

#include <Cg/cg.h>
#include <glm/glm.hpp>

#include <ResourcesMgr/Resource.hpp>

/// \todo mettre tout à niveau.
/// \warning ne PAS inclure/utiliser ce fichier

enum ShaderType{
    SHAD_PIX, SHAD_VERT
};

class ShaderBase : public Resource{
    public:

    ShaderBase(const std::string& name, CGprogram prog, ShaderType type);
    ~ShaderBase();

    ShaderType getType() const{
        return _type;
    }

    CGprogram getProgram() const{
        return _program;
    }

    virtual void setParameter(const std::string name, const float* value) = 0;
    virtual void setParameter(const std::string name, const glm::mat4 value) = 0;

    protected:
    CGparameter getParameter(const std::string name) const;
    ShaderType _type;
    CGprogram _program;
};

#endif // SHADER_HPP_INCLUDED
