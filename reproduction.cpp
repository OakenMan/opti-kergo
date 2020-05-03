#include "reproduction.hpp"

#include <iostream>
#include <algorithm>
#include <chrono>
#include <limits.h>

/*
 * Crossover PMX (légèrement modifié)
 * [!] Inutilisé
 */
/*
vector<unsigned int> pmx(vector<unsigned int> p1, vector<unsigned int> p2) {

   vector<unsigned int> child;

   unsigned int n1 = p1.size();
   unsigned int n2 = p2.size();

   unsigned int smallestSize = min(n1, n2);

   // On modifie les parents en rajoutant des UINT_MAX pour qu'ils soient de même taille

   // Si p1 plus grand que p2
   if(n2 < n1) {
      // On rallonge p2
      for(unsigned int i=0; i<n1-n2; i++) {
         p2.push_back(UINT_MAX);
      }
   }
   // Si p2 plus grand que p1
   else if(n1 < n2) {
      // On rallonge p1
      for(unsigned int i=0; i<n2-n1; i++) {
         p1.push_back(UINT_MAX);
      }
   }

   unsigned int n = p1.size();

   // Initialisation des enfants
   for(unsigned int i=0; i<n; i++) {
      child.push_back(UINT_MAX);
   }

   // Indices choisis pour la "coupe"
   // cutLength = rand(2, smallestSize-2)
   // cutStart = rand(0, n-cutLength)
   // coupe = [cutStart, cutEnd]
   unsigned int cutLength  = MIN_CUT_SIZE + rand() % (smallestSize - MAX_CUT_SIZE - MIN_CUT_SIZE + 1);
   unsigned int cutStart   = rand() % (smallestSize - cutLength + 1);
   unsigned int cutEnd     = cutStart + cutLength - 1;

   // cout << "\tmaxSize=" << n << ", minSize=" << smallestSize << ", length=" << cutLength << ", coupe=[" << cutStart << ", " << cutEnd << "]" << endl;

   // Copie de la coupe de p1 dans child
   for(unsigned int i=cutStart; i<=cutEnd; i++) {
      child[i] = p1[i];
   }

   // Pour chaque valeur dans cette coupe dans p2
   for(unsigned int i=cutStart; i<=cutEnd; i++) {
      // Si cette valeur n'a pas été copiée dans child
      if(!contains(child, p2[i])) {
         bool next = false;
         unsigned int index = i;
         do {
            // On récupère la valeur au même index dans p1
            unsigned int valueInP1 = p1[index];
            // On récupère l'index de cette valeur dans p2
            unsigned int indexInP2 = indexOf(p2, valueInP1);
            // Si cet index est dans la coupe, alors on recommence
            // avec cet index
            if(indexInP2 >= cutStart && indexInP2 <= cutEnd) {
               index = indexInP2;
            }
            // Sinon, on copie la valeur de départ à cette position dans child
            else {
               child[indexInP2] = p2[i];
               next = true;
            }
         } while(!next);
      }
   }

   // Enfin, on copie les valeurs restantes de p2 dans child
   for(unsigned int i=0; i<n; i++) {
      if(!contains(child, p2[i])) {
         child[i] = p2[i];
      }
   }

   // Et on supprime les 0 en trop dans child
   vector<unsigned int>::iterator it;
   do {
      it = find(child.begin(), child.end(), UINT_MAX);
      if(it != child.end()) {
         if(*it == UINT_MAX) {
            child.erase(it);
         }
      }
   } while(it != child.end());

   return child;
}
*/

/*
 * Crossover OX1
 * (légèrement modifié pour qu'il puisse fonctionner sur des vecteurs de tailles différentes et qu'il donne un résultat sans doublons)
 * Complexité : O(n)
 */
vector<unsigned int> ox1(vector<unsigned int> p1, vector<unsigned int> p2) {

   vector<unsigned int> child;

   unsigned int n1 = p1.size();  // Taille de p1
   unsigned int n2 = p2.size();  // Taille de p2

   unsigned int smallestSize = min(n1, n2);

   // On modifie les parents en rajoutant des UINT_MAX pour qu'ils soient de même taille
   // On utilise la constante UINT_MAX car c'est peu probable qu'on ai 4 milliards de POI...
   // Si p1 plus grand que p2 :
   if(n2 < n1) {
      // On rallonge p2
      for(unsigned int i=0; i<n1-n2; i++) {
         p2.push_back(UINT_MAX);
      }
   }
   // Si p2 plus grand que p1 :
   else if(n1 < n2) {
      // On rallonge p1
      for(unsigned int i=0; i<n2-n1; i++) {
         p1.push_back(UINT_MAX);
      }
   }

   unsigned int n = p1.size();   // Taille des deux vecteurs après modification

   child.reserve(n+1);           // On alloue de la place pour l'enfant (plus de la sureté qu'autre chose)

   // Initialisation de l'enfant
   for(unsigned int i=0; i<n; i++) {
      child.push_back(UINT_MAX);
   }

   // Indices choisis pour la "coupe"
   // cutLength = rand(2, smallestSize-2)
   // cutStart = rand(0, n-cutLength)
   // coupe = [cutStart, cutEnd]
   unsigned int cutLength  = MIN_CUT_SIZE + rand() % (smallestSize - MIN_CUT_SIZE);
   unsigned int cutStart   = rand() % (smallestSize - cutLength + 1);
   unsigned int cutEnd     = cutStart + cutLength - 1;

   // Copie de la coupe de p1 dans child
   for(unsigned int i=cutStart; i<=cutEnd; i++) {
      child[i] = p1[i];
   }

   unsigned int index=0;

   for(unsigned int i=0; i<n && index < n; i++) {
      // On saute la coupe, qui est déjà initialisée chez l'enfant
      if(index == cutStart) {
         index += cutLength;
      }
      // Si p2[i] n'as pas été copiée dans l'enfant, on le rajoute à la première place disponible
      if(!contains(child, p2[i]) || p2[i] == UINT_MAX) {             // voir 'vector_methods.hpp'
         child[index] = p2[i];
         index++;
      }
   }

   // Et on supprime les UINT_MAX en trop dans child
   vector<unsigned int>::iterator it;
   do {
      it = find(child.begin(), child.end(), UINT_MAX);
      if(it != child.end()) {
         if(*it == UINT_MAX) {
            child.erase(it);
         }
      }
   } while(it != child.end());

   // On désalloue la place en trop utilisée par l'enfant
   child.shrink_to_fit();

   return child;
}

/*
 * Applique un algo. de crossover (actuellement OX1) entre p1 et p2 (tableaux des POI visités chaque jour)
 */
vector<vector<unsigned int>> crossover(vector<vector<unsigned int>> p1, vector<vector<unsigned int>> p2) {

   // On fusionne tous les vecteurs (=séquences de POI) en un seul vector (voir 'vector_methods.hpp')
   vector<unsigned int> p1Linked = linkVectors(p1);
   vector<unsigned int> p2Linked = linkVectors(p2);

   // On applique OX1 dessus
   vector<unsigned int> childLinked = ox1(p1Linked, p2Linked);

   vector<vector<unsigned int>> child;

   // On re-sépare le vecteur enfant en suivant le modèle de p2
   unsigned int index = 0;
   unsigned int day = 0;
   while(index < childLinked.size() && day < p2.size()) {
      vector<unsigned int> oneDay;
      for(unsigned int j=0; j<p2[day].size() && index < childLinked.size(); j++) {
         oneDay.push_back(childLinked[index]);
         index++;
      }
      child.push_back(oneDay);
      day++;
   }

   return child;
}

/*
 * Mélange 2 vecteurs en fonction d'un pattern généré aléatoirement
 */
vector<unsigned int> shuffle_int(vector<unsigned int> *p1, vector<unsigned int> *p2) {

   vector<unsigned int> pattern;
   vector<unsigned int> child;

   unsigned int n = p1->size(); // Ici, p1 et p2 font forcément la même taille

   // Génère un pattern composé de 0 et de 1 (ex : 01001011)
   for(unsigned int i=0; i<n; i++) {
      pattern.push_back(rand() % 2);
   }

   // Pour un index i, si pattern[i] = 1, on garde la valeur de p1, sinon on garde celle de p2
   for(unsigned int i=0; i<n; i++) {
      if(pattern[i])    child.push_back(p1->at(i));
      else              child.push_back(p2->at(i));
   }

   return child;
}

/*
 * Mélange 2 vecteurs en fonction d'un pattern généré aléatoirement
 */
vector<float> shuffle_float(vector<float> *p1, vector<float> *p2) {

   vector<unsigned int> pattern;
   vector<float> child;

   unsigned int n = p1->size(); // Ici, p1 et p2 font forcément la même taille

   // Génère un pattern composé de 0 et de 1 (ex : 01001011)
   for(unsigned int i=0; i<n; i++) {
      pattern.push_back(rand() % 2);
   }

   // Pour un index i, si pattern[i] = 1, on garde la valeur de p1, sinon on garde celle de p2
   for(unsigned int i=0; i<n; i++) {
      if(pattern[i])    child.push_back(p1->at(i));
      else              child.push_back(p2->at(i));
   }

   return child;
}

/*
 * Créé une nouvelle solution (enfant) à partir de deux autres solutions (parents)
 */
Solution * reproduce(Solution *p1, Solution *p2, Instance *instance) {

   Solution * child = new Solution();

   // On mélange la liste des hôtels intermédiaires
   child->v_Id_Hotel_Intermedaire = shuffle_int(&p1->v_Id_Hotel_Intermedaire, &p2->v_Id_Hotel_Intermedaire);

   // On mélange les séquances de POI
   child->v_v_Sequence_Id_Par_Jour = crossover(p1->v_v_Sequence_Id_Par_Jour, p2->v_v_Sequence_Id_Par_Jour);

   // On mélange des heures de départ
   child->v_Date_Depart = shuffle_float(&p1->v_Date_Depart, &p2->v_Date_Depart);

   // On évalue (fonction objectif et score négatif) la nouvelle solution
   child->Evaluation_Solution(instance);

   return child;
}

/*
 * Reproduit une population
 * [!] La taille de la population doit être PAIRE [!]
 * Complexité : ~O(p*n) avec p = taille de la population et n = nombre de POI visités par solution
 */
vector<Solution*> reproduction(vector<Solution*> population, Instance *instance) {
   vector<Solution*> children;

   // Pour chaque "couple" de parents p1 et p2, on créé 2 enfants en "mélangeant" p1 à p2, puis p2 à p1.
   for(unsigned int i=0; i<population.size(); i+=2) {
      children.push_back(reproduce(population[i], population[i+1], instance));
      children.push_back(reproduce(population[i+1], population[i], instance));
   }

   return children;
}
