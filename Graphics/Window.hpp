#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <string>
#include <SDL2/SDL.h>

#include "InputManager.hpp"


namespace Graphics{

    class WindowsManager;

    class Window {
    friend class WindowsManager;
    public:
        ~Window();
        void swapBuffer();
        inline std::string getTitle(){
            return _title;
        }
        inline SDL_Window* getSDLWindow(){
            return _window;
        }
        inline unsigned int getWidth(){
            return _width;
        }

        inline unsigned int getHeight(){
            return _height;
        }

        void captureCursor(bool s);

        bool isCursorCaptured(){
            return _cursorCaptured;
        }

    protected:
        Window(std::string title, unsigned int width = 800, unsigned int height = 600, unsigned long Flags = 0);
        unsigned int _width, _height;
        SDL_Window* _window;
        std::string _title;
        bool _cursorCaptured;
    };
}

#endif // WINDOW_H_INCLUDED
