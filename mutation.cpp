#include "mutation.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <limits.h>

int main(int argc, const char * argv[]){

   srand(time(NULL));

   chrono::time_point<chrono::system_clock> chrono_start, chrono_end;
   chrono::duration<double> elapsed;

   // Lecture de l'instance
   Instance *instance = new Instance();
   if(!instance->chargement_Instance("Data/Inst8.txt")) {
      cerr << "Impossible de charger l'instance" << endl;
   }

   // Génération de la population de base
   vector<Solution*> population = generation(instance, 1000);

   chrono_start = chrono::system_clock::now();

   // Mutation de la population
   mutation(population, instance);

   chrono_end = chrono::system_clock::now();

   // On supprime la population
   deletePopulation(population);

   elapsed=chrono_end-chrono_start;

   cout << "time = " << elapsed.count() << endl;

   return 0;
}

void muter_Hotels_Intermediares(Solution *solution, unsigned int nbHotels) {

   // On choisit un jour à muter
   unsigned int day = rand() % solution->v_Id_Hotel_Intermedaire.size();

   // On génère un hôtel
   unsigned int newHotel = rand() % nbHotels;

   // On le remplace dans la liste des hôtels intermédiaires
   solution->v_Id_Hotel_Intermedaire[day] = newHotel;

   // cout << "HOTELS : remplacement de l'hôtel du jour " << day << " par " << newHotel << endl;

}

void muter_Sequence_POI(Solution *solution, unsigned int nbPOI) {

   // On choisit un jour à muter
   unsigned int day = rand() % solution->v_v_Sequence_Id_Par_Jour.size();

   // rand()%2 = 1 => on ajoute un POI
   if(rand()%2) {
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

            // cout << "POI : ajout de " << newPOI << " à la position [" << day << "][" << index << "]" << endl;
         }
      }
   }
   // rand()%2 = 0 => on supprime un POI
   else {
      // On génère la position de suppression
      unsigned int index = rand() % solution->v_v_Sequence_Id_Par_Jour[day].size();
      vector<unsigned int>::iterator it = solution->v_v_Sequence_Id_Par_Jour[day].begin();
      // Et on supprime la valeur à cette position
      solution->v_v_Sequence_Id_Par_Jour[day].erase(it+index);

      // cout << "POI : suppression du POI à la position [" << day << "][" << index << "]" << endl;
   }
}

void muter_Date_Depart(Solution *solution, float dateMax) {

   // On choisit un jour à muter
   unsigned int day = rand() % solution->v_Date_Depart.size();

   float minChange = min(solution->v_Date_Depart[day], float(MAX_CHANGE_ON_DATE));
   float maxChange = min(dateMax - solution->v_Date_Depart[day], float(MAX_CHANGE_ON_DATE));
   float change = -minChange + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/maxChange));

   solution->v_Date_Depart[day] += change;

   // cout << "DATE : changement de la date de départ du jour " << day << " de " << change << endl;
}

/*
 * Fait muter une solution
 */
void mutate(Solution *solution, Instance *instance) {

   // génère un float entre 0 et 100
   if(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100)) < PROBA_MUT_HOTEL) {
      muter_Hotels_Intermediares(solution, instance->get_Nombre_Hotel());
      // cout << "Mutation sur les hôtels !" << endl;
   }

   if(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100)) < PROBA_MUT_POI) {
      muter_Sequence_POI(solution, instance->get_Nombre_POI());
      // cout << "Mutation sur les POI !" << endl;
   }

   if(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100)) < PROBA_MUT_DATE) {
      muter_Date_Depart(solution, 75.0); // <---- récupérer la date max depuis l'instance
      // cout << "Mutation sur les dates !" << endl;
   }

}

/*
 * Effectue des mutations sur une population
 */
void mutation(vector<Solution*> population, Instance *instance) {

   for(unsigned int i=0; i<population.size(); i++) {
      mutate(population[i], instance);
   }

}
