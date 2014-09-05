#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <map>
#include <string>
#include <sstream>

#include "../Utils/Singleton.hpp"
#include "../Utils/SmartPtr.hpp"

#include "Functor.hpp"
#include "Look.hpp"

namespace Console{

    class Console : public Singleton<Console>
    {
        public:
        friend class Singleton<Console>;

        void registerCommand(const std::string& name, const Functor& func);
        void sendCar(char car);
        void enable(bool e){
            _enabled = e;
        }

        void update();

        void changeLook(Look* newLook);

        private:

            Console(){}

            void processCurrent();

            typedef std::map<std::string, Functor> FunctorMap;
            FunctorMap _commandTable;

            SmartPtr<Look> _look;

            std::string _current;
            bool _enabled;
    };

}
#endif // CONSOLE_HPP
