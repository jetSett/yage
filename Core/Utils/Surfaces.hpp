#ifndef SURFACES_HPP_INCLUDED
#define SURFACES_HPP_INCLUDED

#include <algorithm>
#include <glm/glm.hpp>

enum Intersection{
    INT_IN, INT_OUT, INT_INTERSECT
};

struct Rect{
    int x, y;
    int w, h;

    Intersection intersect(const glm::vec2& point) const;
    Intersection intersect(const Rect& rect) const;
};

bool operator==(const Rect& r1, const Rect& r2);

#endif // SURFACES_HPP_INCLUDED
