#include <AntColony.h>
#include <Utils.h>
#include <Ride.h>
#include <PheremoneTrail.h>
#include <vector>
#include <algorithm>
#include <thread>
#include <utility>
#include <cstdlib>
#include <iostream>

AntColony::AntColony(const double pheremoneWeighting, const double evaporationConstant, const unsigned colonySize, unsigned iterations, const Parameters &parameters) :
    pheremoneWeighting(pheremoneWeighting),
    evaporationConstant(evaporationConstant),
    colonySize(colonySize),
    iterations(iterations),
    ridesToComplete(parameters.allRides),
    pheremoneMatrix(ridesToComplete.size(), std::vector<double>(ridesToComplete.size())),
    T(parameters.T),
    F(parameters.F),
    B(parameters.B)
{
}

Ant AntColony::findBestAnt()
{
    for(unsigned i = 0; i < iterations; i++)
    {
        ants.clear();
        std::generate_n(std::back_inserter(ants), colonySize, [&](){return Ant(ridesToComplete, pheremoneWeighting, pheremoneMatrix, T, F, B);});
        // for(auto &ant : ants)
            // ant.walkToSolution();
        walkAntsToSolutions();
        updatePheremoneMatrix();
        // Progress indicator:
        std::cout << "Completed iteration " << i+1 << " of " << iterations << std::endl;
    }
    // We assume that the last colony of ants will have a very good best ant by this time
    const auto bestAnt = std::max_element(ants.begin(), ants.end(), [&](const Ant &a, const Ant &b){return a.getScore() < b.getScore();});
    return *bestAnt;
}


void AntColony::walkAntsToSolutions()
{
    const char *threadCount = std::getenv("ACO_THREAD_COUNT");
    unsigned numberOfThreads = 4; // Defaulting to a value I found experimentally fast
    if(threadCount != NULL)
    {
        numberOfThreads = std::stoi(threadCount);
    }
    std::vector<std::pair<unsigned, unsigned>> antIndicesForEachThread{getIndexPairs(numberOfThreads, ants.size())};
    std::vector<std::thread> antWalkingThreads;
    antWalkingThreads.reserve(numberOfThreads);
    for(const auto &indexPair : antIndicesForEachThread)
        antWalkingThreads.push_back(std::thread(&AntColony::walkSubsetOfAnts, this, indexPair));
    for(auto &antWalkingThread : antWalkingThreads)
        antWalkingThread.join();

}

void AntColony::walkSubsetOfAnts(const std::pair<unsigned, unsigned> &indexPair)
{
    for(unsigned i = indexPair.first; i <= indexPair.second; i++)
        ants[i].walkToSolution();
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

