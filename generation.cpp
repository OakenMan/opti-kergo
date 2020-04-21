#include "generation.hpp"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>

// int main(int argv, const char * argc[]) {
//
//    srand(time(NULL));
//
//    // Lecture de l'instance
//    Instance *instance = new Instance();
//    if(!instance->chargement_Instance("Data/Inst2.txt")) {
//       cerr << "Impossible de charger l'instance" << endl;
//    }
//
//    Solution * solution;
//    for(unsigned int i=0; i<1000; i++) {
//       solution = generateFeasibleSolution(instance);
//    }
//
//    cout << "success";
//    solution->print();
// }

Solution * generateSolution(Instance *instance) {
   Solution *sol = new Solution();

   // Génération de "v_Id_Hotel_Intermedaire"
   for(unsigned int i=0; i<instance->get_Nombre_Jour()-1; i++) {
      unsigned int idHotel = rand() % instance->get_Nombre_Hotel();     // génère un id entre 0 et nbHotels-1
      sol->v_Id_Hotel_Intermedaire.push_back(idHotel);
   }

   // Génération de "v_v_Sequence_Id_Par_Jour" et "v_Date_Depart"
   for(unsigned int i=0; i<instance->get_Nombre_Jour(); i++) {
      float dateMax = 24.0;   // TODO : récupérer ce nombre depuis l'instance, puis soustraire la durée max de voyage par jour
      float dateDepart = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/dateMax));  // génère un float entre 0.0 et dateMax
      sol->v_Date_Depart.push_back(dateDepart);

      vector<unsigned int> poiList;
      unsigned int nbPOIthisDay = 5 + rand() % (instance->get_Nombre_POI() / (instance->get_Nombre_Jour() * 3));    // génère un nombre entre 0 et nbPOI/(nbJours*3)-1

      for(unsigned int j=0; j<nbPOIthisDay; j++) {
         bool success = false;
         while(!success) {
            bool found = false;
            unsigned int newPOI = rand() % instance->get_Nombre_POI();

            // Regarde si newPOI est déjà dans les jours précédents
            for(unsigned int k=0; k<sol->v_v_Sequence_Id_Par_Jour.size(); k++) {
               if(contains(sol->v_v_Sequence_Id_Par_Jour[k], newPOI)) {
                  found = true;
               }
            }
            // Et dans le jour actuel
            if(contains(poiList, newPOI)) {
               found = true;
            }
            if(!found) {
               poiList.push_back(newPOI);
               success = true;
            }
         }
      }

      sol->v_v_Sequence_Id_Par_Jour.push_back(poiList);
   }

   sol->Evaluation_Solution(instance);

   return sol;
}

Solution * generateFeasibleSolution(Instance *instance) {
   const float MARGIN = 0.1;

   Solution *sol = new Solution();

   // On instancie la liste de tous les POI disponibles (= non-visités)
   vector<unsigned int> poiAvailable;
   for(unsigned int i=0; i<instance->get_Nombre_POI(); i++) {
      poiAvailable.push_back(i);
   }
   // cout << "Génération de la liste des POI disponibles" << endl;
   // printVector(poiAvailable);


   unsigned int lastHotel = instance->get_Id_Hotel_depart();

   for(unsigned int j=0; j<instance->get_Nombre_Jour(); j++) {
      // cout << "[.] Génération du jour " << j << endl;

      unsigned int poi;
      float distanceThisDay = 0;
      float dateDepart = 0;
      vector<unsigned int> poiThisDay;

      // Génération du premier POI et de la date de départ
      do {
         poi = poiAvailable[rand() % poiAvailable.size()];                                         // On choisit un POI dans la liste des POI non-visités
         distanceThisDay = instance->get_distance_Hotel_POI(lastHotel, poi) + MARGIN;              // On récupère la distance du dernier hotel à ce POI
         dateDepart = max(float(0), instance->get_POI_Heure_ouverture(poi) - distanceThisDay);     // dateDepart = heure d'ouverture du POI - distance depuis l'hotel, ou 0 si ce nombre est < 0
      } while(dateDepart + distanceThisDay > instance->get_POI_Heure_fermeture(poi));              // On répète si on arrive après la fermeture de ce POI

      sol->v_Date_Depart.push_back(dateDepart);    // On ajoute la date de départ à la solution

      poiThisDay.push_back(poi);                                                    // On ajoute ce POI à la liste des POI visités le jours j
      poiAvailable.erase(find(poiAvailable.begin(), poiAvailable.end(), poi));      // Et on le supprime de la liste des POI disponibles

      // Génération (arbitraire, à changer par la suite ?) de l'hôtel du soir
      unsigned int nextHotel;
      if(j < instance->get_Nombre_Jour() - 1) {                // Si on est pas le dernier jour
         nextHotel = rand() % instance->get_Nombre_Hotel();    // On choisit un hotel au hasard
      }
      else {                                                   // Sinon
         nextHotel = instance->get_Id_Hotel_Arrivee();         // Le prochain hotel est l'hotel d'arrivée
      }

      int nbTries = 0;
      // float distanceToNextHotel = instance->get_distance_Hotel_POI(nextHotel, poiThisDay.back());

      // Ajout de POI ce jour (tant qu'on a pas atteind une certaine limite d'essais ratés)
      while(nbTries < 100) {  // TODO : au lieu de faire avec du random, parcourir la liste de tous les POI restants ?

         // On choisit un POI parmis ceux non-visités
         poi = poiAvailable[rand() % poiAvailable.size()];

         // On vérifie si on peut visiter ce POI :

         // SI (date de départ + distance déjà parcourue + distance du dernier POI au POI choisi) > ouverture POI et < fermeture POI
         float dateArriveePOI = dateDepart + distanceThisDay + instance->get_distance_POI_POI(poiThisDay.back(), poi) + MARGIN;
         if(dateArriveePOI >= instance->get_POI_Heure_ouverture(poi) && dateArriveePOI <= instance->get_POI_Heure_fermeture(poi)) {

            // SI (distance déjà parcourue + distance du dernier POI au POI choisi + distance du POI choisit au prochain hotel) < distance max ce jour
            float distanceToNextHotel = distanceThisDay + instance->get_distance_POI_POI(poiThisDay.back(), poi) + instance->get_distance_Hotel_POI(nextHotel, poi) + MARGIN;
            if(distanceToNextHotel < instance->get_POI_Duree_Max_Voyage(j)) {

               // ALORS on peut ajouter ce p***** de POI
               distanceThisDay += instance->get_distance_POI_POI(poiThisDay.back(), poi);    // On actualise la distance parcourue ce jour
               poiThisDay.push_back(poi);                                                    // On ajoute ce POI à la liste des POI visités le jours j
               poiAvailable.erase(find(poiAvailable.begin(), poiAvailable.end(), poi));      // Et on le supprime de la liste des POI disponibles
               // distanceToNextHotel = instance->get_distance_Hotel_POI(nextHotel, poiThisDay.back());  // On actualise la distance au prochain hotel
               nbTries = 0;                                                                  // On reset nbTries

            }
            else {
               nbTries++;
            }
         }
         else {
            nbTries++;
         }
      }

      // On arrive plus à ajouter de POI, donc on finit le jour et on passe au suivant
      if(j < instance->get_Nombre_Jour() - 1) {
         sol->v_Id_Hotel_Intermedaire.push_back(nextHotel);
      }
      sol->v_v_Sequence_Id_Par_Jour.push_back(poiThisDay);

      lastHotel = nextHotel;

   }

   sol->Evaluation_Solution(instance);

   return sol;
}

vector<Solution*> generation(Instance *instance, unsigned int size) {

   vector<Solution*> population;

   // Génération de solutions au hasard (souvent non-réalisables)
   for(unsigned int i=0; i<RATIO_POP*size; i++) {
      population.push_back(generateSolution(instance));
   }

   // Génération de solutions propres (souvent réalisables)
   for(unsigned int i=RATIO_POP*size; i<size; i++) {
      population.push_back(generateFeasibleSolution(instance));
   }

   return population;
}

void deletePopulation(vector<Solution*> population) {
   for(unsigned int i=0; i<population.size(); i++) {
      delete population[i];
   }
}
