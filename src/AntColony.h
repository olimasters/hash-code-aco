#ifndef ANTCOLONY_H
#define ANTCOLONY_H

#include <vector>

class AntColony
{
    public:
        AntColony(const double pheremoneWeighting, const double evaporationConstant, const unsigned colonySize, unsigned iterations, const std::vector<Ride> &ridesToComplete);
        Solution findBestSolution();
    private:
        void updatePheremoneMatrix();
        void evaporatePheremones();
        const double pheremoneWeighting;
        const double evaporationConstant;
        const unsigned colonySize;
        unsigned iterations;
        const std::vector<Ride> &ridesToComplete;
        std::vector<std::vector<double>> pheremoneMatrix;
        std::vector<PheremoneTrail> newPheremoneTrails;
        std::vector<Ant> ants;
}
#endif
