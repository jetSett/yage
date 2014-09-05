#ifndef IMAGELOADER_INC
#define IMAGELOADER_INC

#include "Resources/Image.hpp"

#include <ResourcesMgr/Loaders.hpp>


class ImagesLoader : public Loader<Image>{
public:
    ImagesLoader();
    ~ImagesLoader();

    virtual Image* loadFromFile(const std::string& file);
    virtual void saveToFile(const Image* obj, const std::string& file);

};


#endif // IMAGELOADER_INC
