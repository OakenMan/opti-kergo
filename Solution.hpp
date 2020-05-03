#ifndef Solution_hpp
#define Solution_hpp

#include "Instance.hpp"
#include "vector_methods.hpp"
#include <stdio.h>
#include <vector>

using namespace std;

/* [!]
 * Du fait de notre choix de travailler avec des solutions non-réalisables, nous avons du rajouter un attribut (i_valeur_score_negatif) et
 * deux méthodes (Evaluation_Solution et calculer_score_retard) à la classe Solution. Ces changements n'ont aucun impact sur la méthode "Verification_Solution",
 * qui n'as pas été modifiée.
 */

class Solution
{
    public:// /!\ Normalement pour coder "proprement" il faudrait mettre ces attributs en privée et passer par des fonctions setters/getters pour les modifier. Cependant, dans une méthode de résolution, les opérations sur les solutions (ajout d'id POI, supression d'ID, etc.) sont très très nombreuses, passer par des setters/getters (qui en plus vérifie certaines opérations) est très coûteux en temps de calcul. En optimisation, on évite et manipule directement les solutions (autres méthodes, passer par les inline mais ça reste lourd).
        vector<unsigned int> v_Id_Hotel_Intermedaire;            // Donne l'Id des hôtels entre deux jours (ne considère pas l'hôtel départ et d'arrivé). La taille du tableau est égale au nombre de jours - 1.
        vector<vector<unsigned int>> v_v_Sequence_Id_Par_Jour;   // Donne la séquence d'Id des POIs visités par jour (v_v_Sequence_Id_Par_Jour[d] : séquence de d'Id des POIs visités le jour d). La taille de la première dimension du tableau est égale au nombre de jours.
        vector<float> v_Date_Depart;                             // Donne la date/heure de départ de l'hôtel de chaque jour. La taille du tableau est égale au nombre de jours.

        unsigned int i_valeur_fonction_objectif;                 // Valeur de la fonction objectif (somme des scores des POIs visités)
        unsigned int i_valeur_score_negatif;                     // Valeur du score "d'infaisabilite", utilisée pour affiner la séléction

    public:
    /* Constructeurs et destructeur  */
        Solution();
        virtual ~Solution();

    bool Verification_Solution(Instance *instance);

    /*
     * Calcule la fonction objectif et le score négatif d'une solution
     */
    void Evaluation_Solution(Instance * instance);

    /*
     * Affiche une solution
     */
    void print();
};

unsigned int calculer_score_retard(int heure_totale, float duree_actuelle_trajet, float heure_limite, int fromA, int fromB, int toa, int tob);

#endif
