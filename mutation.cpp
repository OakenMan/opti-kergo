#include "mutation.hpp"

#include <iostream>
#include <algorithm>
#include <chrono>
#include <limits.h>

/*
 * Fait muter la liste des hôtels intermédiaires d'une solution
 * (choisit un jour au hasard, et change l'hôtel par un autre)
 */
void muter_Hotels_Intermediares(Solution *solution, unsigned int nbHotels) {

        // On choisit un jour à muter
        unsigned int day = rand() % solution->v_Id_Hotel_Intermedaire.size();

        // On génère un hôtel
        unsigned int newHotel = rand() % nbHotels;

        // On le remplace dans la liste des hôtels intermédiaires
        solution->v_Id_Hotel_Intermedaire[day] = newHotel;
}

/*
 * Fait muter les séquences de POI d'une solution
 * (choisit un jour au hasard, et y supprime ou ajoute un POI)
 */
void muter_Sequence_POI(Solution *solution, unsigned int nbPOI) {

        // On choisit un jour à muter
        unsigned int day = rand() % solution->v_v_Sequence_Id_Par_Jour.size();

        int random = rand() % 2;    // Génère un nombre au hasard (0 ou 1)

        // Si y'a plus que un seul POI dans un jour, on force le rajout
        if(solution->v_v_Sequence_Id_Par_Jour[day].size() <= 1) {
           random = 1;
        }

        // random == 1 => on ajoute un POI
        if(random) {
                bool success = false;
                while(!success) {
                        // On génère un POI à insérer
                        unsigned int newPOI = rand() % nbPOI;
                        // Si il n'est pas déjà dans la séquence de POI
                        if(!contains(linkVectors(solution->v_v_Sequence_Id_Par_Jour), newPOI)) {
                                // On génère la position d'insertion
                                unsigned int index = rand() % solution->v_v_Sequence_Id_Par_Jour[day].size();
                                vector<unsigned int>::iterator it = solution->v_v_Sequence_Id_Par_Jour[day].begin();
                                // Et on y insère newPOI
                                solution->v_v_Sequence_Id_Par_Jour[day].insert(it+index, newPOI);
                                success = true;
                        }
                }
        }
        // random == 0 => on supprime un POI
        else {
                // On génère la position de suppression
                unsigned int index = rand() % solution->v_v_Sequence_Id_Par_Jour[day].size();
                vector<unsigned int>::iterator it = solution->v_v_Sequence_Id_Par_Jour[day].begin();
                // Et on supprime la valeur à cette position
                solution->v_v_Sequence_Id_Par_Jour[day].erase(it+index);
        }
}

/*
 * Fait muter le vecteur des dates de départ d'une solutions
 * (augmente ou diminue aléatoirement la date de départ)
 */
void muter_Date_Depart(Solution *solution, float dateMax, Settings *settings) {

        // On choisit un jour à muter
        unsigned int day = rand() % solution->v_Date_Depart.size();

        float minChange = min(solution->v_Date_Depart[day], float(settings->MAX_CHANGE_ON_DATE));
        float maxChange = min(float(0.01) + dateMax - solution->v_Date_Depart[day], float(settings->MAX_CHANGE_ON_DATE));

        // On génère un changement d'heure compris entre minChange et maxChange (qui sont initialisés de telle façon à ce qu'il
        // soit impossible d'obtenir une date de départ négative ou superieur à la durée d'une journée)
        float change = -minChange + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/maxChange));

        // On applique ce changement à la date de départ
        solution->v_Date_Depart[day] += change;
}

/*
 * Fait muter une solution
 */
void mutate(Solution *solution, Instance *instance, Settings *settings) {

        // Trois fois de suite, on génère un nombre entre 0 et 100 et on regarde si il est inférieur à la probabilité
        // de mutation de ce caractère. Si oui, on fait muter ce caractère, puis on ré-évalue la solution.

        // Mutation des hôtels intermédiaires
        if(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100)) < settings->PROBA_MUT_HOTEL) {
                muter_Hotels_Intermediares(solution, instance->get_Nombre_Hotel());
                solution->Evaluation_Solution(instance);
        }

        // Mutation des séquences de POI
        if(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100)) < settings->PROBA_MUT_POI) {
                muter_Sequence_POI(solution, instance->get_Nombre_POI());
                solution->Evaluation_Solution(instance);
        }

        // Mutation des dates de départ
        if(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100)) < settings->PROBA_MUT_DATE) {
                muter_Date_Depart(solution, instance->get_Duree_Max_Jour(), settings);
                solution->Evaluation_Solution(instance);
        }
}

/*
 * Effectue des mutations sur une population
 */
void mutation(vector<Solution*> population, Instance *instance, Settings *settings) {
        for(unsigned int i=0; i<population.size(); i++) {
                mutate(population[i], instance, settings);
        }
}
