#include "Texture.hpp"
#include "Renderer.hpp"
#include <ResourcesMgr/ResourceManager.hpp>
#include <ResourcesMgr/MediaManager.hpp>
#include <Memory/NewInc.hpp>

namespace Graphics{
namespace D3{

    Texture::~Texture(){
    }

    void Texture::load(const Image& img, PixelFormat format, unsigned long flag, const std::string& name){
        if(isFormatCompressed(format) && !Renderer::getInstance().hasCapability(CAP_DXT_COMPRESSION)){
            format = PXF_A8R8G8B8;
            Logger::Log() << "Warning"
                          << "Compressed format chosen, but unsuported by rending system"
                          << "Used format will be PXF_A8R8G8B8"
                          << std::string("Texture : ") + name;
        }

        glm::ivec2 size = glm::ivec2(nearPower2(img.getSize().x), nearPower2(img.getSize().y));
        if(size != img.getSize() && !Renderer::getInstance().hasCapability(CAP_TEX_NON_POWER_2)){
            Logger::Log() << "Warning"
                          << "texture's dimensions non power of two and unsuported by rendering system"
                          << "dimensions will be adjusted"
                          << "texture : " + name;
        }else{
            size = img.getSize();
        }

        try{
            _texture = Renderer::getInstance().createTexture(name, size, format, flag);
        }catch(const std::exception& e){
            throw LoadingFailed(name + std::string(e.what()));
        }

        if(name != "")
            ResourceManager::getInstance().add(name, _texture);

        if(isFormatCompressed(format))
            getPixels() = Image(getSize(), PXF_A8R8G8B8);

        getPixels().copyImage(img);

        update();

    }

    void Texture::create(const glm::ivec2& size, PixelFormat format, unsigned long, const std::string){
        createFromImage(Image(size, format), format);
    }

    void Texture::createFromFile(const std::string& file, PixelFormat format, unsigned long flag){
        _texture = ResourceManager::getInstance().get<TextureBase>(file);

        if(!_texture){
            SmartPtr<Image> image = MediaManager::getInstance().loadMediaFromFile<Image>(file);
            load(*image, format, flag, file);
        }
    }

    void Texture::createFromImage(const Image& img, PixelFormat format, unsigned long flag, const std::string name){
        _texture = ResourceManager::getInstance().get<TextureBase>(name);

        if(!_texture){
            load(img, format, flag, name);
        }
    }

    void Texture::saveToFile(const std::string& file){
        MediaManager::getInstance().saveMediaToFile(&(_texture->_data), file);
    }

    void Texture::update(const Rect& rect){
        _texture->_data.flip();
        if(rect.w == -1){
            _texture->update({0, 0, (int)getSize().x, (int)getSize().y});
        }else{
            _texture->update(rect);
        }
    }

    //accesseurs

    Image& Texture::getPixels() const{
        return _texture->_data;
    }

    const glm::ivec2& Texture::getSize() const{
        return _texture->_size;
    }

    PixelFormat Texture::getFormat() const{
        return _texture->_format;
    }

    const std::string& Texture::getName() const{
        return _texture->getName();
    }

    const TextureBase* Texture::getTexture() const{
        return _texture;
    }
}
}
