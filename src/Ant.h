#ifndef ANT_H
#define ANT_H

#include <Solution.h>
#include <Ride.h>
#include <vector>

class Ant
{
    public:
        Ant(const std::vector<Ride> &ridesToComplete, double pheremoneWeighting, const std::vector<std::vector<double>> &pheremoneMatrix, unsigned T, unsigned F, unsigned B);
        void walkToSolution();
        Solution getSolution() const;
        unsigned getScore() const;

    private:
        std::vector<Vehicle> getFreeVehicles() const;
        // TODO: fix this, if it needs to know about all this stuff then wrap it up into a Parameters struct
        unsigned T;
        unsigned F;
        unsigned B;

        unsigned currentTime;
        std::vector<Vehicle> fleet;
        const std::vector<Ride> &ridesToComplete;
        const std::vector<std::vector<double>> &pheremoneMatrix;
}
#end
