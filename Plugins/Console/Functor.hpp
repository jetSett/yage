#ifndef FUNCTOR_HPP_INCLUDED
#define FUNCTOR_HPP_INCLUDED

#include <string>
#include <tuple>

#include <sstream>

#include "../Utils/Exceptions.hpp"
#include "../Utils/SmartPtr.hpp"
#include "../Utils/Logger.hpp"
#include "../Utils/StringUtilities.hpp"

namespace Console{

    template<typename T>
    struct Base{typedef T type;};

    template <typename T>
    struct Base<T&> {typedef T type;};
    template <typename T>
    struct Base<const T> {typedef T type;};
    template <typename T>
    struct Base<const T&> {typedef T type;};

    class Function{
        public:
            virtual ~Function(){}
            virtual std::string execute(const std::string&) = 0;
    };

    struct CallFunction{
        template<class Ret, class ...Args>
        static std::string exec(Ret(*func)(Args...), Args... arg){
             // Sorry, Functions must return something to be used as functors
             StringPacker pack;
             pack(func(arg...));
            return pack;
        }
    };


    class Functor{
    public:
        Functor(Function* f = nullptr) : _funct(f){}

        std::string operator()(const std::string& param){
            if(!_funct)
                throw PersoException("Erreur : null function in a functer");

            return _funct->execute(param);
        }

    private:
         SmartPtr<Function>_funct;
    };
}

#include "Functor.tcc"

#endif // FUNCTOR_HPP_INCLUDED
