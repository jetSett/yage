#ifndef CAMERASMANAGER_HPP
#define CAMERASMANAGER_HPP

#include <string>
#include <map>

#include "Utils/Singleton.hpp"

#include "Memory/SmartPtr.hpp"
#include "Cameras/Camera.hpp"

namespace Graphics{
namespace D3{

    typedef SmartPtr<Camera> CameraPtr;
    typedef std::map<std::string, CameraPtr> CameraMap;

    class CamerasManager : public Singleton<CamerasManager>
    {
    friend class Singleton<CamerasManager>;
    public:
        ~CamerasManager();

        void addCamera(const std::string& name, Camera*);
        CameraPtr getCamera(const std::string& name);
        void setActiveCamera(const std::string& name);

        void update();

    private:

        CamerasManager(){}

        bool exist(const std::string&);

        std::string _activeName;

        CameraMap _cameras;
    };

}
}

#endif // CAMERASMANAGER_HPP
