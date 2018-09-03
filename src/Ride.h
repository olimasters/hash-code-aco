#include <Coordinate.h>
#ifndef RIDE_H
#define RIDE_H
struct Ride
{
    Ride(unsigned a, unsigned b, unsigned x, unsigned y, unsigned s, unsigned f) :
        startPosition(a,b),
        endPosition(x,y),
        earliestStart(s),
        latestFinish(f) {} ;
    unsigned distance() const {return dist(startPosition, endPosition);};
    Coordinate startPosition;
    Coordinate endPosition;
    unsigned earliestStart;
    unsigned latestFinish;
};
#endif
