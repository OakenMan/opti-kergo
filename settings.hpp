#ifndef settings_hpp
#define settings_hpp

#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <string>
#include <cstdlib>

using namespace std;

/*
 * Classe qui contient tous les paramètres de l'algorithme
 */
class Settings
{
   public:
      int debug;  // Niveau de debug (0 = aucune affichage)

      long seed;  // Seed utilisé pour la génération de nombres aléatoires

      int populationSize;  // Taille de la population

      int maxIter;                     // Nombre max d'itérations avant arrêt
      double maxTime;                  // Nombre max de secondes avant arrêt
      int maxIterWithoutAmeliorations; // Nombre max d'itérations sans améliorations avant arrêt

      bool condIter;    //
      bool condTime;    // Booléens pour les conditions d'arrêt
      bool condAmel;    //

      // Probabilités de mutation, en %
      float PROBA_MUT_HOTEL;
      float PROBA_MUT_POI;
      float PROBA_MUT_DATE;

      // Changement max (positif ou négatif) de la date en une mutation
      float MAX_CHANGE_ON_DATE;

   public:
       /* Constructeur et destructeur  */
       Settings();
       virtual ~Settings();

       /*
        * Génère des paramètres au hasard, utilisé dans le programme "find_parameters"
        * Actuellement non-utilisé
        */
       void generateRandomSettings();

       /*
        * Affiche les paramètres
        */
       void print();

       /*
        * Parse les paramètres à partir des arguments du programme
        */
       void parseArgv(int argc, const char * argv[]);

};

/*
 * Affiche l'aide (./exec -h)
 */
void displayHelp();

#endif
