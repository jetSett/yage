#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <Memory/SmartPtr.hpp>
#include <Utils/Logger.hpp>
#include <Utils/Exceptions.hpp>
#include "TextureBase.hpp"

namespace Graphics{
namespace D3{

    class Texture
    {
        public:
            ~Texture();
            Image& getPixels() const;
            const glm::ivec2& getSize() const;
            PixelFormat getFormat() const;
            const std::string& getName() const;
            const TextureBase* getTexture() const;

            void create(const glm::ivec2& size, PixelFormat format,
                        unsigned long flag = 0, const std::string name = "");

            void createFromFile(const std::string& file, PixelFormat format,
                                unsigned long flag = 0);

            void createFromImage(const Image& img, PixelFormat format,
                                 unsigned long flag = 0, const std::string name = "");
            void saveToFile(const std::string& file);

            void update(const Rect& rect = {-1, -1, -1, -1});

        private:
            void load(const Image& img, PixelFormat format, unsigned long flag, const std::string& name);

            ResourcePtr<TextureBase> _texture;
    };

}
}

#endif // TEXTURE_HPP
