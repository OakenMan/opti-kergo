#define CHEMIN_DOSSIER_DONNEES "Data/"
#define NOM_FICHIER_LISTE_FICHIER_DONNEES "data.txt"
#define NOM_FICHIER_LISTE_SORTIE "sortie.txt"

#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include "Instance.hpp"
#include "Solution.hpp"
#include "selection.hpp"
#include "generation.hpp"
#include "reproduction.hpp"
#include "mutation.hpp"
#include "vector_methods.hpp"

using namespace std;

int Resolution(Instance * instance);

unsigned int bestSolution(vector<Solution*> population, bool onlyfeasible) {
   unsigned int bestSolution = 0;

   for(unsigned int i=0; i<population.size(); i++) {
      if(onlyfeasible) {
         ///
      }
      else {
         if(population[i]->i_valeur_fonction_objectif > bestSolution) {
            bestSolution = population[i]->i_valeur_fonction_objectif;
         }
      }
   }

   return bestSolution;
}

int main(int argc, const char * argv[])
{
    try
    {
        string s_tmp;
        string s_chemin=CHEMIN_DOSSIER_DONNEES;					// s_chemin = ".../opti-kergo/Data/"
        s_chemin.append(NOM_FICHIER_LISTE_FICHIER_DONNEES);		// s_chemin = ".../opti-kergo/Data/data.txt"

        ifstream fichier(s_chemin.c_str(), std::ios::in);		// fichier = fichier data.txt

		std::ofstream fichier_Sortie_Resume;					// ???

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

					// création des timers
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

                      /*------------- Et maintenant... l'algo -------------*/

                      vector<unsigned int> scores;

                      int nbIter = 1000;
                      int populationSize = 1000;

                      vector<Solution*> population = generation(instance, populationSize);

                      for(int i=0; i<nbIter; i++) {
                        scores.push_back(bestSolution(population, false));
                        vector<Solution*> selection = Selection(population);     // Selection sur la population
                        vector<Solution*> children = reproduction(selection);    // Reproduction de la selection
                        mutation(children, instance);                            // Mutation des enfants
                        fusion(&selection, children);                            // Ajout des enfants à la population de base
                      }

                      i_best_solution_score = bestSolution(population, false);

                      /*---------------------------------------------------*/

                      chrono_end = chrono::system_clock::now();

                      cout<< "Fin de résolution de "<<s_tmp<<endl;

                      elapsed=chrono_end-chrono_start;

                      // écriture sur le fichier de sortie
                      fichier_Sortie<<s_tmp <<"\t\t\t"<<elapsed.count()<<"\t\t\t"<< i_best_solution_score <<endl;

                      s_tmp="";
                      getline(fichier,s_tmp);		// on relie une ligne et on recommence
                      delete instance;
                    }
                    else {
                       cout<<"Erreur impossible "<<endl;
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
        cout << "Erreur fatale : " <<endl;
        cout << err <<endl;
    }
    return 0;
}

int Resolution(Instance * instance)
{
    unsigned int i_val_Retour_Fct_obj=0;
    Solution * uneSolution = new Solution();
    vector<unsigned int> v_i_tmp ;

/*INITIALISATION D'UN SOLUTION EN DUR*/
    v_i_tmp.clear();
    uneSolution->v_Id_Hotel_Intermedaire.push_back(2);
    uneSolution->v_Date_Depart.push_back(0.0);
    uneSolution->v_Date_Depart.push_back(0.0);
    v_i_tmp ={0, 2, 5, 9, 14, 21, 28, 20, 27, 35, 42, 36, 29, 22, 30, 31};
    uneSolution->v_v_Sequence_Id_Par_Jour.push_back(v_i_tmp);
    v_i_tmp ={24, 32, 40, 33, 25, 19, 26, 34, 41, 47, 52, 56, 59, 61};
    uneSolution->v_v_Sequence_Id_Par_Jour.push_back(v_i_tmp);
    uneSolution->i_valeur_fonction_objectif=816;
/* */

    uneSolution->Verification_Solution(instance);

    i_val_Retour_Fct_obj=uneSolution->i_valeur_fonction_objectif;
    delete uneSolution;
    return i_val_Retour_Fct_obj;
}
