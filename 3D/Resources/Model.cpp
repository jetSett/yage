#include <ResourcesMgr/MediaManager.hpp>

#include "Model.hpp"
#include <Memory/NewInc.hpp>

Model::Model(const std::string& name, const Vertex* vertices, unsigned long vcount,
             const Index* indices, unsigned long icount, const std::string& texture) : Resource(name){

    using namespace Graphics;

    if(texture.empty())
        useTexture = false;
    else
        useTexture = true;

    if(icount == 0)
        useIBuffer = false;
    else
        useIBuffer = true;

    D3::DeclarationElement elem[] = {
        {0, D3::ELT_USAGE_POSITION, D3::ELT_TYPE_FLOAT3},
        {0, D3::ELT_USAGE_NORMAL, D3::ELT_TYPE_FLOAT3},
        {0, D3::ELT_USAGE_TEXCOORD0, D3::ELT_TYPE_FLOAT2},
        {0, D3::ELT_USAGE_DIFUSE, D3::ELT_TYPE_COLOR}
    };
    _declaration = D3::Renderer::getInstance().createVertexDeclaration(elem);
    _vertexBuffer = D3::Renderer::getInstance().createVertexBuffer(vcount, 0, vertices);
    if(useIBuffer)
        _indexBuffer = D3::Renderer::getInstance().createIndexBuffer(icount, 0, indices);

    if(useTexture)
        _texture.createFromFile(texture, PXF_A8R8G8B8);
}

void Model::rend(){
    using namespace Graphics;
    D3::Renderer::getInstance().setDeclaration(_declaration);
    if(useTexture)
        D3::Renderer::getInstance().setTexture(0, _texture.getTexture());
        D3::Renderer::getInstance().setVertexBuffer(0, _vertexBuffer);

    if(useIBuffer){
        D3::Renderer::getInstance().setIndexBuffer(_indexBuffer);
        D3::Renderer::getInstance().drawIndexedPrimitives(D3::PT_TRIANGLELIST, 0, _vertexBuffer.getCount()/3);
    }else{
        D3::Renderer::getInstance().drawPrimitives(D3::PT_TRIANGLELIST, 0, _vertexBuffer.getCount()/3);
    }
}

Model::~Model(){}
