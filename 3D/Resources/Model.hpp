#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include <glm/glm.hpp>

#include <ResourcesMgr/Resource.hpp>

#include "../Renderer.hpp"
#include "../Buffer.hpp"
#include "../Texture.hpp"

class Model : public Resource{
public:

    struct Vertex{
        float px, py, pz;
        float nx, ny, nz;
        float tx, ty;
        Graphics::Color color;
    };

    typedef unsigned short Index;

    Model(const std::string& name, const Vertex* vertices, unsigned long vcount,
          const Index* indices, unsigned long icount, const std::string& texture);
    ~Model();

    virtual void rend();

    Graphics::D3::Texture& getTexture(){
        return _texture;
    }

private:
    Graphics::D3::DeclarationPtr _declaration, _normDecl;
    Graphics::D3::Buffer<Vertex> _vertexBuffer;
    Graphics::D3::Buffer<Index> _indexBuffer;
    Graphics::D3::Texture _texture;

    bool useIBuffer, useTexture;

};

#endif // MODEL_H_INCLUDED
