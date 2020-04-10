#include "reproduction.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

void print(vector<unsigned int> &v) {
   for(unsigned int i=0; i<v.size(); i++) {
      cout << v[i] << " ";
   }
}

/*
   Croisement:
	Hotels : Croisement de séquence idiot
	POIs : opérateur de croisement : PMX, on travaille juste sur un seul jour
	Date départ : croisement de séquence idiot

   PMX - Cas à gérer :
   - parents de taille différentes (ex: p1=[1 3 4] et p2=[6 3 1 4 5])
   - parents avec des contenus différentes (ex : p1=[1 2 3] et p2=[4 5 6])
*/


int main(int argc, const char * argv[]){

   srand(time(NULL));

   vector<unsigned int> p1 = {1, 5, 3, 2, 7, 6, 4};
   vector<unsigned int> p2 = {6, 3, 5, 1, 2, 4, 7};

   chrono::time_point<chrono::system_clock> chrono_start, chrono_end;
   chrono::duration<double> elapsed;

   chrono_start = chrono::system_clock::now();

   for(unsigned int i=0; i<10; i++){
      vector<unsigned int> c1 = shuffle_int(p1, p2);
      vector<unsigned int> c2 = shuffle_int(p2, p1);

      cout << "child1 = ";
      print(c1);
      cout << "\nchild2 = ";
      print(c2);
      cout << endl;
      cout << "------------" << endl;
   }

   chrono_end = chrono::system_clock::now();

   elapsed=chrono_end-chrono_start;

   cout << "time = " << elapsed.count() << endl;

   return 0;
}

/**
 * Retourne vrai si v contient value, faux sinon
 */
bool contains(vector<unsigned int> v, unsigned int value) {
   return find(v.begin(), v.end(), value) != v.end();
}

/**
 * Retourne l'index de value dans v, ou v.end() si value n'est pas dans v
 */
unsigned int indexOf(vector<unsigned int> v, unsigned int value) {
   vector<unsigned int>::iterator it = find(v.begin(), v.end(), value);
   // if(it == v.end()) return -1;                          // <--- engendre une segfault dans le pmx
   // else              return distance(v.begin(), it);
   return distance(v.begin(), it);
}

/**
 * Applique un algorithme PMX (Partial-Mapped-Crossover) légèrement modifié (pour gérer des cas de tableaux de taille différentes
 * ou avec des éléments différents) à deux tableaux représentant des séquences de POI pour un jour de voyage.
 */
vector<unsigned int> pmx(vector<unsigned int> p1, vector<unsigned int> p2) {

   vector<unsigned int> child;

   unsigned int n1 = p1.size();
   unsigned int n2 = p2.size();

   unsigned int smallestSize = min(n1, n2);

   // On modifie les parents en rajoutant des 0 pour qu'ils soient de même taille
   // (TODO : faire ça sur des copies pour pas modifier réellement les parents)

   // Si p1 plus grand que p2
   if(n2 < n1) {
      // On rallonge p2
      for(unsigned int i=0; i<n1-n2; i++) {
         p2.push_back(0);
      }
   }
   // Si p2 plus grand que p1
   else if(n1 < n2) {
      // On rallonge p1
      for(unsigned int i=0; i<n2-n1; i++) {
         p1.push_back(0);
      }
   }

   unsigned int n = p1.size();

   // Initialisation des enfants
   for(unsigned int i=0; i<n; i++) {
      child.push_back(0);
   }

   // Indices choisis pour la "coupe"
   // cutLength = rand(2, n-2)
   // cutStart = rand(0, n-cutLength)
   // coupe = [cutStart, cutEnd]
   unsigned int cutLength  = MIN_CUT_SIZE + rand() % (smallestSize - MAX_CUT_SIZE);
   unsigned int cutStart   = rand() % (smallestSize - cutLength + 1);
   unsigned int cutEnd     = cutStart + cutLength - 1;

   cout << "n=" << n << ", length=" << cutLength << ", coupe=[" << cutStart << ", " << cutEnd << "]" << endl;

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
      it = find(child.begin(), child.end(), 0);
      if(it != child.end()) {
         if(*it == 0) {
            child.erase(it);
         }
      }
   } while(it != child.end());

   return child;
}

vector<unsigned int> shuffle_int(vector<unsigned int> p1, vector<unsigned int> p2) {

   vector<unsigned int> child;

   unsigned int n = p1.size(); // ici, p1 et p2 font forcément la même taille

   vector<unsigned int> pattern;

   // Génère un pattern composé de 0 et de 1
   for(unsigned int i=0; i<n; i++) {
      pattern.push_back(rand() % 2);
   }

   print(pattern);
   cout << endl;

   for(unsigned int i=0; i<n; i++) {
      if(pattern[i])    child.push_back(p1[i]);
      else              child.push_back(p2[i]);
   }

   return child;
}

vector<float> shuffle_float(vector<float> p1, vector<float> p2) {

   vector<float> child;

   unsigned int n = p1.size(); // ici, p1 et p2 font forcément la même taille

   vector<unsigned int> pattern;

   // Génère un pattern composé de 0 et de 1
   for(unsigned int i=0; i<n; i++) {
      pattern.push_back(rand() % 2);
   }

   print(pattern);
   cout << endl;

   for(unsigned int i=0; i<n; i++) {
      if(pattern[i])    child.push_back(p1[i]);
      else              child.push_back(p2[i]);
   }

   return child;
}

Solution faireUnBebe(Solution *papa, Solution *maman) {
   Solution *child = new Solution();

   // On mélange la liste des hôtels intermédiaires
   child->v_Id_Hotel_Intermedaire = shuffle_int(papa->v_Id_Hotel_Intermedaire, maman->v_Id_Hotel_Intermedaire);

   // On choisit un jour au hasard et on mélange la séquence des POI de ce jour
   unsigned int index = rand() % papa->v_v_Sequence_Id_Par_Jour.size();
   child->v_v_Sequence_Id_Par_Jour[index] = pmx(papa->v_v_Sequence_Id_Par_Jour[index], maman->v_v_Sequence_Id_Par_Jour[index]);

   // On mélange des heures de départ
   child->v_Date_Depart = shuffle_float(papa->v_Date_Depart, maman->v_Date_Depart);

   return *child;
}

vector<Solution> reproduction(vector<Solution> population) {
   vector<Solution> children;

   return children;
}
