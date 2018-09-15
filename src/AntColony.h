#ifndef ANTCOLONY_H
#define ANTCOLONY_H

#include <Ant.h>
#include <PheremoneTrail.h>
#include <Parameters.h>
#include <Ride.h>
#include <Solution.h>
#include <vector>

class AntColony
{
    public:
        AntColony(const double pheremoneWeighting, const double evaporationConstant, const unsigned colonySize, unsigned iterations, const Parameters &parameters);
        Ant findBestAnt();
    private:
        void walkAntsToSolutions();
        void walkSubsetOfAnts(const std::vector<std::pair<unsigned, unsigned>> &indexPair);
        void updatePheremoneMatrix();
        void addTrailToMatrix(const PheremoneTrail &trail, unsigned score);
        void evaporatePheremones();
        const double pheremoneWeighting;
        const double evaporationConstant;
        const unsigned colonySize;
        unsigned iterations;
        const std::vector<Ride> &ridesToComplete;
        std::vector<std::vector<double>> pheremoneMatrix;
        std::vector<PheremoneTrail> newPheremoneTrails;
        std::vector<Ant> ants;
        unsigned T;
        unsigned F;
        unsigned B;
};
#endif
