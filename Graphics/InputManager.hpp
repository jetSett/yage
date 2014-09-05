#ifndef INPUT_HPP_INCLUDED
#define INPUT_HPP_INCLUDED

#include <array>
#include <list>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include <Utils/Exceptions.hpp>
#include <Utils/Singleton.hpp>

namespace Graphics{

    struct InputManagement{
        InputManagement(){
            for(bool& b : _keyboard){
                b = false;
            }
            for(bool& b : _mouse){
                b = false;
            }
            for(unsigned int& i : _keyboardLastUsed){
                i = 0;
            }
        }

        std::array<bool, SDL_NUM_SCANCODES> _keyboard;
        std::array<bool, 8> _mouse;
        std::array<unsigned int, SDL_NUM_SCANCODES> _keyboardLastUsed;

    };

    class InputManager : public Singleton<InputManager>, private InputManagement{
        friend class Singleton<InputManager>;
    public:
        void updateEvent();

        void setDelay(unsigned int d){
            _delay = d;
        }

        SDL_Window* getCurrentWindow(){
            return _currentWindow;
        }

        bool stillRunning(){
            return !_finish;
        }

        bool isPressed(const SDL_Scancode s){
            return _keyboard[s];
        }

        bool isPressed(const Uint8 s){
            return _mouse[s];
        }

        bool isPressedSinceDelay(const SDL_Scancode s);

        bool hasMouseMoved(){
            return (_mRelX != 0 or _mRelY != 0);
        }

        void terminate(){
            _finish = true;
        }

        glm::ivec2 posPointer(){
            glm::ivec2 v;
            v.x = _mX;
            v.y = _mY;
            return v;
        }

        int getPointerX(){
            return _mX;
        }

        int getPointerY(){
            return _mY;
        }
        int getPointerXRel(){
            return _mRelX;
        }

        int getPointerYRel(){
            return _mRelY;
        }

        unsigned int getTimeStep(){
            return timeStep;
        }

        void waitKey(SDL_Scancode);
        void addTerminateKey(SDL_Scancode s);


    private:
        void checkTerminateKey();
        InputManager();

        std::list<SDL_Scancode> _terminateKeys;

        int _delay = 50;

        int _mX, _mY;
        int _mRelX, _mRelY;

        bool _finish;

        unsigned int timeStart, timeEnd, timeStep;

        SDL_Event _event;

        SDL_Window* _currentWindow;

    };

}

#endif // INPUT_HPP_INCLUDED
