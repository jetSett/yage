#ifndef CONVERTPIXEL_HPP_INCLUDED
#define CONVERTPIXEL_HPP_INCLUDED

#include <iostream>
#include <string>

#include <Utils/Exceptions.hpp>

enum PixelFormat{
    PXF_L8,
    PXF_A8L8,
    PXF_A1R5G5B5,
    PXF_A4R4G4B4,
    PXF_R8G8B8,
    PXF_A8R8G8B8,
    PXF_DXTC1,
    PXF_DXTC3,
    PXF_DXTC5
};

std::string toString(PixelFormat pf);

template <PixelFormat Pscr, PixelFormat Pdest>
inline void convertPixel(const unsigned char*, unsigned char*) {
    throw UnemplementedFunction(std::string("convertPixel ") + toString(Pscr) + std::string("->") + toString(Pdest));
}

#include "ConvertPixel.tcc"

inline bool isFormatCompressed(PixelFormat pf) {
    switch(pf) {
    case PXF_DXTC1:
    case PXF_DXTC3:
    case PXF_DXTC5:
        return true;
    default:
        return false;
    }
}

inline int getMipLevels(int w, int h) {
    int count = 0;
    while((w > 1) || (h > 1)) {
        if(w > 1) w /= 2;
        if(h > 1) h /= 2;
        ++count;
    }
    return count;
}

inline unsigned int getBytesPerPixel(PixelFormat pf) {
    switch(pf) {
    case PXF_L8:
        return 1;
    case PXF_A8L8:
        return 2;
    case PXF_A1R5G5B5:
        return 2;
    case PXF_A4R4G4B4:
        return 2;
    case PXF_R8G8B8:
        return 3;
    case PXF_A8R8G8B8:
        return 4;
    case PXF_DXTC1:
        return 1;
    case PXF_DXTC3:
        return 2;
    case PXF_DXTC5:
        return 2;
    default:
        return 0;
    }
}

inline void convertPixel(PixelFormat srcPf, const unsigned char* src, PixelFormat destPf, unsigned char* dest) {
#define CONVERSION_FOR(pf) \
            case pf : \
            {\
                switch(destPf) \
                { \
                    case PXF_L8: convertPixel<pf, PXF_L8>(src, dest);break;\
                    case PXF_A8L8: convertPixel<pf, PXF_A8L8>(src, dest);break;\
                    case PXF_A1R5G5B5: convertPixel<pf, PXF_A1R5G5B5>(src, dest);break;\
                    case PXF_A4R4G4B4: convertPixel<pf, PXF_A4R4G4B4>(src, dest);break;\
                    case PXF_R8G8B8: convertPixel<pf, PXF_R8G8B8>(src, dest);break;\
                    case PXF_A8R8G8B8: convertPixel<pf, PXF_A8R8G8B8>(src, dest);break;\
                    case PXF_DXTC1: convertPixel<pf, PXF_DXTC1>(src, dest);break;\
                    case PXF_DXTC3: convertPixel<pf, PXF_DXTC3>(src, dest);break;\
                    case PXF_DXTC5: convertPixel<pf, PXF_DXTC5>(src, dest);break;\
                }\
                break;\
            }
//    std::cout << toString(srcPf) << " -> " << toString(destPf) << std::endl;
    switch(srcPf) {
        CONVERSION_FOR(PXF_L8)
        CONVERSION_FOR(PXF_A8L8)
        CONVERSION_FOR(PXF_A1R5G5B5)
        CONVERSION_FOR(PXF_A4R4G4B4)
        CONVERSION_FOR(PXF_R8G8B8)
        CONVERSION_FOR(PXF_A8R8G8B8)
        CONVERSION_FOR(PXF_DXTC1)
        CONVERSION_FOR(PXF_DXTC3)
        CONVERSION_FOR(PXF_DXTC5)
    }

#undef CONVERSION_FOR

}



#endif // CONVERTPIXEL_HPP_INCLUDED
