#include "stats.hpp"

// Renvoie le meilleur score d'une population, en prenant uniquement en compte les solutions réalisables si onlyFeasible = true
unsigned int getBestScore(vector<Solution*> population, bool onlyFeasible) {
   unsigned int bestSolution = 0;
   unsigned int index = 0;

   for(unsigned int i=0; i<population.size(); i++) {
      if(onlyFeasible) {
         if(population[i]->i_valeur_fonction_objectif > bestSolution && population[i]->i_valeur_score_negatif == 0) {
            bestSolution = population[i]->i_valeur_fonction_objectif;
            index = i;
         }
      }
      else {
         if(population[i]->i_valeur_fonction_objectif > bestSolution) {
            bestSolution = population[i]->i_valeur_fonction_objectif;
            index = i;
         }
      }
   }

   if(DEBUG) {
      population[index]->print();
   }

   return bestSolution;
}

// Renvoie la meilleure solution réalisable d'une population
Solution * getBestSolution(vector<Solution*> population) {
   Solution * bestSolution = new Solution();
   bestSolution->i_valeur_fonction_objectif = 0;

   for(unsigned int i=0; i<population.size(); i++) {
      if(population[i]->i_valeur_fonction_objectif > bestSolution->i_valeur_fonction_objectif && population[i]->i_valeur_score_negatif == 0) {
         bestSolution = population[i];
      }
   }

   return bestSolution;
}

// Renvoie le meilleur ratio (fonction objectif/score négatif) d'une population
float bestRatio(vector<Solution*> population) {
   float bestRatio = 0;
   unsigned int index = 0;

   for(unsigned int i=0; i<population.size(); i++) {
      float ratio = (float)(population[i]->i_valeur_fonction_objectif/(population[i]->i_valeur_score_negatif+1));
      if(ratio > bestRatio) {
         bestRatio = ratio;
         index = i;
      }
   }

   if(DEBUG) {
      population[index]->print();
   }

   return bestRatio;
}

// Renvoie le score moyen d'une population
float averageScore(vector<Solution*> population, bool onlyFeasible) {
   unsigned int sum = 0;
   int nbr = 1;

   for(unsigned int i=0; i<population.size(); i++) {
      if(onlyFeasible) {
         if(population[i]->i_valeur_score_negatif == 0) {
            sum += population[i]->i_valeur_fonction_objectif;
            nbr++;
         }
      }
      else {
         sum += population[i]->i_valeur_fonction_objectif;
         nbr++;
      }
   }

   return (float)(sum / nbr);
}

// Renvoie le ratio moyen d'une population
float averageRatio(vector<Solution*> population) {
   float sum = 0;
   for(unsigned int i=0; i<population.size(); i++) {
      sum += (population[i]->i_valeur_fonction_objectif) / (population[i]->i_valeur_score_negatif+1);
   }

   return sum / population.size();
}

// Renvoie la "diversité" (solutions non-réalisables | solutions réalisables) d'une population
vector<unsigned int> diversity(vector<Solution*> population) {
   vector<unsigned int> diversity;
   diversity.push_back(0);
   diversity.push_back(0);

   for(unsigned int i=0; i<population.size(); i++) {
      if(population[i]->i_valeur_score_negatif == 0) {
         diversity[1] += 1;
      }
      else {
         diversity[0] += 1;
      }
   }

   return diversity;
}

// Affiche un récapitulatif d'une population
void analyse(vector<Solution*> population) {
   cout << "Taille de la population : " << population.size() << endl;
   cout << "Meilleurs solution / Moyennes " << endl;
   cout << "   Toutes      : " << getBestScore(population, false) << "\t| " << averageScore(population, false) << endl;
   cout << "   Réalisables : " << getBestScore(population, true) << "\t| " << averageScore(population, true) << endl;
   cout << "Meilleur ratio : " << bestRatio(population) << endl;
   cout << "Ratio moyen    : " << averageRatio(population) << endl;
   cout << "Diversité (non-réalisables/réalisables) : ";
   vector<unsigned int> div = diversity(population);
   printVector(div);
}

// Réacapitulatif en une seule ligne
void analyseOneLine(vector<Solution*> population) {
   cout << bestRatio(population) << "\t| " << averageRatio(population) << "\t| ";
   vector<unsigned int> div = diversity(population);
   printVector(div);
}
