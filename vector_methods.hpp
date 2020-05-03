#ifndef vector_methods_hpp
#define vector_methods_hpp

#include <vector>

using namespace std;

/*
 * Fonctions utilisées pour manipuler plus facilement des vecteurs
 */

/*
 * Affiche un vecteur d'unsigned int sous cette forme : "[ x y z ] (n=taille) \n"
 */
void printVector(vector<unsigned int> &v);

/*
 * Affiche un vecteur de floats sous cette forme : "[ x y z ] (n=taille) \n"
 */
void printVector(vector<float> &v);

/*
 * Retourne vrai si v contient value, faux sinon
 */
bool contains(vector<unsigned int> v, unsigned int value);

/*
 * Retourne l'index de value dans v, ou v.end()-1 si value n'est pas dans v
 */
unsigned indexOf(vector<unsigned int> v, unsigned int value);

/*
 * Génère un vecteur aléatoirement, de taille compris entre minSize et maxSize, et de valeurs comprises entre 0 et maxValue
 */
vector<unsigned int> randomVector(unsigned int minSize, unsigned int maxSize, unsigned int maxValue);

/*
 * Fusionne tous les vecteurs d'un vecteur de vecteur, pour ne former qu'un seul vecteur ._.
 */
vector<unsigned int> linkVectors(vector<vector<unsigned int>> v);

#endif
