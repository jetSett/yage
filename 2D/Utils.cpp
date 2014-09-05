#include "Utils.hpp"
#include <Memory/NewInc.hpp>

namespace Graphics{
namespace D2{
    unsigned long convertEnum(PixelFormat pf){
        switch(pf){
        case PXF_A1R5G5B5:
            return SDL_PIXELFORMAT_ARGB1555;
        case PXF_A4R4G4B4:
            return SDL_PIXELFORMAT_ARGB4444;
        case PXF_A8R8G8B8:
            return SDL_PIXELFORMAT_ARGB8888;
        case PXF_R8G8B8:
            return SDL_PIXELFORMAT_RGB888;

            default:
                return SDL_PIXELFORMAT_UNKNOWN;
        }
    }
}
}
