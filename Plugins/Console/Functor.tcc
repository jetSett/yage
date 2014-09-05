namespace Console{

    template<class Ret>
    class Function0 : public Function{
        public:

        Function0(Ret(*func)()) : _fonct(func){
        }

        std::string execute(const std::string&){
            return  CallFunction::exec<Ret>(_fonct);
        }
        private:
        Ret(*_fonct)();
    };

    template<class Ret>
    inline Functor bind(Ret(*func)()){
        return Functor(new Function0<Ret>(func));
    }

    template<class Ret, class Arg1>
    class Function1 : public Function{
        public:

        Function1(Ret(*func)(Arg1)) : _fonct(func){
        }

        std::string execute(const std::string& arg){
            typename Base<Arg1>::type a1;
            StringExtractor extract(arg);
            extract(a1);
            return  CallFunction::exec<Ret, Arg1>(_fonct, a1);
        }
        private:
        Ret(*_fonct)(Arg1);
    };

    template<class Ret, class Arg1>
    inline Functor bind(Ret(*func)(Arg1)){
        return Functor(new Function1<Ret, Arg1>(func));
    }

    template<class Ret, class Arg1, class Arg2>
    class Function2 : public Function{
        public:

        Function2(Ret(*func)(Arg1, Arg2)) : _fonct(func){
        }

        std::string execute(const std::string& arg){
            typename Base<Arg1>::type a1;
            typename Base<Arg2>::type a2;
            StringExtractor extract(arg);
            extract(a1);
            extract(a2);

            return  CallFunction::exec<Ret, Arg1, Arg2>(_fonct, a1, a2);
        }
        private:
        Ret(*_fonct)(Arg1, Arg2);
    };


    template<class Ret, class Arg1, class Arg2>
    inline Functor bind(Ret(*func)(Arg1, Arg2)){
        return Functor(new Function2<Ret, Arg1, Arg2>(func));
    }

    template<class Ret, class Arg1, class Arg2, class Arg3>
    class Function3 : public Function{
        public:

        Function3(Ret(*func)(Arg1, Arg2, Arg3)) : _fonct(func){
        }

        std::string execute(const std::string& arg){
            typename Base<Arg1>::type a1;
            typename Base<Arg2>::type a2;
            typename Base<Arg3>::type a3;
            StringExtractor extract(arg);
            extract(a1);
            extract(a2);
            extract(a3);
            return  CallFunction::exec<Ret, Arg1, Arg2, Arg3>(_fonct, a1, a2, a3);
        }
        private:
        Ret(*_fonct)(Arg1, Arg2, Arg3);
    };

    template<class Ret, class Arg1, class Arg2, class Arg3>
    inline Functor bind(Ret(*func)(Arg1, Arg2, Arg3)){
        return Functor(new Function3<Ret, Arg1, Arg2, Arg3>(func));
    }

}
