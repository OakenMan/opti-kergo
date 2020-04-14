#include "vector_methods.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

/*
 * Affiche un vecteur sous cette forme : "[ x y z ] (n=taille) \n"
 */
void print(vector<unsigned int> &v) {
   cout << "[ ";
   for(unsigned int i=0; i<v.size(); i++) {
      cout << v[i] << " ";
   }
   cout << "] (n=" << v.size() << ")";
   cout << endl;
}

/*
 * Retourne vrai si v contient value, faux sinon
 */
bool contains(vector<unsigned int> v, unsigned int value) {
   return find(v.begin(), v.end(), value) != v.end();
}

/*
 * Retourne l'index de value dans v, ou v.end()-1 si value n'est pas dans v
 */
unsigned int indexOf(vector<unsigned int> v, unsigned int value) {
   for(unsigned int i=0; i<v.size(); i++) {
      if(v[i] == value) {
         return i;
      }
   }
   return v.size()-1;
}

/*
 * Génère un vecteur aléatoirement, de taille compris entre minSize et maxSize, et de valeurs comprises entre 0 et maxValue
 */
vector<unsigned int> randomVector(unsigned int minSize, unsigned int maxSize, unsigned int maxValue) {
   vector<unsigned int> v;

   unsigned int size = minSize + rand() % (maxSize - minSize + 1);

   for(unsigned int i=0; i<size; i++) {
      unsigned int r = rand() % (maxValue + 1);
      if(contains(v, r)) {
         i--;
      }
      else {
         v.push_back(r);
      }
   }

   return v;
}

/*
 * Fusionne tous les vecteurs d'un vecteur de vecteur, pour ne former qu'un seul vecteur ._.
 */
vector<unsigned int> linkVectors(vector<vector<unsigned int>> v) {

   vector<unsigned int> linked;
   for(unsigned int i=0; i<v.size(); i++) {
      for(unsigned int j=0; j<v[i].size(); j++) {
         linked.push_back(v[i][j]);
      }
   }

   return linked;

}

void melange_tableau(vector<Solution*>* solutions)
{
    unsigned int i;
    unsigned int taille_pop = solutions->size();
    unsigned int indice_aleatoire;
    Solution* solution_tmp;

    for (i = 0; i < taille_pop; i++)
    {
        indice_aleatoire = rand() % taille_pop;
        solution_tmp = solutions->at(i);
        solutions->at(i) = solutions->at(indice_aleatoire);
        solutions->at(indice_aleatoire) = solution_tmp;
    }
}

/*
Trie un tableau de solutions irréalisables selon un ordre croissant de leur ratio "score objectif / score négatif"
*/
//TODO : Implémenter un algorithme plus efficace
void trier_tableau_par_ratio_objectif_negatif(vector<Solution*>* solutions)
{
    unsigned int i;
    unsigned int indice_max;
    Solution* solution_tmp;

    for (i = 0; i < solutions->size(); i++)
    {
        indice_max = indice_ratio_obj_neg_max(solutions, i);
        if (i != indice_max)
        {
            solution_tmp = solutions->at(i);
            solutions->at(i) = solutions->at(indice_max);
            solutions->at(indice_max) = solution_tmp;
        }
    }
}

//Renvoie l'indice de la solution ayant le meilleur ratio "score obj. / score nég." à partir de l'indice "indice_depart"
int indice_ratio_obj_neg_max(vector<Solution*>* solutions, int indice_depart)
{
    unsigned int i;
    float ratio_tmp;
    unsigned int indice_tmp;

    if (solutions->size() == 0)
    {
        cout << "ERREUR FONCTION MIN, solutions.size() == 0" << endl;
        return 0;
    }
    else
    {
        ratio_tmp = (float)solutions->at(indice_depart)->i_valeur_fonction_objectif / (float)solutions->at(indice_depart)->i_valeur_score_negatif;   
        indice_tmp = indice_depart;
    }

    for (i = indice_depart; i < solutions->size(); ++i)
    {
        if (ratio_tmp < (float)solutions->at(i)->i_valeur_fonction_objectif / (float)solutions->at(i)->i_valeur_score_negatif)
        {
            ratio_tmp = solutions->at(i)->i_valeur_fonction_objectif / (float)solutions->at(i)->i_valeur_score_negatif;
            indice_tmp = i;
        }
    }

    return indice_tmp;
}

/*
Trie un tableau de solutions réalisables selon un ordre croissant de leur score objectif
*/
//TODO : Implémenter un algorithme plus efficace
void trier_tableau_par_score_objectif(vector<Solution*> * solutions)
{
    unsigned int i;
    unsigned int indice_min;
    Solution* solution_tmp;

    for (i = 0; i < solutions->size(); i++)
    {
        indice_min = indice_score_objectif_max(solutions, i);
        if (i != indice_min)
        {
            solution_tmp = solutions->at(i);
            solutions->at(i) = solutions->at(indice_min);
            solutions->at(indice_min) = solution_tmp;
        }
    }
}

//Renvoie l'indice de la solution ayant le meilleur score objectif à partir de l'indice "indice_depart"
int indice_score_objectif_max(vector<Solution*>* solutions, int indice_depart)
{
    unsigned int i;
    unsigned int valeur_tmp;
    unsigned int indice_tmp;

    if (solutions->size() == 0)
    {
        cout << "ERREUR FONCTION MIN, solutions.size() == 0" << endl;
        return 0;
    }
    else
    {
        valeur_tmp = solutions->at(indice_depart)->i_valeur_fonction_objectif;    
        indice_tmp = indice_depart;
    }

    for (i = indice_depart; i < solutions->size(); ++i)
    {
        if (valeur_tmp < solutions->at(i)->i_valeur_fonction_objectif)
        {
            valeur_tmp = solutions->at(i)->i_valeur_fonction_objectif;
            indice_tmp = i;
        }
    }

    return indice_tmp;
}
