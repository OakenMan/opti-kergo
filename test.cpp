#define CHEMIN_DOSSIER_DONNEES "Data/"
#define NOM_FICHIER_LISTE_FICHIER_DONNEES "data.txt"
#define NOM_FICHIER_LISTE_SORTIE "sortie.txt"

#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include "Instance.hpp"
#include "Solution.hpp"

using namespace std;

Instance* charger_instance();
Solution* mock_solution(Instance * instance);

//TODO : Mettre en place un vrai framework de test (voir Catch2)

int main(int argc, const char * argv[])
{
    Instance * instance = charger_instance();
    Solution* solution = mock_solution(instance);
    vector<Solution*> solutions;
    solutions.push_back(solution);
    //CALCULER SCORE : VALIDE
    cout << "on test la fonction de calcul du score de retard" << endl;
    calculer_score_retard(45, 20, 19, 0, 30, 1, 5);
    calculer_score_retard(45, 25, 19, 0, 30, 1, 5);
    calculer_score_retard(45, 30, 19, 0, 30, 1, 5);
    calculer_score_retard(45, 40, 19, 0, 30, 1, 5);
    calculer_score_retard(45, 44, 19, 0, 30, 1, 5);
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