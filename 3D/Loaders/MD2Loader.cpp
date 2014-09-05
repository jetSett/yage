#include <fstream>

#include "MD2Loader.hpp"
#include <Memory/NewInc.hpp>

Model* MD2Loader::loadFromFile(const std::string& name) {
    std::ifstream stream(name.c_str(), std::ios_base::binary);
    Header head;
    stream.read(reinterpret_cast<char*>(&head), sizeof(Header));

    if(head.magic != _magicId)
        throw LoadingFailed(name + " magic");
    if(head.version != _MD2Version)
        throw LoadingFailed(name + " version");
    std::vector<Texture> textures(head.nbTex);
    std::vector<TexCoord> texCoord(head.nbTexCoord);
    std::vector<Triangle> triangles(head.nbTriangles);
    std::vector<Frame> frames(head.nbFrames);

    stream.seekg(head.offsetTextures, std::ios_base::beg);
    stream.read(reinterpret_cast<char*>(&textures[0]), sizeof(Texture)*head.nbTex);

    stream.seekg(head.offsetTexCoords, std::ios_base::beg);
    stream.read(reinterpret_cast<char*>(&texCoord[0]), sizeof(TexCoord)*head.nbTexCoord);

    stream.seekg(head.offsetTriangles, std::ios_base::beg);
    stream.read(reinterpret_cast<char*>(&triangles[0]), sizeof(Triangle)*head.nbTriangles);

    stream.seekg(head.offsetFrames, std::ios_base::beg);
    frames[0].vertices.resize(head.nbVert);
    stream.read(reinterpret_cast<char*>(&frames[0].scale), sizeof(frames[0].scale));
    stream.read(reinterpret_cast<char*>(&frames[0].translate), sizeof(frames[0].translate));
    stream.read(reinterpret_cast<char*>(&frames[0].name), sizeof(frames[0].name));
    stream.read(reinterpret_cast<char*>(&frames[0].vertices[0]), sizeof(Point)*head.nbVert);

    std::vector<Model::Vertex> vertices;
    std::vector<Model::Index>  indices;

    for(int i = 0; i < head.nbTriangles; ++i) {
        for(int j=0; j<3; ++j) {
            Model::Vertex v;
            const Point& vert = frames[0].vertices[triangles[i].vertices[j]];
            const TexCoord& texC = texCoord[triangles[i].texCoords[j]];

            v.px = vert.x*frames[0].scale.x+frames[0].translate.x;
            v.py = vert.y*frames[0].scale.y+frames[0].translate.y;
            v.pz = vert.z*frames[0].scale.z+frames[0].translate.z;

            v.nx = _normalTable[vert.n].x;
            v.ny = _normalTable[vert.n].y;
            v.nz = _normalTable[vert.n].z;

            v.color = Graphics::D3::Renderer::getInstance().convertColor(Graphics::Color::White);

            v.tx = texC.u/static_cast<float>(head.texW);
            v.ty = texC.v/static_cast<float>(head.texH);

            vertices.push_back(v);
            indices.push_back(i*3+2-j);
        }
    }

    std::string texName = "";

    if(textures[0].name != nullptr)
        texName = textures[0].name;
    Model* m = new Model(name, &vertices[0], (int)vertices.size(), &indices[0], (int)indices.size(), texName);
    return m;
}
const glm::vec3 MD2Loader::_normalTable[] = {
    glm::vec3(-0.525731f,  0.000000f,  0.850651f),
    glm::vec3(-0.442863f,  0.238856f,  0.864188f),
    glm::vec3(-0.295242f,  0.000000f,  0.955423f),
    glm::vec3(-0.309017f,  0.500000f,  0.809017f),
    glm::vec3(-0.162460f,  0.262866f,  0.951056f),
    glm::vec3( 0.000000f,  0.000000f,  1.000000f),
    glm::vec3( 0.000000f,  0.850651f,  0.525731f),
    glm::vec3(-0.147621f,  0.716567f,  0.681718f),
    glm::vec3( 0.147621f,  0.716567f,  0.681718f),
    glm::vec3( 0.000000f,  0.525731f,  0.850651f),
    glm::vec3( 0.309017f,  0.500000f,  0.809017f),
    glm::vec3( 0.525731f,  0.000000f,  0.850651f),
    glm::vec3( 0.295242f,  0.000000f,  0.955423f),
    glm::vec3( 0.442863f,  0.238856f,  0.864188f),
    glm::vec3( 0.162460f,  0.262866f,  0.951056f),
    glm::vec3(-0.681718f,  0.147621f,  0.716567f),
    glm::vec3(-0.809017f,  0.309017f,  0.500000f),
    glm::vec3(-0.587785f,  0.425325f,  0.688191f),
    glm::vec3(-0.850651f,  0.525731f,  0.000000f),
    glm::vec3(-0.864188f,  0.442863f,  0.238856f),
    glm::vec3(-0.716567f,  0.681718f,  0.147621f),
    glm::vec3(-0.688191f,  0.587785f,  0.425325f),
    glm::vec3(-0.500000f,  0.809017f,  0.309017f),
    glm::vec3(-0.238856f,  0.864188f,  0.442863f),
    glm::vec3(-0.425325f,  0.688191f,  0.587785f),
    glm::vec3(-0.716567f,  0.681718f, -0.147621f),
    glm::vec3(-0.500000f,  0.809017f, -0.309017f),
    glm::vec3(-0.525731f,  0.850651f,  0.000000f),
    glm::vec3( 0.000000f,  0.850651f, -0.525731f),
    glm::vec3(-0.238856f,  0.864188f, -0.442863f),
    glm::vec3( 0.000000f,  0.955423f, -0.295242f),
    glm::vec3(-0.262866f,  0.951056f, -0.162460f),
    glm::vec3( 0.000000f,  1.000000f,  0.000000f),
    glm::vec3( 0.000000f,  0.955423f,  0.295242f),
    glm::vec3(-0.262866f,  0.951056f,  0.162460f),
    glm::vec3( 0.238856f,  0.864188f,  0.442863f),
    glm::vec3( 0.262866f,  0.951056f,  0.162460f),
    glm::vec3( 0.500000f,  0.809017f,  0.309017f),
    glm::vec3( 0.238856f,  0.864188f, -0.442863f),
    glm::vec3( 0.262866f,  0.951056f, -0.162460f),
    glm::vec3( 0.500000f,  0.809017f, -0.309017f),
    glm::vec3( 0.850651f,  0.525731f,  0.000000f),
    glm::vec3( 0.716567f,  0.681718f,  0.147621f),
    glm::vec3( 0.716567f,  0.681718f, -0.147621f),
    glm::vec3( 0.525731f,  0.850651f,  0.000000f),
    glm::vec3( 0.425325f,  0.688191f,  0.587785f),
    glm::vec3( 0.864188f,  0.442863f,  0.238856f),
    glm::vec3( 0.688191f,  0.587785f,  0.425325f),
    glm::vec3( 0.809017f,  0.309017f,  0.500000f),
    glm::vec3( 0.681718f,  0.147621f,  0.716567f),
    glm::vec3( 0.587785f,  0.425325f,  0.688191f),
    glm::vec3( 0.955423f,  0.295242f,  0.000000f),
    glm::vec3( 1.000000f,  0.000000f,  0.000000f),
    glm::vec3( 0.951056f,  0.162460f,  0.262866f),
    glm::vec3( 0.850651f, -0.525731f,  0.000000f),
    glm::vec3( 0.955423f, -0.295242f,  0.000000f),
    glm::vec3( 0.864188f, -0.442863f,  0.238856f),
    glm::vec3( 0.951056f, -0.162460f,  0.262866f),
    glm::vec3( 0.809017f, -0.309017f,  0.500000f),
    glm::vec3( 0.681718f, -0.147621f,  0.716567f),
    glm::vec3( 0.850651f,  0.000000f,  0.525731f),
    glm::vec3( 0.864188f,  0.442863f, -0.238856f),
    glm::vec3( 0.809017f,  0.309017f, -0.500000f),
    glm::vec3( 0.951056f,  0.162460f, -0.262866f),
    glm::vec3( 0.525731f,  0.000000f, -0.850651f),
    glm::vec3( 0.681718f,  0.147621f, -0.716567f),
    glm::vec3( 0.681718f, -0.147621f, -0.716567f),
    glm::vec3( 0.850651f,  0.000000f, -0.525731f),
    glm::vec3( 0.809017f, -0.309017f, -0.500000f),
    glm::vec3( 0.864188f, -0.442863f, -0.238856f),
    glm::vec3( 0.951056f, -0.162460f, -0.262866f),
    glm::vec3( 0.147621f,  0.716567f, -0.681718f),
    glm::vec3( 0.309017f,  0.500000f, -0.809017f),
    glm::vec3( 0.425325f,  0.688191f, -0.587785f),
    glm::vec3( 0.442863f,  0.238856f, -0.864188f),
    glm::vec3( 0.587785f,  0.425325f, -0.688191f),
    glm::vec3( 0.688191f,  0.587785f, -0.425325f),
    glm::vec3(-0.147621f,  0.716567f, -0.681718f),
    glm::vec3(-0.309017f,  0.500000f, -0.809017f),
    glm::vec3( 0.000000f,  0.525731f, -0.850651f),
    glm::vec3(-0.525731f,  0.000000f, -0.850651f),
    glm::vec3(-0.442863f,  0.238856f, -0.864188f),
    glm::vec3(-0.295242f,  0.000000f, -0.955423f),
    glm::vec3(-0.162460f,  0.262866f, -0.951056f),
    glm::vec3( 0.000000f,  0.000000f, -1.000000f),
    glm::vec3( 0.295242f,  0.000000f, -0.955423f),
    glm::vec3( 0.162460f,  0.262866f, -0.951056f),
    glm::vec3(-0.442863f, -0.238856f, -0.864188f),
    glm::vec3(-0.309017f, -0.500000f, -0.809017f),
    glm::vec3(-0.162460f, -0.262866f, -0.951056f),
    glm::vec3( 0.000000f, -0.850651f, -0.525731f),
    glm::vec3(-0.147621f, -0.716567f, -0.681718f),
    glm::vec3( 0.147621f, -0.716567f, -0.681718f),
    glm::vec3( 0.000000f, -0.525731f, -0.850651f),
    glm::vec3( 0.309017f, -0.500000f, -0.809017f),
    glm::vec3( 0.442863f, -0.238856f, -0.864188f),
    glm::vec3( 0.162460f, -0.262866f, -0.951056f),
    glm::vec3( 0.238856f, -0.864188f, -0.442863f),
    glm::vec3( 0.500000f, -0.809017f, -0.309017f),
    glm::vec3( 0.425325f, -0.688191f, -0.587785f),
    glm::vec3( 0.716567f, -0.681718f, -0.147621f),
    glm::vec3( 0.688191f, -0.587785f, -0.425325f),
    glm::vec3( 0.587785f, -0.425325f, -0.688191f),
    glm::vec3( 0.000000f, -0.955423f, -0.295242f),
    glm::vec3( 0.000000f, -1.000000f,  0.000000f),
    glm::vec3( 0.262866f, -0.951056f, -0.162460f),
    glm::vec3( 0.000000f, -0.850651f,  0.525731f),
    glm::vec3( 0.000000f, -0.955423f,  0.295242f),
    glm::vec3( 0.238856f, -0.864188f,  0.442863f),
    glm::vec3( 0.262866f, -0.951056f,  0.162460f),
    glm::vec3( 0.500000f, -0.809017f,  0.309017f),
    glm::vec3( 0.716567f, -0.681718f,  0.147621f),
    glm::vec3( 0.525731f, -0.850651f,  0.000000f),
    glm::vec3(-0.238856f, -0.864188f, -0.442863f),
    glm::vec3(-0.500000f, -0.809017f, -0.309017f),
    glm::vec3(-0.262866f, -0.951056f, -0.162460f),
    glm::vec3(-0.850651f, -0.525731f,  0.000000f),
    glm::vec3(-0.716567f, -0.681718f, -0.147621f),
    glm::vec3(-0.716567f, -0.681718f,  0.147621f),
    glm::vec3(-0.525731f, -0.850651f,  0.000000f),
    glm::vec3(-0.500000f, -0.809017f,  0.309017f),
    glm::vec3(-0.238856f, -0.864188f,  0.442863f),
    glm::vec3(-0.262866f, -0.951056f,  0.162460f),
    glm::vec3(-0.864188f, -0.442863f,  0.238856f),
    glm::vec3(-0.809017f, -0.309017f,  0.500000f),
    glm::vec3(-0.688191f, -0.587785f,  0.425325f),
    glm::vec3(-0.681718f, -0.147621f,  0.716567f),
    glm::vec3(-0.442863f, -0.238856f,  0.864188f),
    glm::vec3(-0.587785f, -0.425325f,  0.688191f),
    glm::vec3(-0.309017f, -0.500000f,  0.809017f),
    glm::vec3(-0.147621f, -0.716567f,  0.681718f),
    glm::vec3(-0.425325f, -0.688191f,  0.587785f),
    glm::vec3(-0.162460f, -0.262866f,  0.951056f),
    glm::vec3( 0.442863f, -0.238856f,  0.864188f),
    glm::vec3( 0.162460f, -0.262866f,  0.951056f),
    glm::vec3( 0.309017f, -0.500000f,  0.809017f),
    glm::vec3( 0.147621f, -0.716567f,  0.681718f),
    glm::vec3( 0.000000f, -0.525731f,  0.850651f),
    glm::vec3( 0.425325f, -0.688191f,  0.587785f),
    glm::vec3( 0.587785f, -0.425325f,  0.688191f),
    glm::vec3( 0.688191f, -0.587785f,  0.425325f),
    glm::vec3(-0.955423f,  0.295242f,  0.000000f),
    glm::vec3(-0.951056f,  0.162460f,  0.262866f),
    glm::vec3(-1.000000f,  0.000000f,  0.000000f),
    glm::vec3(-0.850651f,  0.000000f,  0.525731f),
    glm::vec3(-0.955423f, -0.295242f,  0.000000f),
    glm::vec3(-0.951056f, -0.162460f,  0.262866f),
    glm::vec3(-0.864188f,  0.442863f, -0.238856f),
    glm::vec3(-0.951056f,  0.162460f, -0.262866f),
    glm::vec3(-0.809017f,  0.309017f, -0.500000f),
    glm::vec3(-0.864188f, -0.442863f, -0.238856f),
    glm::vec3(-0.951056f, -0.162460f, -0.262866f),
    glm::vec3(-0.809017f, -0.309017f, -0.500000f),
    glm::vec3(-0.681718f,  0.147621f, -0.716567f),
    glm::vec3(-0.681718f, -0.147621f, -0.716567f),
    glm::vec3(-0.850651f,  0.000000f, -0.525731f),
    glm::vec3(-0.688191f,  0.587785f, -0.425325f),
    glm::vec3(-0.587785f,  0.425325f, -0.688191f),
    glm::vec3(-0.425325f,  0.688191f, -0.587785f),
    glm::vec3(-0.425325f, -0.688191f, -0.587785f),
    glm::vec3(-0.587785f, -0.425325f, -0.688191f),
    glm::vec3(-0.688191f, -0.587785f, -0.425325f)
};
