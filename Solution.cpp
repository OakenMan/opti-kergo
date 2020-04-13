#include "Solution.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <set>

Solution::Solution()
{
    i_valeur_fonction_objectif=0;
}
Solution::~Solution()
{
   v_Id_Hotel_Intermedaire.clear();
   v_v_Sequence_Id_Par_Jour.clear();
   v_Date_Depart.clear();
}

bool Solution::Verification_Solution(Instance *instance)
{
    bool b_solution_ok=true;
    unsigned int i,j,i_score;
    float f_date;
    set<unsigned int> set_POIs_Visites;
    i_score=0;
    //Vérification des Ids Hôtel et la taille du tableau associé
    if(v_Id_Hotel_Intermedaire.size()!=(instance->get_Nombre_Jour()-1))
    {
        cout<< "Erreur : Nombre d'hôtels de v_Id_Hotel_Intermedaire. " <<endl;
        b_solution_ok=false;
    }
    for(i=0;i<v_Id_Hotel_Intermedaire.size();i++)
    {
        if((v_Id_Hotel_Intermedaire[i]<0)||(v_Id_Hotel_Intermedaire[i]>=instance->get_Nombre_Hotel()))
        {
            cout<< "Erreur : Id hôtel dans v_Id_Hotel_Intermedaire ("<<i<<") : "<< v_Id_Hotel_Intermedaire[i]<<"." <<endl;
            b_solution_ok=false;
        }
    }
    //Vérification des Ids POIs (et unicité) et la taille du tableau associé
    if(v_v_Sequence_Id_Par_Jour.size()!=(instance->get_Nombre_Jour()))
    {
        cout<< "Erreur : La taille de la première dimension de v_v_Sequence_Id_Par_Jour doit être égale au nombre de jour. " <<endl;
        b_solution_ok=false;
    }
    for(i=0;i<v_v_Sequence_Id_Par_Jour.size();i++)
    {
        for(j=0;j<v_v_Sequence_Id_Par_Jour[i].size();j++)
        {
            if((v_v_Sequence_Id_Par_Jour[i][j]<0)||(v_v_Sequence_Id_Par_Jour[i][j]>=instance->get_Nombre_POI()))
            {
                cout<< "Erreur : Id POI dans v_v_Sequence_Id_Par_Jour ("<<i<<","<<j<<") : "<< v_v_Sequence_Id_Par_Jour[i][j]<<"." <<endl;
                b_solution_ok=false;
            }
            else
            {
                if(set_POIs_Visites.find(v_v_Sequence_Id_Par_Jour[i][j])==set_POIs_Visites.end())
                {
                    set_POIs_Visites.insert(v_v_Sequence_Id_Par_Jour[i][j]);
                    i_score=i_score+instance->get_POI_Score(v_v_Sequence_Id_Par_Jour[i][j]);
                }
                else
                {
                    cout<< "Erreur : le POI "<<v_v_Sequence_Id_Par_Jour[i][j]<<" est visité plsuieurs fois dans la solution. " <<endl;
                    b_solution_ok=false;
                }
            }
        }
    }
    //Vérification des dates de départs et la taille du tableau associé
    if(v_Date_Depart.size()!=(instance->get_Nombre_Jour()))
    {
        cout<< "Erreur : Nombre de date de départ de v_Date_Depart. " <<endl;
        b_solution_ok=false;
    }
    for(i=0;i<v_Date_Depart.size();i++)
    {
        if((v_Date_Depart[i]<0)||(v_Date_Depart[i]>=100000))
        {
            cout<< "Erreur : date de départ dans v_Date_Depart ("<<i<<") : "<< v_Date_Depart[i]<<"." <<endl;
            b_solution_ok=false;
        }
    }
    //Vérification du respect des fenêtres de temps des POIs et  des durées maximales d'une journée
    for(i=0;i<v_v_Sequence_Id_Par_Jour.size();i++)
    {
        if(v_v_Sequence_Id_Par_Jour[i].size()!=0)
        {
            f_date=v_Date_Depart[i];
            if(i==0)
                f_date=f_date+instance->get_distance_Hotel_POI(instance->get_Id_Hotel_depart(), v_v_Sequence_Id_Par_Jour[i][0]);
            else
                f_date=f_date+instance->get_distance_Hotel_POI(v_Id_Hotel_Intermedaire[i-1], v_v_Sequence_Id_Par_Jour[i][0]);
            j=0;
            do
            {
                if(f_date<instance->get_POI_Heure_ouverture(v_v_Sequence_Id_Par_Jour[i][j]))
                    f_date=instance->get_POI_Heure_ouverture(v_v_Sequence_Id_Par_Jour[i][j]);
                else
                {
                    if(f_date>instance->get_POI_Heure_fermeture(v_v_Sequence_Id_Par_Jour[i][j]))
                    {
                        cout<< "Erreur : arrivé après la fermeture du POI "<<v_v_Sequence_Id_Par_Jour[i][j]<<", heure : "<< f_date<<"." <<endl;
                        b_solution_ok=false;
                    }
                }
                j++;
                if(j<v_v_Sequence_Id_Par_Jour[i].size())
                {
                    f_date=f_date+instance->get_distance_POI_POI(v_v_Sequence_Id_Par_Jour[i][j-1], v_v_Sequence_Id_Par_Jour[i][j]);
                }
            }while(j<v_v_Sequence_Id_Par_Jour[i].size());
            if(i==(v_v_Sequence_Id_Par_Jour.size()-1))
                f_date=f_date+instance->get_distance_Hotel_POI(instance->get_Id_Hotel_Arrivee(), v_v_Sequence_Id_Par_Jour[i][j-1]);
            else
                f_date=f_date+instance->get_distance_Hotel_POI(v_Id_Hotel_Intermedaire[i], v_v_Sequence_Id_Par_Jour[i][j-1]);
            if((f_date-v_Date_Depart[i])>instance->get_POI_Duree_Max_Voyage(i))
            {
                cout<< "Erreur : durée max du jour "<<i<<" dépassée puisqu'elle dure : "<< (f_date-v_Date_Depart[i])<<"." <<endl;
                b_solution_ok=false;
            }
        }
        else
        {
            int i_ID_depart,i_ID_Arrivee;
            f_date=v_Date_Depart[i];
            if(instance->get_Nombre_Jour()>1)
            {
                if(i==0)
                    i_ID_depart=instance->get_Id_Hotel_depart();
                else
                    i_ID_depart=v_Id_Hotel_Intermedaire[i-1];

                if((instance->get_Nombre_Jour()-1)==i)
                    i_ID_Arrivee=instance->get_Id_Hotel_Arrivee();
                else
                    i_ID_Arrivee=v_Id_Hotel_Intermedaire[i];
            }
            else
            {
                i_ID_depart=instance->get_Id_Hotel_depart();
                i_ID_Arrivee=instance->get_Id_Hotel_Arrivee();
            }

            f_date=f_date+instance->get_distance_Hotel_Hotel(i_ID_depart, i_ID_Arrivee);
            if((f_date-v_Date_Depart[i])>instance->get_POI_Duree_Max_Voyage(i))
            {
                cout<< "Erreur : durée max du jour "<<i<<" dépassée puisqu'elle dure : "<< (f_date-v_Date_Depart[i])<<"." <<endl;
                b_solution_ok=false;
            }
        }
    }
    //Vérification de la fonction objectif
    if(i_score!=i_valeur_fonction_objectif)
    {
        cout<< "Erreur : la fonction objectif est mal calculée, cela devrait être : "<< i_score<<"." <<endl;
        b_solution_ok=false;
    }

    return b_solution_ok;
}

void display(vector<unsigned int> &v) {
   cout << "[ ";
   for(unsigned int i=0; i<v.size(); i++) {
      cout << v[i] << " ";
   }
   cout << "] (n=" << v.size() << ")" << endl;
}

void display(vector<float> &v) {
   cout << fixed << setprecision(2);
   cout << "[ ";
   for(unsigned int i=0; i<v.size(); i++) {
      cout << v[i] << " ";
   }
   cout << "]" << endl;
}

void Solution::print() {
   cout << "---------- Solution ----------" << endl;
   cout << "Hôtels intermédiaires : ";
   display(v_Id_Hotel_Intermedaire);
   cout << "Séquences de POI par jour : " << endl;
   for(unsigned int i=0; i<v_v_Sequence_Id_Par_Jour.size(); i++) {
      cout << i << " : ";
      display(v_v_Sequence_Id_Par_Jour[i]);
   }
   cout << "Heure de départ chaque jour : ";
   display(v_Date_Depart);
   //cout << "SCORE = " << i_valeur_fonction_objectif << endl;
}

Solution * generateSolution(Instance *instance) {
   Solution *sol = new Solution();

   // Génération de "v_Id_Hotel_Intermedaire"
   for(unsigned int i=0; i<instance->get_Nombre_Jour()-1; i++) {
      unsigned int idHotel = rand() % instance->get_Nombre_Hotel();     // génère un id entre 0 et nbHotels-1
      sol->v_Id_Hotel_Intermedaire.push_back(idHotel);
   }

   // Génération de "v_v_Sequence_Id_Par_Jour" et "v_Date_Depart"
   for(unsigned int i=0; i<instance->get_Nombre_Jour(); i++) {
      float dateMax = 24.0;   // TODO : récupérer ce nombre depuis l'instance, puis soustraire la durée max de voyage par jour
      float dateDepart = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/dateMax));  // génère un float entre 0.0 et dateMax
      sol->v_Date_Depart.push_back(dateDepart);

      vector<unsigned int> poiList;
      unsigned int nbPOIthisDay = 5 + rand() % (instance->get_Nombre_POI() / (instance->get_Nombre_Jour() * 3));    // génère un nombre entre 0 et nbPOI/(nbJours*3)-1

      for(unsigned int j=0; j<nbPOIthisDay; j++) {
         bool success = false;
         while(!success) {
            bool found = false;
            unsigned int newPOI = rand() % instance->get_Nombre_POI();

            // Regarde si newPOI est déjà dans les jours précédents
            for(unsigned int k=0; k<sol->v_v_Sequence_Id_Par_Jour.size(); k++) {
               if(contains(sol->v_v_Sequence_Id_Par_Jour[k], newPOI)) {
                  found = true;
               }
            }
            // Et dans le jour actuel
            if(contains(poiList, newPOI)) {
               found = true;
            }
            if(!found) {
               poiList.push_back(newPOI);
               success = true;
            }
         }
      }

      sol->v_v_Sequence_Id_Par_Jour.push_back(poiList);
   }

   return sol;
}
