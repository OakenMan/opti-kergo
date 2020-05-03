#define CHEMIN_DOSSIER_DONNEES "Data/"
#define NOM_FICHIER_LISTE_FICHIER_DONNEES "data.txt"
#define NOM_FICHIER_LISTE_SORTIE "sortie.txt"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <limits.h>

#include "Instance.hpp"
#include "Solution.hpp"

#include "selection.hpp"
#include "generation.hpp"
#include "reproduction.hpp"
#include "mutation.hpp"
#include "vector_methods.hpp"
#include "stats.hpp"
#include "settings.hpp"

using namespace std;

Instance* Prechargement_Instance();
int Resolution(Settings s, Instance* instance);

int main(int argc, const char * argv[])
{
  unsigned int NOMBRE_ITER_PAR_SETTINGS = 5;
  unsigned int NOMRE_SECONDES_PAR_EXECUTION = 600; // 8h = 28800

  Settings s;
  Settings best_setting;
  float best_score = 0;
  float score_solution_total = 0;
  Instance * instance = Prechargement_Instance();

  chrono::time_point<chrono::system_clock> chrono_start, chrono_end;
  chrono::duration<double> elapsed = chrono::duration<double>::zero();
  chrono_start = chrono::system_clock::now();

  while (elapsed.count() < NOMRE_SECONDES_PAR_EXECUTION)
  {
    s.generateRandomSettings();
    s.printSettings();
    score_solution_total = 0;

    // cout << "Test avec les settings suivantes : " << endl;
    // s.print();

    for (unsigned int i = 0; i < NOMBRE_ITER_PAR_SETTINGS; i++)
    {
       int score = Resolution(s, instance);
       score_solution_total += score;
       cout << i << " - " << score << endl;
    }

    float score_moyen = float(score_solution_total / NOMBRE_ITER_PAR_SETTINGS);
    if (score_moyen > best_score)
    {
      cout << "MEILLEURS SETTINGS TROUVÉS : " << endl;
      best_score = score_moyen;
      best_setting = s;
      
      cout << "Score moyen = " << best_score << endl;
    }
    else
    {
<<<<<<< HEAD
      cout << "Settings moins bien" << endl;
      cout << "score moyen = " << float(score_solution_total / NOMBRE_ITER_PAR_SETTINGS) << endl;
=======
      cout << "SETTINGS MOINS BIEN" << endl;
      // s.print();
      // cout << "Score moyen = " << score_moyen << endl;
>>>>>>> 42fa5de29d6a3786b46354fe02e3f3a1914489b6
    }

    chrono_end = chrono::system_clock::now();
    elapsed = chrono_end - chrono_start;
    cout << "time = " << elapsed.count() << "s" << endl;
  }

  cout << "BEST SETTINGS : " << endl;
  best_setting.print();
  cout << "MOYENNE : " << best_score << endl;
}

Instance* Prechargement_Instance()
{
  string s_tmp;
  string s_chemin=CHEMIN_DOSSIER_DONNEES;         // s_chemin = ".../opti-kergo/Data/"
  s_chemin.append(NOM_FICHIER_LISTE_FICHIER_DONNEES);   // s_chemin = ".../opti-kergo/Data/data.txt"
  ifstream fichier(s_chemin.c_str(), std::ios::in);   // fichier = fichier data.txt

  Instance * instance = new Instance();

  if(fichier)
  {
    getline(fichier,s_tmp);   // on récupère une ligne du fichier dans s_tmp

    s_chemin=CHEMIN_DOSSIER_DONNEES;
    s_chemin.append(s_tmp);
    s_chemin.erase(remove(s_chemin.begin(), s_chemin.end(), '\r'), s_chemin.end());
    s_chemin.erase(remove(s_chemin.begin(), s_chemin.end(), '\n'), s_chemin.end());

    if(instance->chargement_Instance(s_chemin));
    else {
      cout<<"Erreur : impossible de charger l'instance "<<s_tmp<<endl;
    }
  }

  else
  {
    cout<<" Erreur lecture des données : chemin listant l'ensemble des données non valide. "<<endl;
  }

  fichier.close();
  return instance;
}

int Resolution(Settings s, Instance* instance)
{
  unsigned int i_best_solution_score=0;

  try
  {
					     // Création des timers
    chrono::time_point<chrono::system_clock> chrono_start, chrono_end;
    chrono::duration<double> elapsed;
    chrono_start = chrono::system_clock::now();

                      /*------------- Paramètres de l'algo -------------*/
    srand(time(NULL));
                      /*------------- Algorithme génétique -------------*/
    vector<Solution*> population = generation(instance, s.populationSize);   // Génération de la population de base

    int iterations = 0;
    int iterWithoutAmeliorations = 0;
    bool finished = false;

    for(iterations=0; !finished; iterations++) {

      vector<Solution*> selection = Selection(population);                 // Selection sur la population
      vector<Solution*> children = reproduction(selection, instance);      // Reproduction de la selection
<<<<<<< HEAD
      mutation(children, instance, &s);                                    // Mutation des enfants
=======
      mutation(children, instance, &s);                                        // Mutation des enfants
>>>>>>> 42fa5de29d6a3786b46354fe02e3f3a1914489b6
      population.clear();
      population = fusion(selection, children);                            // Ajout des enfants à la population de base

      // Update du chrono
      chrono_end = chrono::system_clock::now();
      elapsed=chrono_end-chrono_start;

      // Update du nombre d'itérations sans améliorations
      if(bestSolution(population, true) > i_best_solution_score) {
        iterWithoutAmeliorations = 0;
      }
      else {
        iterWithoutAmeliorations++;
      }

      // Conditions d'arrêt
      if(s.condIter && iterations >= s.maxIter-1)
<<<<<<< HEAD
         finished = true;
      if(s.condTime && elapsed.count() >= s.maxTime)
         finished = true;
      if(s.condAmel && iterWithoutAmeliorations >= s.maxIterWithoutAmeliorations)
         finished = true;
=======
      {
        finished = true;
      }
      if(s.condTime && elapsed.count() >= s.maxTime)
      {
        finished = true;
      }
      if(s.condAmel && iterWithoutAmeliorations >= s.maxIterWithoutAmeliorations)
      {
        finished = true;
      }
>>>>>>> 42fa5de29d6a3786b46354fe02e3f3a1914489b6

      i_best_solution_score = bestSolution(population, true);     // Mise à jour du meilleur score
      cout << "i_best_solution_score = " << i_best_solution_score << " & iter = " << iterations << endl;
    }

    // cout << "Finished in " << elapsed.count() << "s/" << iterations << " itérations" << endl;

    deletePopulation(population);   // On supprime la population finale à la fin de l'algo
    /*---------------------------------------------------*/
  }
  catch(string err)
  {
    cout << "Erreur fatale : " <<endl;
    cout << err <<endl;
  }

  return i_best_solution_score;
}
