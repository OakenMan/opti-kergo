#include "generation.hpp"
#include <iostream>
#include <vector>

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

   return sol;
}

vector<Solution*> generation(Instance *instance, unsigned int size) {

   vector<Solution*> population;

   for(unsigned int i=0; i<size; i++) {
      population.push_back(generateSolution(instance));
   }

   return population;
}

void deletePopulation(vector<Solution*> population) {
   for(unsigned int i=0; i<population.size(); i++) {
      delete population[i];
   }
}
