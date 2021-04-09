#ifndef STATION_H_INCLUDED
#define STATION_H_INCLUDED
#include "Trajet.h"
#include "Lieu.h"
#include <iostream>
#include <vector>
#include <windows.h>
#include "Admin.h"

class Station
{
private:
    int m_nbLieu;
    int m_nbTrajet;
    std::vector<Lieu> m_lieu;       // Station correspond à la classe graphe
    std::vector<Trajet> m_trajet;   // comporte un vecteur respectivement pour les lieux et les trajets existants
    std::vector<int> m_coef;    // used pour les critères de choix pour le skieur
    std::string m_mode;
    std::string m_filename;     // nom du fichier, data

public:
    Station(std::string filename);
    ~Station();
    void afficher();    // méthode d'affichage
    float CalculTempsCoef(Trajet traj);     // Permet de nous calculer le temps avec les coeff
    int CalculFlow(Trajet traj);    // Permet de calculer un flow à partir d'un trajet
    void AffichagePoint();  // nous permet de nous afficher les infos d'un lieu
    void AffichageTrajet(); // pareil pour un trajet
    void dijkstra(int debut, int fin);
    bool bfs(int debut,int fin);
    float CalculTemps(Trajet traj); // Permet de calculer le temps réel
    void Critere(); // permet l'utilisateur de personnaliser son xp sur l'appli
    void Personnaliser();
    void reecritureFicher();    // réécrit les nouvelles infos dans le file
    std::string affichageTemps(float temps);    // une trad pour le temps
    void Trajet2point();       // chemin le plus court avec des lieux en prenant compte des critères
    void SelectionTrajet(); // Utilisation pour les extensions
    void FordFercuson();
    void fermeturePiste();
};


#endif // STATION_H_INCLUDED
