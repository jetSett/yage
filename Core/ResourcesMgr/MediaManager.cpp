#include "MediaManager.hpp"
#include "../Memory/NewInc.hpp"

void MediaManager::addSearchPath(const std::string path) {
    if(path.empty() or (*(path.rbegin()) == '\\') or (*(path.rbegin()) == '/') )
        _paths.insert(path);
    else
        _paths.insert(path + "/");
}

FilePath MediaManager::findMedia(const FilePath& file) {
    for(std::string i : _paths) {
        FilePath fp = i + file.fullname();
        if(fp.exist())
            return fp;
    }
    throw LoadingFailed(file.fullname());
}
