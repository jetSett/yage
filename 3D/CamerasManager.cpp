#include "CamerasManager.hpp"
#include <Memory/NewInc.hpp>

namespace Graphics{
namespace D3{

    bool CamerasManager::exist(const std::string& name){
        return _cameras.find(name) != _cameras.end();
    }

    void CamerasManager::addCamera(const std::string& name, Camera* cam){
        assert(cam != nullptr);
        if(exist(name))
            throw PersoException("Camera " + name + "ever exist");
        CameraPtr ptr(cam);
        _cameras[name] = ptr;
        _activeName = name;
    }

    void CamerasManager::setActiveCamera(const std::string& name){
        if(!exist(name))
            throw BadIndex("setActiveCamera : " + name);
        _activeName = name;
    }

    CameraPtr CamerasManager::getCamera(const std::string& name){
        if(!exist(name))
            throw BadIndex("getCamera : " + name);
        return _cameras[name];
    }

    void CamerasManager::update(){
        if(_cameras.empty())
            throw BadIndex("CamerasManager::update");
        _cameras[_activeName]->update();
    }

    CamerasManager::~CamerasManager(){}

}
}
