#ifndef mutation_hpp
#define mutation_hpp

#include "Instance.hpp"
#include "Solution.hpp"
#include "vector_methods.hpp"
#include <stdio.h>
#include <vector>

using namespace std;

const float MUTATION_CHANCE = 0.1;

const float MAX_CHANGE_ON_DATE = 5.0;

// Probabilités de mutation, en %
const float PROBA_MUT_HOTEL = 1;
const float PROBA_MUT_POI = 5;
const float PROBA_MUT_DATE = 5;

void muter_Hotels_Intermediares(Solution *solution, unsigned int nbHotels);

void muter_Sequence_POI(Solution *solution, unsigned int nbPOI);

void muter_Date_Depart(Solution *solution, float dateMax);

/*
 * Fait muter une solution
 */
void muter(Solution *solution, Instance *instance);

/*
 * Effectue des mutations sur une population
 */
void mutation(vector<Solution*> population, Instance *instance);

#endif
