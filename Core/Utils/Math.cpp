#include "Math.hpp"
#include "../Memory/NewInc.hpp"

unsigned int nearPower2(unsigned int y){
    unsigned int res = 2;
    while(res<y)
        res <<=1;
    unsigned int z = res >> 1;
    return res-y < y-z ? res: z;
}

RandGenerator::RandGenerator(){
    _engine.seed(time(nullptr));
}

double RandGenerator::rand(double beg, double end){
    std::uniform_real_distribution<double> distrib(beg, end);
    return distrib(_engine);
}
