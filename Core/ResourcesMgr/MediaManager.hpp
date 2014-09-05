#ifndef MEDIAMANAGER_HPP
#define MEDIAMANAGER_HPP

#include <map>
#include <set>
#include <string>
#include <algorithm>

#include "../Utils/Metaprog.hpp"
#include "../Memory/SmartPtr.hpp"
#include "../Utils/FilePath.hpp"
#include "../Utils/StringUtilities.hpp"
#include "../Utils/Singleton.hpp"
#include "Loaders.hpp"


//ici mettre tous les fichiers contenus dans les dossiers Resources
#include "../../3D/Resources/Model.hpp"
#include "../../Graphics/Resources/Image.hpp"
#include "../../3D/Resources/ShaderBase.hpp"
#include "../../Sounds/Resources/Sound.hpp"

typedef TYPELIST_4(Model, Image, ShaderBase, Sound) Medias;

template<class T>
struct MediaHolder{
    typedef std::map<std::string, SmartPtr<Loader<T>>> LoaderMap;
    LoaderMap _loaders;
};


class MediaManager : public ScatteredHierarchy<Medias, MediaHolder>, public Singleton<MediaManager>
{
    friend class Singleton<MediaManager>;
    public:


        void addSearchPath(const std::string path);

        FilePath findMedia(const FilePath& file);

        template <class T> inline T* loadMediaFromFile(const FilePath& file){
            FilePath path = findMedia(file);
            return findLoader<T>(path).load(path.fullname());
        }

        template <class T> inline void saveMediaToFile(const T* obj, const FilePath& file){
            findLoader<T>(file).saveToFile(obj, file.fullname());
        }

        template <class T> inline Loader<T>& findLoader(const FilePath& file){
            std::string ext = file.extension();

            ext = toLower(ext);

            typename MediaHolder<T>::LoaderMap::iterator it = MediaHolder<T>::_loaders.find(ext);

            if(it != MediaHolder<T>::_loaders.end() and it->second)
                return *it->second;
            throw LoadingFailed(file.filename() + std::string(" Loader not found"));
        }

        template <class T> inline void registerLoader(Loader<T>* loader, const std::string ext){
            std::vector<std::string> extensions;
            split(ext, extensions, " /\\*.,;|-_\t\n'\"");

            SmartPtr<Loader<T>> ptr = loader;
            for(std::string str : extensions){
                str = toLower(str);
                MediaHolder<T>::_loaders[str] = ptr;
            }
        }

    private:
        MediaManager(){
            _paths.insert("");
        }
        std::set<std::string> _paths;
};

#endif // MEDIAMANAGER_HPP
