#define CHEMIN_DOSSIER_DONNEES "Data/"
#define NOM_FICHIER_LISTE_FICHIER_DONNEES "data.txt"

#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <time.h>
#include "Instance.hpp"
#include "Solution.hpp"
#include "vector_methods.hpp"

using namespace std;

Instance* charger_instance();
Solution* mock_solution(Instance * instance);

//TODO : Mettre en place un vrai framework de test (voir Catch2)

int main(int argc, const char * argv[])
{
	// srand(time(NULL));
	srand(1);
    Instance * instance = charger_instance();
    vector<Solution*> solutions;
    for (unsigned int i = 0; i < 3; i++)
    {
    	cout << "*** Solution " << i << "***" << endl;
    	solutions.push_back(generateSolution(instance));
    	solutions[i]->print();
    	cout << endl;
    }
    // //CALCULER SCORE : VALIDE
    // cout << "on test la fonction de calcul du score de retard" << endl;
    // calculer_score_retard(45, 20, 19, 0, 30, 1, 5);
    // calculer_score_retard(45, 25, 19, 0, 30, 1, 5);
    // calculer_score_retard(45, 30, 19, 0, 30, 1, 5);
    // calculer_score_retard(45, 40, 19, 0, 30, 1, 5);
    // calculer_score_retard(45, 44, 19, 0, 30, 1, 5);

    //FONCTION VECTORS :
    cout << "Indice de la solution ayant le score objectif max : " << indice_score_objectif_max(&solutions) << endl;
    cout << "Indice de la solution ayant le ratio score obj. / score neg. max : " << indice_ratio_obj_neg_max(&solutions) << endl;
    cout << "On trie le tableau de solutions ayant un score neg" << endl;
    trier_tableau_par_ratio_objectif_negatif(&solutions);
    cout << "nouveau tableau : " << endl;
    for (unsigned int i = 0; i < 3; i++)
    {
    	cout << "*** Solution " << i << "***" << endl;
    	solutions[i]->print();
    	cout << endl;
    }
    cout << "on mélange" << endl;
    melange_tableau(&solutions);
    cout << "nouveau tableau : " << endl;
    for (unsigned int i = 0; i < 3; i++)
    {
    	cout << "*** Solution " << i << "***" << endl;
    	solutions[i]->print();
    	cout << endl;
    }
}

Instance* charger_instance()
{
	try
    {
        string s_tmp;
        string s_chemin=CHEMIN_DOSSIER_DONNEES;					// s_chemin = ".../opti-kergo/Data/"
        s_chemin.append(NOM_FICHIER_LISTE_FICHIER_DONNEES);		// s_chemin = ".../opti-kergo/Data/data.txt"

        ifstream fichier(s_chemin.c_str(), std::ios::in);		// fichier = fichier data.txt

        s_chemin=CHEMIN_DOSSIER_DONNEES;						// s_chemin = ".../opti-kergo/"

        if(fichier)
        {
	        getline(fichier,s_tmp);		// on récupère une ligne du fichier dans s_tmp

	       	Instance * instance = new Instance();

	        s_chemin=CHEMIN_DOSSIER_DONNEES;

	        s_chemin.append(s_tmp);
	        s_chemin.erase(remove(s_chemin.begin(), s_chemin.end(), '\r'), s_chemin.end());
	        s_chemin.erase(remove(s_chemin.begin(), s_chemin.end(), '\n'), s_chemin.end());

	        instance->chargement_Instance(s_chemin);
	        fichier.close();

	        return instance;
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

    return nullptr;
}

Solution* mock_solution(Instance * instance)
{
	cout << "Mock d'une solution" << endl;
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
    uneSolution->Evaluation_Solution(instance);
/* */
    uneSolution->Verification_Solution(instance);
    uneSolution->print();

    return uneSolution;
}