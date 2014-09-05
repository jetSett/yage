#include "PixelUtils.hpp"
#include <Memory/NewInc.hpp>

std::string toString(PixelFormat pf){
    switch(pf){
        case PXF_L8:
        return "PXF_L8";
        case PXF_A8L8:
        return "PXF_A8L8";
        case PXF_A1R5G5B5:
        return "PXF_A1R5G5B5";
        case PXF_A4R4G4B4:
        return "PXF_A4R4G4B4";
        case PXF_R8G8B8:
        return "PXF_R8G8B8";
        case PXF_A8R8G8B8:
        return "PXF_A8R8G8B8";
        case PXF_DXTC1:
        return "PXF_DXTC1";
        case PXF_DXTC3:
        return "PXF_DXTC3";
        case PXF_DXTC5:
        return "PXF_DXTC5";
    }
    return "";
}
