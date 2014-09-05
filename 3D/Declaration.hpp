#ifndef DECLARATION_HPP_INCLUDED
#define DECLARATION_HPP_INCLUDED

#include <Memory/SmartPtr.hpp>

namespace Graphics{
namespace D3{

    enum ElementUsage{
        ELT_USAGE_POSITION,
        ELT_USAGE_NORMAL,
        ELT_USAGE_DIFUSE,
        ELT_USAGE_TEXCOORD0,
        ELT_USAGE_TEXCOORD1,
        ELT_USAGE_TEXCOORD2,
        ELT_USAGE_TEXCOORD3
    };

    enum ElementType{
        ELT_TYPE_FLOAT1,
        ELT_TYPE_FLOAT2,
        ELT_TYPE_FLOAT3,
        ELT_TYPE_FLOAT4,
        ELT_TYPE_COLOR
    };

    struct DeclarationElement{
        unsigned int stream;
        ElementUsage usage;
        ElementType type;
    };

    class Declaration{
    public:
        virtual ~Declaration(){}
    protected:
        Declaration(){}
    };
    typedef SmartPtr<Declaration> DeclarationPtr;
}
}

#endif // DECLARATION_HPP_INCLUDED
