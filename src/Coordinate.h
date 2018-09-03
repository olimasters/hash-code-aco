#include <cmath>
#ifndef COORDINATE_H
#define COORDINATE_H

struct Coordinate
{
    Coordinate(unsigned x, unsigned y) : x(x), y(y) {};
    bool operator==(const Coordinate &other){return x == other.x && y == other.y;};
    unsigned x;
    unsigned y;
};

inline unsigned dist(const Coordinate &a, const Coordinate &b)
{
    return std::abs((int)a.x - (int)b.x) + std::abs((int)a.y - (int)b.y);
};

#endif
