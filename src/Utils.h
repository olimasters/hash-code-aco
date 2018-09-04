#include <Scorer.h>
#include <iostream>
#include <vector>
#ifndef UTILS_H
#define UTILS_H
std::vector<unsigned int> getLineOfIntegers(std::istream &is);
Scorer createScorerFromFile(std::string inputFilename);
void normalise(std::vector<double> &numbers);
#endif
