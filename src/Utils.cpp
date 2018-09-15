#include <Utils.h>
#include <Parameters.h>
#include <numeric>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

std::vector<std::pair<unsigned, unsigned>> getIndexPairs(unsigned threads, unsigned jobs)
{
    std::vector<std::pair<unsigned, unsigned>> results;
    unsigned jobsPerThread = jobs / threads;
    unsigned workaholicThreads = jobs % threads;
    for(unsigned i = 0; i < (threads - workaholicThreads) * jobsPerThread; i += jobsPerThread)
    {
        results.push_back(std::pair<unsigned, unsigned>{i, i + jobsPerThread - 1});
    }
    for(unsigned i = (threads - workaholicThreads) * jobsPerThread; i < jobs - jobsPerThread; i += jobsPerThread + 1)
    {
        results.push_back(std::pair<unsigned, unsigned>{i, i + jobsPerThread});
    }
    return results;
}

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

Parameters createParamsFromFile(std::string inputFilename)
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
        rides.push_back(Ride{a, b, x, y, s, f, i});
    }
    return Parameters{R, C, F, N, B, T, rides};
}

void normalise(std::vector<double> &numbers)
{
    double sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    if(sum == 0)
        for(double &number : numbers)
            number = 1.0/numbers.size();
    else
        for(double &number : numbers)
            number /= sum;
}
