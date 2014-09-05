#ifndef STRINGUTILITIES_HPP_INCLUDED
#define STRINGUTILITIES_HPP_INCLUDED

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

#include "Exceptions.hpp"

inline void split(const std::string& str, std::vector<std::string>& tokens, const std::string& delim = " \t\n"){
    tokens.clear();
    for(std::string::size_type p1 = 0, p2 = 0; p1 != std::string::npos; ){
        p1 = str.find_first_not_of(delim, p1);
        if(p1 != std::string::npos){
            p2 = str.find_first_of(delim, p1);
            tokens.push_back(str.substr(p1, p2-p1));
            p1 = p2;
        }
    }
}

inline bool isDigit(const std::string& s){
    return !s.empty() && (std::find_if(s.begin(), s.end(), [](char c){return !std::isdigit(c);}) == s.end());
}

inline std::string toLower(const std::string& str){
    std::string ret(str.size(), ' ');
    std::transform(str.begin(), str.end(), ret.begin(), static_cast<int (*)(int)>(std::tolower));
    return ret;
}

class StringExtractor{
public:
    StringExtractor(const std::string& str) : iss(str){}

    template<class T>
    void operator()(T& a){
        if(!(iss>>a)){
            if(iss.str().empty()){
                throw PersoException("Cannot extract value from an empty string");
            }else{
                throw PersoException("Cannot extract value from the given string");
            }
        }
    }

private:
    std::istringstream iss;
};

class StringPacker{
    public:

    template<class T>
    void operator()(T v){
        if(!oss << v){
            throw PersoException("cannot pack value of the given variable");
        }
    }

    operator std::string(){
    return oss.str();
    }

    private:
        std::ostringstream oss;
};

#endif // STRINGUTILITIES_HPP_INCLUDED
