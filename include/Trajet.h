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
    int m_B;        // une arete dispose d'un point A et B d�part -- > arriv�e ainsi qu'un poids assign� � cette arete
    float m_temps;
    float m_reelTemps;          // le temps correspond au temps avec les crit�res activ�s pour tromper l'algo, le temps r�el correspond au v�ritable tmps pour un trajet
    bool m_selec;
    int m_flow;     // sert pour ford fulkerson
    int m_flowMax;
public:
    Trajet(int nbTrajet,std::string nomTrajet, std::string type,int a, int b);
    ~Trajet();
    float getTemps();
    void setTemps(float temps);
    int getDebut();
    int getFin();
    void afficher();                // principalement des getter et setter, except� des traduction par exemple V--> piste verte
    std::string getType();
    std::string getNomTrajet();
    int getNbTrajet();
    std::string TradType();
    void setReelTemps(float temps);
    float getReelTemps();
    void setSelec(bool selec);
    bool getSelec();
    void setFlow(int flow);
    void setMaxFlow(int flowMax);
    int getFlow();
    int getMaxFlow();
};


#endif // TRAJET_H_INCLUDED
