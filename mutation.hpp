#ifndef mutation_hpp
#define mutation_hpp

#include "Solution.hpp"
#include "Instance.hpp"
#include "vector_methods.hpp"
#include "settings.hpp"

#include <vector>

using namespace std;

/*
 * Fait muter la liste des hôtels intermédiaires d'une solution
 * (choisit un jour au hasard, et change l'hôtel par un autre)
 */
void muter_Hotels_Intermediares(Solution *solution, unsigned int nbHotels);

/*
 * Fait muter les séquences de POI d'une solution
 * (choisit un jour au hasard, et y supprime ou ajoute un POI)
 */
void muter_Sequence_POI(Solution *solution, unsigned int nbPOI);

/*
 * Fait muter le vecteur des dates de départ d'une solutions
 * (augmente ou diminue aléatoirement la date de départ)
 */
void muter_Date_Depart(Solution *solution, float dateMax, Settings *settings);

/*
 * Fait muter une solution
 */
void mutate(Solution *solution, Instance *instance, Settings *settings);

/*
 * Effectue des mutations sur une population
 */
void mutation(vector<Solution*> population, Instance *instance, Settings *settings);

#endif
