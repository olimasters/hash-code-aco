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
    Parameters parameters(createParamsFromFile(argv[1]));
    // TODO: tune parameters
    const double pheremoneWeighting = 0.5;
    const double evaporationConstant = 0.6;
    const unsigned colonySize = 20;
    unsigned iterations = 20;
    AntColony colony(pheremoneWeighting, evaporationConstant, colonySize, iterations, parameters);
    Ant bestAnt = colony.findBestAnt();
    printSolution(bestAnt.getSolution());
    std::cout << "Score: " << bestAnt.getScore() << std::endl;
    return 0;
}
