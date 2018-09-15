#ifndef UTILS_H
#define UTILS_H
#include <Parameters.h>
#include <iostream>
#include <vector>
#include <utility>
std::vector<std::pair<unsigned, unsigned>> getIndexPairs(unsigned threads, unsigned jobs);
std::vector<unsigned int> getLineOfIntegers(std::istream &is);
Parameters createParamsFromFile(std::string inputFilename);
void normalise(std::vector<double> &numbers);
#endif
