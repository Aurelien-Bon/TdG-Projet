#ifndef STATION_H_INCLUDED
#define STATION_H_INCLUDED
#include "Trajet.h"
#include "Lieu.h"
#include <iostream>
#include <vector>
class Station
{
private:
    int m_nbLieu;
    int m_nbTrajet;
    std::vector<Lieu> m_lieu;
    std::vector<Trajet> m_trajet;
    std::vector<int> m_coef;
    std::string m_mode;
    std::string m_filename;

public:
    Station(std::string filename);
    ~Station();
    void afficher();
    float CalculTempsCoef(Trajet traj);
    void AffichagePoint();
    void AffichageTrajet();
    void dijkstra(int debut, int fin);
    bool bfs(int debut,int fin);
    float CalculTemps(Trajet traj);
    void Critere();
    void reecritureFicher();
    std::string affichageTemps(float temps);
    void Trajet2point();
    void SelectionTrajet();
};


#endif // STATION_H_INCLUDED
