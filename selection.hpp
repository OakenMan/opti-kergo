#ifndef selection_hpp
#define selection_hpp

#include "Instance.hpp"
#include "Solution.hpp"
#include <stdio.h>
#include <vector>

using namespace std;

vector<Solution*> Selection(vector<Solution*> solutions);

void melange_tableau(vector<Solution*>* solutions);
void trier_tableau_par_ratio_objectif_negatif(vector<Solution*>* solutions);
int indice_ratio_obj_neg_max(vector<Solution*>* solutions, int indice_depart=0);
void trier_tableau_par_score_objectif(vector<Solution*>* solutions);
int indice_score_objectif_max(vector<Solution*>* solutions, int indice_depart=0);

/*
 * Ajoute la population 2 à la population 1
 */
vector<Solution*> fusion(vector<Solution*> pop1, vector<Solution*> pop2);

#endif
