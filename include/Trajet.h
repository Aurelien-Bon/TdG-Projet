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
    float m_reelTemps;          // le temps correspond au temps avec les critères activés pour tromper l'algo, le temps réel correspond au véritable tmps pour un trajet
    bool m_selec;
    int m_flow;     // sert pour ford fulkerson
    int m_flowMax;
    std::string m_fermeture;
public:
    Trajet(int nbTrajet,std::string nomTrajet, std::string type,int a, int b, std::string fermer);///Constructeur
    ~Trajet();///Destructeur
    float getTemps();//getter de m_temps
    void setTemps(float temps);//setter de m_temps
    int getDebut();//getter de m_A
    int getFin();//getter de m_B
    void afficher();                // principalement des getter et setter, excepté des traduction par exemple V--> piste verte
    std::string getType();//getter de type
    std::string getNomTrajet();//getter de m_nomTrajet
    int getNbTrajet();//setter de m_nomTrajet
    std::string TradType();//methode qui resort le type en entier
    void setReelTemps(float temps);//setter de m_reelTemps
    float getReelTemps();//getter de m_reelTemps
    void setSelec(bool selec);//setter de m_selec
    bool getSelec();//getter de m_selec
    void setFlow(int flow);//setter de m_flow
    void setMaxFlow(int flowMax);//setter de m_flowMax
    int getFlow();//getter de m_flow
    int getMaxFlow();//getter de m_flowMax
    std::string getFermeture();//getter de m_fermeture
    void setFermeture(std::string fermer);//setter de m_fermeture
};


#endif // TRAJET_H_INCLUDED
