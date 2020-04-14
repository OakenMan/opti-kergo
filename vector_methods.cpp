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

void print(vector<float> &v) {
   cout << fixed << setprecision(2);
   cout << "[ ";
   for(unsigned int i=0; i<v.size(); i++) {
      cout << v[i] << " ";
   }
   cout << "]" << endl;
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

/*
 * Ajoute la population 2 à la population 1
 */
void fusion(vector<Solution*> *pop1, vector<Solution*> pop2) {

   // On ajoute la population 2 à la population 1
   for(unsigned int i=0; i<pop2.size(); i++) {
      pop1->push_back(pop2[i]);
   }

}
