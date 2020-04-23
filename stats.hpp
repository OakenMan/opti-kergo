#ifndef stats_hpp
#define stats_hpp

#include "Solution.hpp"

#include <iostream>

using namespace std;

const bool DEBUG = false;

unsigned int bestSolution(vector<Solution*> population, bool onlyFeasible);

float bestRatio(vector<Solution*> population);

float averageScore(vector<Solution*> population, bool onlyFeasible);

float averateRatio(vector<Solution*> population);

vector<unsigned int> diversity(vector<Solution*> population);

void analyse(vector<Solution*> population);

void analyseOneLine(vector<Solution*> population);

#endif
