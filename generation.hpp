#ifndef generation_hpp
#define generation_hpp

#include "Instance.hpp"
#include "Solution.hpp"

using namespace std;

/* Ratio population non-réalisable/réalisable (ex: n=100, ratio=0.7 => 70 non-réal, 30 réal)
 * Faut pas mettre un ratio trop précis sinon ça fout le zbeul avec les virgules et tout tavu
 */
const float RATIO_POP = 0.5;

/*
 * Génère une solution (réalisable ou non) basée sur une instance
 */
Solution * generateSolution(Instance *instance);


Solution * generateFeasibleSolution(Instance *instance);

/*
 * Génère une population de taille "size", basée sur une instance
 */
vector<Solution*> generation(Instance *instance, unsigned int size);

/*
 * Supprime une population
 */
void deletePopulation(vector<Solution*> population);

#endif
