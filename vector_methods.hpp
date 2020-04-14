#ifndef vector_methods_hpp
#define vector_methods_hpp

#include <stdio.h>
#include <vector>
#include "Solution.hpp"

using namespace std;

/*
 * Affiche un vecteur sous cette forme : "[ x y z ] (n=taille) \n"
 */
void print(vector<unsigned int> &v);

/*
 * Retourne vrai si v contient value, faux sinon
 */
bool contains(vector<unsigned int> v, unsigned int value);

/*
 * Retourne l'index de value dans v, ou v.end()-1 si value n'est pas dans v
 */
unsigned indexOf(vector<unsigned int> v, unsigned int value);

/*
 * Génère un vecteur aléatoirement, de taille compris entre minSize et maxSize, et de valeurs comprises entre 0 et maxValue
 */
vector<unsigned int> randomVector(unsigned int minSize, unsigned int maxSize, unsigned int maxValue);

/*
 * Fusionne tous les vecteurs d'un vecteur de vecteur, pour ne former qu'un seul vecteur ._.
 */
vector<unsigned int> linkVectors(vector<vector<unsigned int>> v);

void melange_tableau(vector<Solution*>* solutions);
void trier_tableau_par_ratio_objectif_negatif(vector<Solution*>* solutions);
int indice_ratio_obj_neg_max(vector<Solution*>* solutions, int indice_depart=0);
void trier_tableau_par_score_objectif(vector<Solution*>* solutions);
int indice_score_objectif_max(vector<Solution*>* solutions, int indice_depart=0);

#endif
