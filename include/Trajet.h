#ifndef TRAJET_H_INCLUDED
#define TRAJET_H_INCLUDED
#include <iostream>

class Trajet
{
private:
    int m_nbTrajet;
    std::string m_nomTrajet;
    std::string m_type;
    int m_A;
    int m_B;        // une arete dispose d'un point A et B départ -- > arrivée ainsi qu'un poids assigné à cette arete
    float m_temps;
    float m_reelTemps;
public:
    Trajet(int nbTrajet,std::string nomTrajet, std::string type,int a, int b);
    ~Trajet();
    float getTemps();
    void setTemps(float temps);
    int getDebut();
    int getFin();
    void afficher();
    std::string getType();
    std::string getNomTrajet();
    int getNbTrajet();
    std::string TradType();
    void setReelTemps(float temps);
    float getReelTemps();
};


#endif // TRAJET_H_INCLUDED
