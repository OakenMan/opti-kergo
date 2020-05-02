#ifndef settings_hpp
#define settings_hpp

#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <string>

using namespace std;

class Settings
{
   public:
      int debug;

      long seed;

      int populationSize;

      int maxIter;
      double maxTime;
      int maxIterWithoutAmeliorations;

      bool condIter;
      bool condTime;
      bool condAmel;

      unsigned int MIN_CUT_SIZE;   // Taille min d'une coupe  /!\ Si des jours ont moins de 2 POI, mettre celle ci à 1 sinon crash
      unsigned int MAX_CUT_SIZE;   // Nombre de POI en 1 jour - MAX_CUT_SIZE = Taille max d'une coupe (ex: si 8 POI et MAX_CUT_SIZE=2, taille max = 6)

      // Probabilités de mutation, en %
      float PROBA_MUT_HOTEL;
      float PROBA_MUT_POI;
      float PROBA_MUT_DATE;

      // Changement max (positif ou négatif) de la date en une mutation
      float MAX_CHANGE_ON_DATE;

   public:
   /* Constructeurs et destructeur  */
       Settings();
       virtual ~Settings();

       void printSettings();

       void parseArgv(int argc, const char * argv[]);

};

void displayHelp();

#endif
