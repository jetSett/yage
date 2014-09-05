#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

#include <random>
#include "Singleton.hpp"

//template<int n>
//inline unsigned long pow(unsigned long a){
//    return a*pow<n-1>(a);
//}
//
//template<>
//inline unsigned long pow<0>(unsigned long){
//    return 1;
//}

constexpr unsigned long pow(unsigned long a, int n){
    return n==1?a:a*pow(a, n-1);
}

unsigned int nearPower2(unsigned int y);

class RandGenerator : public Singleton<RandGenerator>{
    friend class Singleton<RandGenerator>;
public:
    double rand(double beg, double end);
private:
    std::default_random_engine _engine;
    RandGenerator();
};

#endif // MATH_H_INCLUDED
