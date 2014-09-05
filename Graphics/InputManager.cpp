#include "InputManager.hpp"
#include <Utils/Logger.hpp>
#include <Memory/NewInc.hpp>

namespace Graphics{

    InputManager::InputManager() : _mX(0), _mY(0), _mRelX(0), _mRelY(0), _finish(false), _currentWindow(nullptr){
        for(unsigned int i = 0; i < SDL_NUM_SCANCODES; ++i){
            _keyboard[i] = false;
            _keyboardLastUsed[i] = 0;
        }
        for(unsigned int i = 0; i < 8; ++i){
            _keyboard[i] = false;
        }
        timeStart = SDL_GetTicks();
    }


    void InputManager::updateEvent(){
        _mRelX = 0;
        _mRelY = 0;

        timeEnd = SDL_GetTicks();
        timeStep = timeEnd-timeStart;
        for(unsigned int& i : _keyboardLastUsed){
            if(i != 0){
                i-= timeStep;
            }
        }

        while(SDL_PollEvent(&_event)){
            switch(_event.type){
            case SDL_KEYDOWN:{
                _keyboard[_event.key.keysym.scancode] = true;
                _keyboardLastUsed[_event.key.keysym.scancode] = _delay;
                break;
            }
            case SDL_KEYUP:
                _keyboard[_event.key.keysym.scancode] = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                _mouse[_event.button.button] = true;
                if(!_terminateKeys.empty()){
                    if(std::find(_terminateKeys.begin(), _terminateKeys.end(), _event.key.keysym.scancode) != _terminateKeys.end()){
                        _finish = true;
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                _mouse[_event.button.button] = false;
                break;
            case SDL_MOUSEMOTION:
                _mX = _event.motion.x;
                _mY = _event.motion.y;
                _mRelX = _event.motion.xrel;
                _mRelY = _event.motion.yrel;
                break;
            case SDL_WINDOWEVENT:
                _currentWindow = SDL_GetWindowFromID(_event.window.windowID);
                if(_currentWindow == 0){
                    throw ExternError("SDL2", SDL_GetError());
                }
                if(_event.window.event == SDL_WINDOWEVENT_CLOSE)
                    _finish = true;
                break;
            default:
                break;
            }
        }
    }

    bool InputManager::isPressedSinceDelay(const SDL_Scancode s){
        if(_keyboardLastUsed[s] != 0){
            _keyboardLastUsed[s] = 0;
            return true;
        }else{
            return false;
        }
    }

    void InputManager::waitKey(SDL_Scancode s){
        SDL_Event e;
        bool cont = true;
        while(cont){
            SDL_WaitEvent(&e); /// \todo ajouter une fonction quittant avec SDL_WINDOWEVENT_CLOSE, pour l'instant on peut pas
            switch(e.type){
            case SDL_WINDOWEVENT:
                _currentWindow = SDL_GetWindowFromID(e.window.windowID);
                if(_currentWindow == 0){
                    throw ExternError("SDL2", SDL_GetError());
                }
                if(_event.window.event == SDL_WINDOWEVENT_CLOSE){
                    terminate();
                    cont = false;
                }
                break;
            case SDL_KEYDOWN:
                if(e.key.keysym.scancode == s)
                    cont = false;
                else if(!_terminateKeys.empty()){
                    if(std::find(_terminateKeys.begin(), _terminateKeys.end(), e.key.keysym.scancode) != _terminateKeys.end()){
                        terminate();
                        cont = false;
                    }
                }
                break;
            default:
                break;
            }
        }
    }

    void InputManager::addTerminateKey(SDL_Scancode s){
        _terminateKeys.push_back(s);
    }

}
