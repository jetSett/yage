#include "Color.hpp"

namespace Graphics{

    Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a){
        _a = a;
        _r = r;
        _g = g;
        _b = b;
    }

    Color::Color(unsigned long c){
        //on prend le a
        unsigned long mask = 0xFF000000;
        _a = (c&mask)/pow(16, 6);
        //on prend le r
        mask = 0x00FF0000;
        _r = (c&mask)/pow(16, 4);
        //on prend le g
        mask = 0x0000FF00;
        _g = (c&mask)/pow(16, 2);
        //on prend le b
        mask = 0x000000FF;
        _b = c&mask;

    }

    void Color::setFloats(float r, float g, float b, float a){
        _a = (unsigned char)(a*255);
        _r = (unsigned char)(r*255);
        _g = (unsigned char)(g*255);
        _b = (unsigned char)(b*255);
    }

    void Color::setUChar(unsigned char r, unsigned char g, unsigned char b, unsigned char a){
        _a = a;
        _r = r;
        _g = g;
        _b = b;
    }

    unsigned long Color::toABGR() const{
        unsigned long col = _a;
        col <<= 8;
        col += _b;
        col <<= 8;
        col += _g;
        col <<= 8;
        col += _r;
        return col;
    }

    unsigned long Color::toARGB() const{
        unsigned long col = _a;
        col <<= 8;
        col += _r;
        col <<= 8;
        col += _g;
        col <<= 8;
        col += _b;
        return col;
    }

    unsigned long Color::toRBGA() const{
        unsigned long col = _r;
        col <<= 8;
        col += _b;
        col <<= 8;
        col += _g;
        col <<= 8;
        col += _a;
        return col;
    }

}
