#ifndef WINDOWSMANAGER_H
#define WINDOWSMANAGER_H

#include <map>
#include <string>
#include <exception>

#include <Memory/SmartPtr.hpp>
#include <Utils/Exceptions.hpp>
#include <Utils/Singleton.hpp>
#include "Window.hpp"

namespace Graphics{
    typedef SmartPtr<Window> WindowPtr;
    typedef std::map<std::string, WindowPtr> WindowsMap;

    class WindowsManager : public Singleton<WindowsManager>{
        friend class Singleton<WindowsManager>;
        public:
            ~WindowsManager();
            WindowPtr getWindow(const std::string&);
            void createWindow(const std::string& nom, unsigned int w, unsigned int h, unsigned long f = 0);

            const WindowsMap& getWindows() const{
                return _windows;
            }

        private:
            WindowsManager();
            WindowsMap _windows;
            Window* _activeWindow;
    };


}
#endif // WINDOWSMANAGER_H
