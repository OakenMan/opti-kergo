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
