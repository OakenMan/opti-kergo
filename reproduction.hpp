#ifndef reproduction_hpp
#define reproduction_hpp

#include "Instance.hpp"
#include "Solution.hpp"
#include "vector_methods.hpp"
#include <stdio.h>
#include <vector>

using namespace std;

const unsigned int MIN_CUT_SIZE = 2;   // Taille min d'une coupe  /!\ Si des jours ont moins de 2 POI, mettre celle ci à 1 sinon crash
const unsigned int MAX_CUT_SIZE = 2;   // Nombre de POI en 1 jour - MAX_CUT_SIZE = Taille max d'une coupe (ex: si 8 POI et MAX_CUT_SIZE=2, taille max = 6)

/*
 * Crossover PMX
 * [!] Ne fonctionne pas totalement mais je le garde au cas où
 */
vector<unsigned int> pmx(vector<unsigned int> p1, vector<unsigned int> p2);

/*
 * Crossover OX1
 */
vector<unsigned int> ox1(vector<unsigned int> p1, vector<unsigned int> p2);

/*
 * Mélange 2 vecteurs en fonction d'un pattern généré aléatoirement (possibilité de le générer différement)
 */
vector<unsigned int> shuffle_int(vector<unsigned int> p1, vector<unsigned int> p2);
vector<float> shuffle_float(vector<float> p1, vector<float> p2);

/*
 * Créé une nouvelle solution (enfant) à partir de deux autres solutions (parents)
 */
Solution * faireUnBebe(Solution *papa, Solution *maman);

/*
 * Reproduit une population
 */
vector<Solution*> reproduction(vector<Solution*> population);

#endif
