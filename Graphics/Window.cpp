#include "Window.hpp"
#include "WindowsManager.hpp"
#include <Memory/NewInc.hpp>

namespace Graphics {
Window::Window(std::string title, unsigned int width, unsigned int height, unsigned long Flags) : _width(width), _height(height), _window(nullptr), _title(title) {
    _window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, width, height,
                               Flags);
    if(!_window) {
        throw ExternError("SDL2", SDL_GetError());
    }
    _cursorCaptured = false;
}
Window::~Window() {
    if(_window)
        SDL_DestroyWindow(_window);
}
void Window::swapBuffer() {
    SDL_GL_SwapWindow(_window);
}

void Window::captureCursor(bool s) {
    s?SDL_SetWindowGrab(_window, SDL_TRUE):SDL_SetWindowGrab(_window, SDL_FALSE);
    s?SDL_SetRelativeMouseMode(SDL_TRUE):SDL_SetRelativeMouseMode(SDL_FALSE);
    _cursorCaptured = s;
}

}
