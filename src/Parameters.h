#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <Ride.h>
#include <vector>

struct Parameters
{
    Parameters(unsigned R, unsigned C, unsigned F, unsigned N, unsigned B, unsigned T, std::vector<Ride> allRides) : 
    R(R),
    C(C),
    F(F),
    N(N),
    B(B),
    T(T),
    allRides(allRides)
    {};

    unsigned R;
    unsigned C;
    unsigned F;
    unsigned N;
    unsigned B;
    unsigned T;
    std::vector<Ride> allRides;
};
#endif
