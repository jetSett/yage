#ifndef LOOK_HPP_INCLUDED
#define LOOK_HPP_INCLUDED

#include <string>

namespace Console{

    class Look{
        public:
        virtual ~Look(){}
        virtual void update() = 0;
        virtual void draw() const = 0;
        virtual void show(bool visible) = 0;
        virtual void commandCalled(const std::string&) = 0;
        virtual void textChanged(const std::string&) = 0;
        virtual void error(const std::string&) = 0;
    };

}
#endif // LOOK_HPP_INCLUDED
