#include <vector>
#include <unordered_map>
#include <Solution.h>
#include <Ride.h>
#include <Vehicle.h>

#ifndef SCORER_H
#define SCORER_H
class Scorer
{
    public:
        Scorer(unsigned R, unsigned C, unsigned F, unsigned N, unsigned B, unsigned T, std::vector<Ride> allRides);
        Scorer(const Parameters &params);
        unsigned calculateScore(const Solution &solution) const;
        const std::vector<Ride> & getRidesToPerform() const;

    private:
        // TODO: half of this isn't needed
        std::vector<std::vector<Ride>> assignmentToSetOfRideLists(std::vector<unsigned> assignment) const;
        unsigned getScore (const std::vector<Ride> &lateCompletedRides, const std::vector<Ride> &timelyRides) const;
        std::vector<std::vector<Ride>> makeVehicleTable(const std::vector<std::vector<unsigned>> bucketsOfIndices) const;
        unsigned R;
        unsigned C;
        unsigned F;
        unsigned N;
        unsigned B;
        unsigned T;
        std::vector<Ride> allRides;
};
#endif
