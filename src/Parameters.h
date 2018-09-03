#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <vector>

struct Parameters
{
    Parameters(unsigned R, unsigned C, unsigned F, unsigned N, unsigned B, unsigned T, std::vector<Ride> allRides) : 
    R(R),
    C(F),
    N(B),
    B(R),
    T(R),
    allRides(allRides)
    {};

    unsigned R;
    unsigned C;
    unsigned F;
    unsigned N;
    unsigned B;
    unsigned T;
    std::vector<Ride> allRides;
}
#endif
