#include <fstream>
#include <iostream>
#include <Utils.h>
#include <AntColony.h>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <input filepath>\n", argv[0]);
        return 1;
    }
    Parameters parameters(getParamsFromFile(argv[1]));
    Scorer scorer(parameters);
    // TODO: tune parameters
    double pheremoneWeighting = 0.5;
    unsigned colonySize = 150;
    unsigned iterations = 50;
    AntColony colony(pheremoneWeighting, colonySize, iterations parameters.allRides);
    Solution bestSolution{colony.findBestSolution()};
    std::cout << scorer.calculateScore(bestSolution) << std::endl;
    return 0;
}
