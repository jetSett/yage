#include "Console.hpp"

namespace Console{

    void Console::registerCommand(const std::string& name, const Functor& func){
        _commandTable[name] = func;
    }

    void Console::processCurrent(){
        std::string command;
        std::istringstream iss(_current);
        iss >> command;

        FunctorMap::iterator it = _commandTable.find(command);
        if(it != _commandTable.end()){
            std::string param;
            std::getline(iss, param);
            it->second(param);
        }else{
            _look->error("unknown command");
        }
    }

    void Console::sendCar(char car){
        switch(car){
        case '\n':
        case '\r':
            if(!_current.empty()){
                processCurrent();
                _current.clear();
            }
            break;
        case '\b':
            if(!_current.empty()){
                _current.erase(_current.size()-1);
            }
            break;
        default:
            _current += car;
        }
    }

}
