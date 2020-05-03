#ifndef reproduction_hpp
#define reproduction_hpp

#include "Solution.hpp"
#include "Instance.hpp"
#include "vector_methods.hpp"
#include "settings.hpp"

#include <vector>

using namespace std;

const unsigned int MIN_CUT_SIZE = 1;   // Taille min d'une coupe
const unsigned int MAX_CUT_SIZE = 2;   // Nombre de POI en 1 jour - MAX_CUT_SIZE = Taille max d'une coupe (ex: si 8 POI et MAX_CUT_SIZE=2, taille max = 6)

/*
 * Crossover PMX (légèrement modifié)
 * [!] Inutilisé
 */
// vector<unsigned int> pmx(vector<unsigned int> p1, vector<unsigned int> p2);

/*
 * Crossover OX1 (légèrement modifié)
 */
vector<unsigned int> ox1(vector<unsigned int> p1, vector<unsigned int> p2);

/*
 * Applique un algo. de crossover (actuellement OX1) entre p1 et p2 (tableaux des POI visités chaque jour)
 */
vector<vector<unsigned int>> crossover(vector<vector<unsigned int>> p1, vector<vector<unsigned int>> p2);

/*
 * Mélange 2 vecteurs en fonction d'un pattern généré aléatoirement
 */
vector<unsigned int> shuffle_int(vector<unsigned int> *p1, vector<unsigned int> *p2);
vector<float> shuffle_float(vector<float> *p1, vector<float> *p2);

/*
 * Créé une nouvelle solution (enfant) à partir de deux autres solutions (parents)
 */
Solution * reproduce(Solution *p1, Solution *p2, Instance *instance);

/*
 * Reproduit une population
 */
vector<Solution*> reproduction(vector<Solution*> population, Instance *instance);

#endif
