#ifndef settings_hpp
#define settings_hpp

#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <string>

using namespace std;

class Settings {
   public:
      long seed = time(NULL);

      int populationSize = 1000;

      int maxIter = 1000;
      double maxTime = 60.0;
      int maxIterWithoutAmeliorations = 100;

      string cond_arret = "ameliorations";

      unsigned int MIN_CUT_SIZE = 1;   // Taille min d'une coupe  /!\ Si des jours ont moins de 2 POI, mettre celle ci à 1 sinon crash
      unsigned int MAX_CUT_SIZE = 2;   // Nombre de POI en 1 jour - MAX_CUT_SIZE = Taille max d'une coupe (ex: si 8 POI et MAX_CUT_SIZE=2, taille max = 6)

      // Probabilités de mutation, en %
      float PROBA_MUT_HOTEL = 1;
      float PROBA_MUT_POI = 50;
      float PROBA_MUT_DATE = 5;

      // Changement max (positif ou négatif) de la date en une mutation
      float MAX_CHANGE_ON_DATE = 5.0;

   public:
    /* Constructeurs et destructeur  */
        Settings();
        virtual ~Settings();

        void print();
        void generateRandomSettings();

};

Settings parseArgv(int argc, const char * argv[]);

void displayHelp();

#endif
