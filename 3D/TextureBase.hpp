#ifndef TEXTUREBASE_HPP_INCLUDED
#define TEXTUREBASE_HPP_INCLUDED

#include <glm/glm.hpp>

#include <Utils/Surfaces.hpp>
#include <Utils/Logger.hpp>

#include <ResourcesMgr/Resource.hpp>

#include "../Graphics/Resources/Image.hpp"


namespace Graphics{
namespace D3{

    class Texture;

    class TextureBase : public Resource{
    public:
        virtual ~TextureBase();
    protected:
        friend class Texture;

        TextureBase(const std::string& name, const glm::ivec2& size, PixelFormat format, bool hasMipmaps, bool autoMipmaps) : Resource(name){
            _size = size;
            _format=format;
            _hasMipmaps=hasMipmaps;
            _autoMipmaps=autoMipmaps;
            _data = Image(_size, _format);
        }

        virtual void update(const Rect& r) = 0;

        glm::ivec2 _size;
        PixelFormat _format;
        Image _data;

        bool _hasMipmaps;
        bool _autoMipmaps;

    };

}
}

#endif // TEXTUREBASE_HPP_INCLUDED
