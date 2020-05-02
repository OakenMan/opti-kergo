#include "settings.hpp"
#include <cstdlib>

Settings::Settings()
{

}

Settings::~Settings()
{

}

void Settings::print() {
   cout << "----- Paramètres ---------------------------------------" << endl;
   cout << "Seed = " << this->seed << endl;
   cout << "Taille de la population = " << this->populationSize << endl;
   cout << "Condition d'arrêt = " << this->cond_arret << endl;
   cout << "Arret au bout de : ";
   if(cond_arret == "iterations")      cout << maxIter << " itérations" << endl;
   if(cond_arret == "time")            cout << maxTime << " secondes" << endl;
   if(cond_arret == "ameliorations")   cout << maxIterWithoutAmeliorations << " itérations sans améliorations" << endl;
   cout << "Proba. mutation hôtels = " << this->PROBA_MUT_HOTEL << endl;
   cout << "Proba. mutation poi = " << this->PROBA_MUT_POI << endl;
   cout << "Proba. mutation dates = " << this->PROBA_MUT_DATE << endl;
   cout << "--------------------------------------------------------" << endl;
}

void Settings::generateRandomSettings()
{
   srand(time(NULL));

   populationSize = (rand() % (1250 - 125 + 1) + 125) * 4; //Un nombre entre 500 et 5 000, pair, dont la moitié est pair

   PROBA_MUT_HOTEL = rand () % (75) + 1;
   PROBA_MUT_POI = rand () % (75) + 1;
   PROBA_MUT_DATE = rand () % (75) + 1;

   MAX_CHANGE_ON_DATE = rand () % (10) + 1;
}

Settings parseArgv(int argc, const char * argv[]) {

   Settings s = Settings();

   for(int i=1; i<argc; i++) {
      if(argv[i] == string("-seed"))
         s.seed = atol(argv[i+1]);
      if(argv[i] == string("-pop-size"))
         s.populationSize = atoi(argv[i+1]);
      if(argv[i] == string("-stop"))
         s.cond_arret = argv[i+1];
      if(argv[i] == string("-max-iter"))
         s.maxIter = atoi(argv[i+1]);
      if(argv[i] == string("-max-time"))
         s.maxTime = atof(argv[i+1]);
      if(argv[i] == string("-max-iterWA"))
         s.maxIterWithoutAmeliorations = atoi(argv[i+1]);
      if(argv[i] == string("-p-mut-hotel"))
         s.PROBA_MUT_HOTEL = atof(argv[i+1]);
      if(argv[i] == string("-p-mut-poi"))
         s.PROBA_MUT_POI = atof(argv[i+1]);
      if(argv[i] == string("-p-mut-date"))
         s.PROBA_MUT_DATE = atof(argv[i+1]);
      if(argv[i] == string("-h")) {
         displayHelp();
         exit(0);
      }
   }

   return s;

}

void displayHelp() {
   cout << "Options : " << endl;
   cout << "-seed [int] \t\t\t\t Généré au hasard si non-précisé" << endl;
   cout << endl;
   cout << "-pop-size [int] \t\t\t Nombre dont la moitié est paire" << endl;
   cout << endl;
   cout << "-stop [iterations|time|ameliorations] \t Condition d'arrêt" << endl;
   cout << "-max-iter [int] \t\t\t Nombre max d'itérations" << endl;
   cout << "-max-time [float] \t\t\t Durée maximale d'exécution" << endl;
   cout << "-max-iterWA [int] \t\t\t Nombre max d'itérations sans amélioration" << endl;
   cout << endl;
   cout << "-p-mut-hotel [float] \t\t\t Pourcentage entre 0 et 100" << endl;
   cout << "-p-mut-poi [float] \t\t\t Pourcentage entre 0 et 100" << endl;
   cout << "-p-mut-date [float] \t\t\t Pourcentage entre 0 et 100" << endl;
}