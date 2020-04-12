#ifndef reproduction_hpp
#define reproduction_hpp

#include "Solution.hpp"
#include <stdio.h>
#include <vector>

using namespace std;

const unsigned int MIN_CUT_SIZE = 2;
const unsigned int MAX_CUT_SIZE = 2;

/**
 * Applique un algorithme PMX (Partial-Mapped-Crossover) légèrement modifié (pour gérer des cas de tableaux de taille différentes
 * ou avec des éléments différents) à deux tableaux représentant des séquences de POI pour un jour de voyage.
 * > params :
 * p1 : parent 1
 * p2 = parent 2
 * > return :
 * un vecteur "enfant", de la taille de p2, constitué d'un mélange entre p1 et p2
 * > complexité :
 * au mieux, O(4n), au pire O(n²)
 * > vitesse :
 * ~60.000/s pour n1=n2=7
 */
vector<unsigned int> pmx(vector<unsigned int> p1, vector<unsigned int> p2);

/**
 * Génère un pattern (pour l'instant aléatoire) sous la forme d'un tableau de 0 et de 1. Ensuite, on parcout le pattern,
 * si c'est 0, child prendra la valeur de p1, si c'est 1, child prendra la valeur de p2.
 * > complexité : O(2n)
 */
vector<unsigned int> shuffle_int(vector<unsigned int> p1, vector<unsigned int> p2);
vector<float> shuffle_float(vector<float> p1, vector<float> p2);


/**
 * Créé une nouvelle solution (enfant) à partir de deux autres solutions (parents)
 */
Solution faireUnBebe(Solution *papa, Solution *maman);

/**
 * Reproduit une population
 */
vector<Solution> reproduction(vector<Solution> population);

#endif
