#ifndef vector_methods_hpp
#define vector_methods_hpp

#include <stdio.h>
#include <vector>

using namespace std;

/*
 * Affiche un vecteur sous cette forme : "[ x y z ] (n=taille) \n"
 */
void print(vector<unsigned int> &v);

/*
 * Retourne vrai si v contient value, faux sinon
 */
bool contains(vector<unsigned int> v, unsigned int value);

/*
 * Retourne l'index de value dans v, ou v.end()-1 si value n'est pas dans v
 */
unsigned indexOf(vector<unsigned int> v, unsigned int value);

#endif
