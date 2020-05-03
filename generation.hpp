#ifndef generation_hpp
#define generation_hpp

#include "Solution.hpp"
#include "Instance.hpp"

#include <vector>

using namespace std;

const float RATIO_POP = 0.5;  // Ratio population non-réalisable/réalisable (ex: n=100, ratio=0.7 => 70 non-réal, 30 réal)

/*
 * Génère une solution (aléatoirement mais en restant "cohérent") en se basant sur une instance
 * Les solution générées par cette fonction sont presque toutes non-réalisables mais ont souvent une bonne fonction objectif
 */
Solution * generateSolution(Instance *instance);

/*
 * Génère une solution "la plus faisable" possible en se basant sur une instance
 * Les solutions générées par cette fonction sont presque toutes réalisables mais ont souvent une mauvaise fonction objectif
 */
Solution * generateFeasibleSolution(Instance *instance);

/*
 * Génère une population de taille "size"
 */
vector<Solution*> generation(Instance *instance, unsigned int size);

/*
 * Supprime une population
 */
void deletePopulation(vector<Solution*> population);

#endif
