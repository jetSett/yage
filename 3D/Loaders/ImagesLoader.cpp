#include "ImagesLoader.hpp"
#include <Utils/Logger.hpp>
#include <IL/il.h>
#include <Memory/NewInc.hpp>

template<>
Image* Loader<Image>::load(const std::string& name){
    return loadFromFile(name);
}

ImagesLoader::ImagesLoader(){
    ilInit();

    ilOriginFunc(IL_ORIGIN_UPPER_LEFT);
    ilEnable(IL_ORIGIN_SET);

    ilEnable(IL_FILE_OVERWRITE);

    ilSetInteger(IL_FORMAT_MODE, IL_BGRA);
    ilEnable(IL_FORMAT_SET);
}

ImagesLoader::~ImagesLoader(){
    ilShutDown();
}

Image* ImagesLoader::loadFromFile(const std::string& file){
    ILuint texture;
    ilGenImages(1, &texture);
    ilBindImage(texture);

    if(!(ilLoadImage(const_cast<ILstring>(file.c_str()))))
        throw LoadingFailed(file);

    glm::ivec2 size;
    size.x = ilGetInteger(IL_IMAGE_WIDTH);
    size.y = ilGetInteger(IL_IMAGE_HEIGHT);

    const unsigned char* pix = ilGetData();

    Image* img = new Image(size, PXF_A8R8G8B8, pix);
    img->flip();

    return img;
}

void ImagesLoader::saveToFile(const Image* object, const std::string& fileName){
    Image img(object->getSize(), PXF_A8R8G8B8);
    img.copyImage(*object);

    img.flip();

    ILuint tx;
    ilGenImages(1, &tx);
    ilBindImage(tx);

    const glm::ivec2& size = img.getSize();

    if(!ilTexImage(size.x, size.y, 1, getBytesPerPixel(img.getFormat()),
                   IL_BGRA, IL_UNSIGNED_BYTE, (void*)img.getData()))
        throw LoadingFailed(fileName);

    if(!ilSaveImage(const_cast<ILstring>(fileName.c_str())))
        throw LoadingFailed(fileName);

    ilBindImage(0);
    ilDeleteImages(1, &tx);

}
