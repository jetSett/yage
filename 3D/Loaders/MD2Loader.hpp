#ifndef MD2_LOADER_INC
#define MD2_LOADER_INC

#include <ResourcesMgr/Loaders.hpp>
#include "../Resources/Model.hpp"

class MD2Loader : public Loader<Model>{
    static const int _magicId    = ('2' << 24) + ('P' << 16) + ('D' << 8) + 'I'; ///< Identifiant magique "IDP2" servant à valider les modèles
    static const int _MD2Version = 8;                                            ///< Numéro de version géré
    static const glm::vec3 _normalTable[];                                       ///< Table des normales précalculées



    struct Header
    {
        int magic;            ///< Numéro magique "IDP2"
        int version;          ///< Version du format
        int texW;         ///< Largeur de la texture
        int texH;        ///< Hauteur de la texture
        int frameSize;        ///< Taille d'une frame en octets
        int nbTex;       ///< Nombre de textures
        int nbVert;       ///< Nombre de vertices par frame
        int nbTexCoord;      ///< Nombre de coordonnées de texture
        int nbTriangles;      ///< Nombre de triangles
        int nbGLCommands;     ///< Nombre de commandes OpenGL
        int nbFrames;         ///< Nombre de frames
        int offsetTextures;   ///< Offset données textures
        int offsetTexCoords;  ///< Offset données coordonnées de texture
        int offsetTriangles;  ///< Offset données triangles
        int offsetFrames;     ///< Offset données frames
        int offsetGLCommands; ///< Offset données commandes OpenGL
        int offsetEnd;        ///< Offset fin de fichier
    };

    struct Point
    {
        unsigned char x, y, z; ///< Coordonnées 3D
        unsigned char n;       ///< Indice de la normale (dans la table des normales précalculées)
    };

    struct TexCoord
    {
        short u, v; ///< Coordonnées de texture (relatives à la taille de celle-ci)
    };

    struct Triangle
    {
        unsigned short vertices[3];  ///< Indices des 3 sommets du triangle
        unsigned short texCoords[3]; ///< Indices des coordonnées de texture des 3 sommets du triangle
    };

    struct Texture
    {
        char name[68]; ///< Nom de fichier de la texture
    };

    struct Frame
    {
        glm::vec3      scale;     ///< Facteur d'échelle
        glm::vec3      translate; ///< Position
        char                name[16];  ///< Nom de la frame
        std::vector<Point> vertices;  ///< Liste des sommets
    };

public:
    virtual Model* loadFromFile(const std::string&);
};

#endif // MD2_LOADER_INC
