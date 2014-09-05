#ifndef COLOR_H
#define COLOR_H

#include <Utils/Math.hpp>

namespace Graphics{

    class Color{
    public:
        Color(unsigned long c = 0xFF000000); //from ARGB !!!!!
        Color(unsigned char r, unsigned char g, unsigned char b,unsigned char a = 0xFF);

        void setFloats(float r, float g, float b, float a = 1.0f);
        void setUChar(unsigned char r, unsigned char g, unsigned char b,unsigned char a = 0xFF);

        unsigned long toARGB() const;
        unsigned long toABGR() const;
        unsigned long toRBGA() const;

        inline unsigned char getAlpha() const{
            return _a;
        }

        inline unsigned char getRed() const{
            return _r;
        }

        inline unsigned char getBlue() const{
            return _b;
        }

        inline unsigned char getGreen() const{
            return _g;
        }

        bool operator==(const Color& c){
            return ( (c._a == _a) &&
                    (c._b == _b) &&
                     (c._r == _r) &&
                     (c._g == _g) );
        }

        void toFloats(float* f){
            f[0] = (float)_r/255;
            f[1] = (float)_g/255;
            f[2] = (float)_b/255;
            f[3] = (float)_a/255;
        }

        static const unsigned long Red = 0xFFFF0000;
        static const unsigned long Green = 0xFF00FF00;
        static const unsigned long Blue = 0xFF0000FF;
        static const unsigned long White = 0xFFFFFFFF;
        static const unsigned long Black = 0xFF000000;


    private:
        unsigned char _a, _r, _g, _b;
    };

}
#endif // COLOR_H
