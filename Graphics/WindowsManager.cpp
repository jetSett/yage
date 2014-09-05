#include "WindowsManager.hpp"
#include <Memory/NewInc.hpp>

namespace Graphics{

    WindowsManager::WindowsManager() : Singleton<WindowsManager>()
    {
        _windows.clear();
        if(SDL_Init(SDL_INIT_VIDEO)>0){
            throw ExternError("SDL2", SDL_GetError());
        }
    }

    WindowsManager::~WindowsManager()
    {
        _windows.clear();
        SDL_Quit();
    }

    WindowPtr WindowsManager::getWindow(const std::string& nom){
        if(_windows.find(nom) == _windows.end()){
            throw BadIndex("WindowsManager::getWindow");
        }
        return _windows[nom];
    }

    void WindowsManager::createWindow(const std::string& nom, unsigned int w, unsigned int h, unsigned long f){
        _windows[nom] = new Window(nom, w, h, f);
    }
}
