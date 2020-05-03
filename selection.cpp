#include "selection.hpp"
#include <cstdlib>
#include <cmath>
#include <iostream>

vector<Solution*> Selection(vector<Solution*> solutions)
{
    vector<Solution*> solutions_realisables;
    vector<Solution*> solutions_irrealisables;
    vector<Solution*> nouvelle_generation;
    unsigned int taille_pop = solutions.size();
    unsigned int i;

    //On sépare l'ensemble de solutions en solutions réalisables et irréalisables
    for (i = 0; i < taille_pop; i++)
    {
        if (solutions[i]->i_valeur_score_negatif > 0)
        {
            solutions_irrealisables.push_back(solutions[i]);
        }
        else
        {
            solutions_realisables.push_back(solutions[i]);
        }
    }

    trier_tableau_par_score_objectif(&solutions_realisables);
    trier_tableau_par_ratio_objectif_negatif(&solutions_irrealisables);

    /*
    On remplit le tableau de la nouvelle génération de 25% des meilleurs solution réalisables et irréalisables si possible.
    Sinon, on comble avec l'un ou l'autre des deux domaines.
    */
    if (solutions_realisables.size() >= taille_pop/4 && solutions_irrealisables.size() >= taille_pop/4)
    {
        for (i = 0; i < taille_pop/4; i++)
        {
            nouvelle_generation.push_back(solutions_realisables[i]);
        }

        for (i = 0; i < taille_pop/4; i++)
        {
            nouvelle_generation.push_back(solutions_irrealisables[i]);
        }
    }
    else if (solutions_realisables.size() >= taille_pop/4 && solutions_irrealisables.size() < taille_pop/4)
    {
        for (i = 0; i < solutions_irrealisables.size(); i++)
        {
            nouvelle_generation.push_back(solutions_irrealisables[i]);
        }

        for (i = 0; i < taille_pop/2 - solutions_irrealisables.size(); i++)
        {
            nouvelle_generation.push_back(solutions_realisables[i]);
        }
    }
    else if (solutions_realisables.size() < taille_pop/4 && solutions_irrealisables.size() >= taille_pop/4)
    {
        for (i = 0; i < solutions_realisables.size(); i++)
        {
            nouvelle_generation.push_back(solutions_realisables[i]);
        }
        for (i = 0; i < taille_pop/2 - solutions_realisables.size(); i++)
        {
            nouvelle_generation.push_back(solutions_irrealisables[i]);
        }
    }
    else
    {
        cout << "ATTENTION ERREUR SUR LA SELECTION" << endl;
    }

    //On mélange le tableau des survivants pour faciliter le travail pour la suite
    melange_tableau(&nouvelle_generation);

    return nouvelle_generation;
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

/*
 * Ajoute la population 2 à la population 1
 */
vector<Solution*> fusion(vector<Solution*> pop1, vector<Solution*> pop2) {

   vector<Solution*> newPop;

   // On ajoute la population 2 à la population 1
   for(unsigned int i=0; i<pop1.size(); i++) {
      newPop.push_back(pop1[i]);
   }

   // On ajoute la population 2 à la population 1
   for(unsigned int i=0; i<pop2.size(); i++) {
      newPop.push_back(pop2[i]);
   }

   return newPop;
}
