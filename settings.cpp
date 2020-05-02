#include "settings.hpp"
#include <cstdlib>

Settings::Settings() {
   debug = 0;

   seed = time(NULL);

   populationSize = 1000;

   maxIter = 1000;
   maxTime = 180.0;
   maxIterWithoutAmeliorations = 1000;

   condIter = false;
   condTime = true;
   condAmel = true;

   MIN_CUT_SIZE = 1;   // Taille min d'une coupe  /!\ Si des jours ont moins de 2 POI, mettre celle ci à 1 sinon crash
   MAX_CUT_SIZE = 2;   // Nombre de POI en 1 jour - MAX_CUT_SIZE = Taille max d'une coupe (ex: si 8 POI et MAX_CUT_SIZE=2, taille max = 6)

   // Probabilités de mutation, en %
   PROBA_MUT_HOTEL = 1;
   PROBA_MUT_POI = 50;
   PROBA_MUT_DATE = 5;

   // Changement max (positif ou négatif) de la date en une mutation
   MAX_CHANGE_ON_DATE = 5.0;
}

Settings::~Settings() {

}

void Settings::print() {
   cout << "----- Paramètres ---------------------------------------" << endl;
   cout << "Debug = " << debug << endl;
   cout << "Seed = " << seed << endl;
   cout << "Taille de la population = " << populationSize << endl;
   cout << "Condition d'arrêt = ";
   if(condIter)                           cout << "itérations";
   if(condIter && (condTime || condAmel)) cout << " OU ";
   if(condTime)                           cout << "temps";
   if(condTime && condAmel)               cout << " OU ";
   if(condAmel)                           cout << "itérations sans améliorations";
   cout << "\nArret au bout de : ";
   if(condIter)                           cout << maxIter << " itérations";
   if(condIter && (condTime || condAmel)) cout << " OU ";
   if(condTime)                           cout << maxTime << " secondes";
   if(condTime && condAmel)               cout << " OU ";
   if(condAmel)                           cout << maxIterWithoutAmeliorations << " itérations sans améliorations";
   cout << "\nProba. mutation hôtels = " << PROBA_MUT_HOTEL << "%" << endl;
   cout << "Proba. mutation poi = " << PROBA_MUT_POI << "%" << endl;
   cout << "Proba. mutation dates = " << PROBA_MUT_DATE << "%" << endl;
   cout << "--------------------------------------------------------" << endl;
}

void Settings::generateRandomSettings()
{
   srand(time(NULL));

   populationSize = 1000; //(rand() % (1250 - 125 + 1) + 125) * 4; //Un nombre entre 500 et 5 000, pair, dont la moitié est pair

   PROBA_MUT_HOTEL = rand () % (75) + 1;
   PROBA_MUT_POI = rand () % (75) + 1;
   PROBA_MUT_DATE = rand () % (75) + 1;

   MAX_CHANGE_ON_DATE = rand () % (10) + 1;
}

void Settings::parseArgv(int argc, const char * argv[]) {

   for(int i=1; i<argc; i++) {
      if(argv[i] == string("-debug"))
         debug = atoi(argv[i+1]);
      if(argv[i] == string("-seed"))
         seed = atol(argv[i+1]);
      if(argv[i] == string("-pop-size"))
         populationSize = atoi(argv[i+1]);
      if(argv[i] == string("-stop")) {
         condIter = false;
         condTime = false;
         condAmel = false;
         string cond = argv[i+1];
         if(cond.find("iter") != string::npos)   condIter = true;
         if(cond.find("time") != string::npos)   condTime = true;
         if(cond.find("amel") != string::npos)   condAmel = true;
      }
      if(argv[i] == string("-max-iter"))
         maxIter = atoi(argv[i+1]);
      if(argv[i] == string("-max-time"))
         maxTime = atof(argv[i+1]);
      if(argv[i] == string("-max-iterWA"))
         maxIterWithoutAmeliorations = atoi(argv[i+1]);
      if(argv[i] == string("-p-mut-hotel"))
         PROBA_MUT_HOTEL = atof(argv[i+1]);
      if(argv[i] == string("-p-mut-poi"))
         PROBA_MUT_POI = atof(argv[i+1]);
      if(argv[i] == string("-p-mut-date"))
         PROBA_MUT_DATE = atof(argv[i+1]);
      if(argv[i] == string("-h")) {
         displayHelp();
         exit(0);
      }
   }
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
