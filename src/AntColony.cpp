#include <AntColony.h>
#include <Ride.h>
#include <PheremoneTrail.h>
#include <vector>
#include <algorithm>

AntColony::AntColony(const double pheremoneWeighting, const double evaporationConstant, const unsigned colonySize, unsigned iterations, const Parameters &parameters) :
    pheremoneWeighting(pheremoneWeighting),
    evaporationConstant(evaporationConstant),
    colonySize(colonySize),
    iterations(iterations),
    ridesToComplete(parameters.allRides),
    T(parameters.T),
    F(parameters.F),
    B(parameters.B)
{
}

Solution AntColony::findBestSolution()
{
    while(iterations--)
    {
        ants.clear();

        std::generate_n(std::back_inserter(ants), colonySize, [&](){return Ant(ridesToComplete, pheremoneWeighting, pheremoneMatrix, T, F, B);});

        for(auto &ant : ants)
            ant.walkToSolution();
        updatePheremoneMatrix();
    }
    // We assume that the last colony of ants will have a very good best ant by this time
    const auto bestAnt = std::max_element(ants.begin(), ants.end(), [&](const Ant &a, const Ant &b){return a.getScore() < b.getScore();});
    return bestAnt->getSolution();
}

void AntColony::updatePheremoneMatrix()
{
    evaporatePheremones();
    for(const auto &ant : ants)
    {
        unsigned score = ant.getScore();
        const PheremoneTrail trail{ant.getPheremoneTrail()};
        addTrailToMatrix(trail, score);
    }
}

void AntColony::addTrailToMatrix(const PheremoneTrail &trail, unsigned score)
{
    for(const auto &indicesPair : trail)
        pheremoneMatrix[indicesPair.first][indicesPair.second] += score;
}

void AntColony::evaporatePheremones()
{
    for(auto &row : pheremoneMatrix)
        for(auto &entry : row)
            entry *= evaporationConstant;
}

