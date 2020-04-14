#ifndef generation_hpp
#define generation_hpp

#include "Instance.hpp"
#include "Solution.hpp"
#include <stdio.h>
#include <vector>

using namespace std;

/*
 * Génère une solution (réalisable ou non) basée sur une instance
 */
Solution * generateSolution(Instance *instance);

/*
 * Génère une population de taille "size", basée sur une instance
 */
vector<Solution*> generation(Instance *instance, unsigned int size);

/*
 * Supprime une population
 */
void deletePopulation(vector<Solution*> population);

#endif
