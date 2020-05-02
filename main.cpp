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

int Resolution(Instance * instance, Settings s);

int main(int argc, const char * argv[])
{
   /*---------- Création de la classe de paramètres ------------------------------------*/
   Settings s;               // Cette action est réalisée une seule fois au début
   s.parseArgv(argc, argv);  // du programme pour que toutes les instances soient
   s.print();                // résolues avec les mêmes paramètres (voir 'settings.hpp')
   /*-----------------------------------------------------------------------------------*/

   try
   {
      string s_tmp;
      string s_chemin=CHEMIN_DOSSIER_DONNEES;					// s_chemin = ".../opti-kergo/Data/"
      s_chemin.append(NOM_FICHIER_LISTE_FICHIER_DONNEES);		// s_chemin = ".../opti-kergo/Data/data.txt"

      ifstream fichier(s_chemin.c_str(), std::ios::in);		// fichier = fichier data.txt

		std::ofstream fichier_Sortie_Resume;

      s_chemin=CHEMIN_DOSSIER_DONNEES;						// s_chemin = ".../opti-kergo/"
      s_chemin.append(NOM_FICHIER_LISTE_SORTIE);				//s_chemin = ".../opti-kergo/sortie.txt"
      ofstream fichier_Sortie(s_chemin.c_str(), std::ios::out | std::ios::app);	// fichier_Sortie = sortie.txt

      if(fichier)
      {
         if(fichier_Sortie)
         {
            fichier_Sortie<<"Fichier données\t\tTps de résolution \tBest solution"<<endl;

            getline(fichier,s_tmp);		// on récupère une ligne du fichier dans s_tmp

            while(s_tmp!="")
            {
               Instance * instance = new Instance();

					// Création des timers
               chrono::time_point<chrono::system_clock> chrono_start, chrono_end;
               chrono::duration<double> elapsed;

               unsigned int i_best_solution_score=0;

               s_chemin=CHEMIN_DOSSIER_DONNEES;

               cout<< "Résolution de "<<s_tmp<<endl;

               s_chemin.append(s_tmp);
               s_chemin.erase(remove(s_chemin.begin(), s_chemin.end(), '\r'), s_chemin.end());
               s_chemin.erase(remove(s_chemin.begin(), s_chemin.end(), '\n'), s_chemin.end());

               if(instance->chargement_Instance(s_chemin)) {	// on charge l'instance du fichier pointé par s_tmp
                  chrono_start = chrono::system_clock::now();

                  i_best_solution_score = Resolution(instance, s);

                  chrono_end = chrono::system_clock::now();
                  elapsed = chrono_end - chrono_start;

                  // écriture sur le fichier de sortie
                  fichier_Sortie<<s_tmp <<"\t\t\t"<<elapsed.count()<<"\t\t\t"<< i_best_solution_score <<endl;

                  s_tmp="";
                  getline(fichier,s_tmp);		// on relie une ligne et on recommence
                  delete instance;

               }
               else {
                  cout<<"Erreur : impossible de charger l'instance "<<s_tmp<<endl;
                  s_tmp="";
                  getline(fichier,s_tmp);		// on relie une ligne et on recommence
               }
            }
            fichier_Sortie.close();
         }
         else
         {
             cout<<" Erreur lecture des données : chemin vers la sortie non valide. "<<endl;
         }
         fichier.close();
       }
       else
       {
          cout<<" Erreur lecture des données : chemin listant l'ensemble des données non valide. "<<endl;
       }
    }
    catch(string err)
    {
        cout << "Erreur fatale : " << err << endl;
    }
    return 0;
}

int Resolution(Instance * instance, Settings s)
{
   /*------------- Paramètres de l'algo -------------*/
   srand(s.seed);
   cout << fixed << setprecision(2);   // Limitation de l'affichage à 2 chiffres après la virgule

   /*------------------ Variables -------------------*/
   // Timers (pour vérifier la condition d'arrêt en fonction du temps)
   chrono::time_point<chrono::system_clock> chrono_start, chrono_end;
   chrono::duration<double> elapsed;

   int iterations = 0;                    // Nombre d'itérations effectuées
   int iterWithoutAmeliorations = 0;      // Nombre d'itérations sans améliorations effectuées
   bool finished = false;                 // Boolean pour arrêter l'algorithme

   unsigned int bestScore = 0;         // Score de la meilleure solution

   /*------------- Algorithme génétique -------------*/

   chrono_start = chrono::system_clock::now();

   vector<Solution*> population = generation(instance, s.populationSize);   // Génération de la population de base

   if(s.debug >= 1) {
      cout << "--------------------------------------------------------" << endl;
      cout << "=== Population de base ===" << endl;
      analyse(population);
   }

   for(iterations=0; !finished; iterations++) {

      vector<Solution*> selection = Selection(population);                 // Selection sur la population
      vector<Solution*> children = reproduction(selection, instance);      // Reproduction de la selection
      mutation(children, instance, &s);                                    // Mutation des enfants
      population.clear();
      population = fusion(selection, children);                            // Ajout des enfants à la population de base

      // Mise à jour du chrono
      chrono_end = chrono::system_clock::now();
      elapsed = chrono_end - chrono_start;

      // Mise à jour du nombre d'itérations sans améliorations
      if(getBestScore(population, true) > bestScore) {
          iterWithoutAmeliorations = 0;
      }
      else {
          iterWithoutAmeliorations++;
      }

      // Conditions d'arrêt
      if(s.condIter && iterations >= s.maxIter-1)                                   // Si on a dépassé le nombre max d'itérations
          finished = true;
      if(s.condTime && elapsed.count() >= s.maxTime)                                // Si on a dépassé la limite de temps
          finished = true;
      if(s.condAmel && iterWithoutAmeliorations >= s.maxIterWithoutAmeliorations)   // Si on dépassé le nombre max d'itérations sans améliorations
          finished = true;

      // Mise à jour du meilleur score
      bestScore = getBestScore(population, true);

      // cout << "it=" << iterations << ", best=" << bestScore << endl;
   }

   if(s.debug >= 1) {
      cout << "\n=== Population finale ===" << endl;
      analyse(population);
      cout << "--------------------------------------------------------" << endl;
   }

   Solution * bestSolution = getBestSolution(population);

   bestSolution->print();

   bestSolution->Verification_Solution(instance);

   deletePopulation(population);   // On supprime de la mémoire la population finale à la fin de l'algo

   cout << "Fin de résolution en " << elapsed.count() << "s/" << iterations << " itérations" << endl;
   cout << "Meilleure solution : " << bestScore << endl;
   cout << "--------------------------------------------------------" << endl;

   return bestSolution->i_valeur_fonction_objectif;
}
