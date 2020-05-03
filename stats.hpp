#ifndef stats_hpp
#define stats_hpp

#include "Solution.hpp"

#include <iostream>

using namespace std;

/*
 *  Méthodes de debug, utilisées pour afficher des statistiques sur les populations
 */

const bool DEBUG = false;

// Renvoie le meilleur score d'une population, en prenant uniquement en compte les solutions réalisables si onlyFeasible = true
unsigned int getBestScore(vector<Solution*> population, bool onlyFeasible);

// Renvoie la meilleure solution réalisable d'une population
Solution * getBestSolution(vector<Solution*> population);

// Renvoie le meilleur ratio (fonction objectif/score négatif) d'une population
float bestRatio(vector<Solution*> population);

// Renvoie le score moyen d'une population
float averageScore(vector<Solution*> population, bool onlyFeasible);

// Renvoie le ratio moyen d'une population
float averateRatio(vector<Solution*> population);

// Renvoie la "diversité" (solutions non-réalisables | solutions réalisables) d'une population
vector<unsigned int> diversity(vector<Solution*> population);

// Affiche un récapitulatif d'une population
void analyse(vector<Solution*> population);

// Réacapitulatif en une seule ligne
void analyseOneLine(vector<Solution*> population);

#endif
