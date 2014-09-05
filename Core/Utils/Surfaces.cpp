#include "Surfaces.hpp"
#include "../Memory/NewInc.hpp"

bool operator==(const Rect& r1, const Rect& r2){
    return r1.x == r2.x && r1.y == r2.y && r1.w == r2.w && r1.h == r2.h;
}

Intersection Rect::intersect(const glm::vec2& point) const{
    if(point.x >= x && point.y >= y && point.x <= x + w && point.y <= y + h){
        return INT_IN;
    }else{
        return INT_OUT;
    }
}

Intersection Rect::intersect(const Rect& rect) const{
    glm::ivec2 start; start.x = std::max(x, rect.x); start.y = std::max(y, rect.y);
    glm::ivec2 end; end.x = std::max(x+w, rect.x + rect.w); end.y = std::max(y+h, rect.y + rect.h);

    Rect overlap;
    overlap.x = start.x;
    overlap.y = start.y;
    overlap.w = std::max(w, rect.w);
    overlap.h = std::max(h, rect.h);

    if(start.x > end.x || start.y > end.y){
        return INT_OUT;
    }else if(overlap == *this || overlap == rect){
        return INT_IN;
    }else{
        return INT_INTERSECT;
    }
}
