#include "generation.hpp"

#include <iostream>
#include <stdio.h>
#include <algorithm>

/*
 * Génère une solution (aléatoirement mais en restant "cohérent") en se basant sur une instance
 * Les solution générées par cette fonction sont presque toutes non-réalisables mais ont souvent une bonne fonction objectif
 */
Solution * generateSolution(Instance *instance) {
   Solution *sol = new Solution();

   // Génération de "v_Id_Hotel_Intermedaire"
   for(unsigned int i=0; i<instance->get_Nombre_Jour()-1; i++) {
      unsigned int idHotel = rand() % instance->get_Nombre_Hotel();     // Génère un hôtel au hasard
      sol->v_Id_Hotel_Intermedaire.push_back(idHotel);                  // Et le rajoute à la liste
   }

   // Génération de "v_v_Sequence_Id_Par_Jour" et "v_Date_Depart"
   for(unsigned int i=0; i<instance->get_Nombre_Jour(); i++) {
      float dateDepart = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/instance->get_Duree_Max_Jour()));  // Génère un float entre 0.0 et dateMax
      sol->v_Date_Depart.push_back(dateDepart);

      vector<unsigned int> poiList;
      unsigned int nbPOIthisDay = 5 + rand() % (instance->get_Nombre_POI() / (instance->get_Nombre_Jour() * 3));    // Génère un nombre entre 0 et nbPOI/(nbJours*3)-1

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

   // Enfin, on évalue la solution pour déterminer sa fonction objectif et son score négatif
   sol->Evaluation_Solution(instance);

   return sol;
}

/*
 * Génère une solution "la plus faisable" possible en se basant sur une instance
 * Les solutions générées par cette fonction sont presque toutes réalisables mais ont souvent une mauvaise fonction objectif
 */
Solution * generateFeasibleSolution(Instance *instance) {
   const float MARGIN = 0.1; // Constance utilisée pour éviter les erreurs d'approximation sur les floats

   Solution *sol = new Solution();

   // On instancie la liste de tous les POI disponibles (= non-visités)
   vector<unsigned int> poiAvailable;
   for(unsigned int i=0; i<instance->get_Nombre_POI(); i++) {
      poiAvailable.push_back(i);
   }

   unsigned int lastHotel = instance->get_Id_Hotel_depart();      // Dernier hôtel visité

   // Pour chaque jour...
   for(unsigned int j=0; j<instance->get_Nombre_Jour(); j++) {

      unsigned int poi;
      float distanceThisDay = 0;          // Distance parcourue ce jour
      float dateDepart = 0;               // Date de départ de ce jour
      vector<unsigned int> poiThisDay;    // Séquence de POI visités ce jour

      // Génération du premier POI et de la date de départ
      do {
         poi = poiAvailable[rand() % poiAvailable.size()];                                         // On choisit un POI dans la liste des POI non-visités
         distanceThisDay = instance->get_distance_Hotel_POI(lastHotel, poi) + MARGIN;              // On récupère la distance du dernier hotel à ce POI
         dateDepart = max(float(0), instance->get_POI_Heure_ouverture(poi) - distanceThisDay);     // dateDepart = min(heure d'ouverture du POI - distance depuis l'hotel, 0)
      } while(dateDepart + distanceThisDay > instance->get_POI_Heure_fermeture(poi));              // On répète si on arrive après la fermeture de ce POI

      // On ajoute la date de départ à la solution
      sol->v_Date_Depart.push_back(dateDepart);

      poiThisDay.push_back(poi);                                                    // On ajoute ce POI à la liste des POI visités le jours j
      poiAvailable.erase(find(poiAvailable.begin(), poiAvailable.end(), poi));      // Et on le supprime de la liste des POI disponibles

      // Génération arbitraire de l'hôtel du soir
      unsigned int nextHotel;
      if(j < instance->get_Nombre_Jour() - 1) {                // Si on est pas le dernier jour
         nextHotel = rand() % instance->get_Nombre_Hotel();    // On choisit un hotel au hasard
      }
      else {                                                   // Sinon
         nextHotel = instance->get_Id_Hotel_Arrivee();         // Le prochain hotel est l'hotel d'arrivée
      }

      int nbTries = 0;     // Nombre d'essais de rajout de POI

      // Ajout de POI ce jour (tant qu'on a pas atteind une certaine limite d'essais ratés)
      while(nbTries < 100) {

         // On choisit un POI parmis ceux non-visités
         poi = poiAvailable[rand() % poiAvailable.size()];

         // On vérifie si on peut visiter ce POI :

         // SI (date de départ + distance déjà parcourue + distance du dernier POI au POI choisi) > ouverture POI et < fermeture POI
         float dateArriveePOI = dateDepart + distanceThisDay + instance->get_distance_POI_POI(poiThisDay.back(), poi) + MARGIN;
         if(dateArriveePOI >= instance->get_POI_Heure_ouverture(poi) && dateArriveePOI <= instance->get_POI_Heure_fermeture(poi)) {

            // SI (distance déjà parcourue + distance du dernier POI au POI choisi + distance du POI choisit au prochain hotel) < distance max ce jour
            float distanceToNextHotel = distanceThisDay + instance->get_distance_POI_POI(poiThisDay.back(), poi) + instance->get_distance_Hotel_POI(nextHotel, poi) + MARGIN;
            if(distanceToNextHotel < instance->get_POI_Duree_Max_Voyage(j)) {

               // ALORS on peut enfin ajouter ce POI
               distanceThisDay += instance->get_distance_POI_POI(poiThisDay.back(), poi);    // On actualise la distance parcourue ce jour
               poiThisDay.push_back(poi);                                                    // On ajoute ce POI à la liste des POI visités ce jour
               poiAvailable.erase(find(poiAvailable.begin(), poiAvailable.end(), poi));      // Et on le supprime de la liste des POI disponibles
               nbTries = 0;                                                                  // On reset nbTries

            }
            // Si on ne peut pas ajouter le POI, on incrémente nbTries
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

   // Enfin, on évalue la solution pour déterminer sa fonction objectif et son score négatif
   sol->Evaluation_Solution(instance);

   return sol;
}

/*
 * Génère une population de taille "size"
 */
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

/*
 * Supprime une population
 */
void deletePopulation(vector<Solution*> population) {
   for(unsigned int i=0; i<population.size(); i++) {
      delete population[i];
   }
}
