#include <Utils.h>
#include <iostream>
#include <fstream>
#include <vector>

std::vector<unsigned int> getLineOfIntegers(std::istream &is)
{
    std::vector<unsigned int> result;
    std::string line;
    std::string number;
    std::getline(is, line);
    for(char &c : line)
    {
        if(c == ' ')
        {
            result.push_back(std::stoi(number));
            number.clear();
        }
        else
            number += c;
    }
    if(line.length() > 0)   // We will have missed the last number
        result.push_back(std::stoi(number));
    return result;
}

Scorer createScorerFromFile(std::string inputFilename)
{
    unsigned R, C, F, N, B, T;
    std::vector<Ride> rides;
    std::ifstream inputFile;
    inputFile.exceptions(std::ifstream::badbit);
    inputFile.open(inputFilename);
    std::vector<unsigned int> metadata(getLineOfIntegers(inputFile));
    R = metadata[0];
    C = metadata[1];
    F = metadata[2];
    N = metadata[3];
    B = metadata[4];
    T = metadata[5];
    rides.reserve(N);
    for(unsigned i = 0; i < N; i++)
    {
        unsigned a, b, x, y, s, f;
        std::vector<unsigned> rideData(getLineOfIntegers(inputFile));
        a = rideData[0];
        b = rideData[1];
        x = rideData[2];
        y = rideData[3];
        s = rideData[4];
        f = rideData[5];
        rides.push_back(Ride{a, b, x, y, s, f});
    }
    return Scorer{R, C, F, N, B, T, rides};
}

Parameters getParamsFromFile(std::string inputFilename)
{
    unsigned R, C, F, N, B, T;
    std::vector<Ride> rides;
    std::ifstream inputFile;
    inputFile.exceptions(std::ifstream::badbit);
    inputFile.open(inputFilename);
    std::vector<unsigned int> metadata(getLineOfIntegers(inputFile));
    R = metadata[0];
    C = metadata[1];
    F = metadata[2];
    N = metadata[3];
    B = metadata[4];
    T = metadata[5];
    rides.reserve(N);
    for(unsigned i = 0; i < N; i++)
    {
        unsigned a, b, x, y, s, f;
        std::vector<unsigned> rideData(getLineOfIntegers(inputFile));
        a = rideData[0];
        b = rideData[1];
        x = rideData[2];
        y = rideData[3];
        s = rideData[4];
        f = rideData[5];
        rides.push_back(Ride{a, b, x, y, s, f});
    }
    return Parameters{R, C, F, N, B, T, rides};
}

void normalise(std::vector<double> &numbers)
{
    double sum = std::accumulate(numbers.begin(), numbers.end());
    for(double &number : numbers)
        number /= sum;
}
