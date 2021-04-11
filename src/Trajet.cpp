#include "Trajet.h"
#include "windows.h"

Trajet::Trajet(int nbTrajet,std::string nomTrajet, std::string type,int a, int b,std::string fermer)///Constructeur
{
    m_nbTrajet = nbTrajet;
    m_nomTrajet = nomTrajet;
    m_type = type;
    m_A = a;
    m_B = b;
    m_fermeture=fermer;
}
Trajet::~Trajet() {}///Destructeur
float Trajet::getTemps()  // retourne le temps d'une arete
{
    return m_temps;
}
void Trajet::setTemps(float temps)//setter de m_temps
{
    m_temps = temps;
}
int Trajet::getDebut()  // retourne le pt de départ
{
    return m_A;
}
int Trajet::getFin()    // retourne lept d'arrivée
{
    return m_B;
}
void Trajet::afficher() // affiche départ -- > arrivée et son poids
{
    std::cout << "Nom: "<<m_nomTrajet;
    //Goto(20);
    std::cout <<"\t\t| Type: "<<m_type;
    //Goto(40);
    std::cout <<"\t\t| Lieu de depart: "<<m_A;
    //Goto(60);
    std::cout << "\t\t| Lieu d'arrivee: " << m_B;
    //Goto(80);
    std::cout << "\t| Duree: " << m_temps << " minutes" << std::endl;
}
std::string Trajet::getType()//getter de m_type
{
    return m_type;
}
std::string Trajet::getNomTrajet()//getter de m_nomTrajet
{
    return m_nomTrajet;
}
int Trajet::getNbTrajet()//getter de m_nbTrajet
{
    return m_nbTrajet;
}

std::string Trajet::TradType()//Methode d'affichage par rapport au type
{
    std::string ecrit="";
    if(m_type=="V")
    {
        ecrit="une piste verte";
    }
    if(m_type=="B")
    {
       ecrit="une piste bleue";
    }
    if(m_type=="R")
    {
           ecrit="une piste rouge";
    }
    if(m_type=="N")
    {
          ecrit="une piste noire";
    }
    if(m_type=="KL")
    {
           ecrit="une piste de kilometre lance";
    }
    if(m_type=="SURF")
    {
          ecrit="un snowpark";
    }
    if(m_type=="TPH")
    {
          ecrit="un telepherique";
    }
    if(m_type=="TC")
    {
           ecrit="un telecabine";
    }
    if(m_type=="TSD")
    {
           ecrit="telesiege debrayable";
    }
    if(m_type=="TS")
    {
          ecrit="un telesiege";
    }
    if(m_type=="TK")
    {
           ecrit="un teleski";
    }
    if(m_type=="BUS")
    {
       ecrit="une navette";
    }
    return ecrit;
}
void Trajet::setReelTemps(float temps)//setter de m_reelTemps
{
    m_reelTemps=temps;
}
float Trajet::getReelTemps()//getter de m_reelTemps
{
    return m_reelTemps;
}
void Trajet::setSelec(bool selec)//setter de m_selec
{
    m_selec=selec;
}
bool Trajet::getSelec()//getter de m_selec
{
    return m_selec;
}
void Trajet::setFlow(int flow)//setter de m_flow
{
    m_flow=flow;
}
void Trajet::setMaxFlow(int flowMax)//setter de m_flowMax
{
    m_flowMax=flowMax;
}
int Trajet::getFlow()//getter de m_flow
{
    return m_flow;
}
int Trajet::getMaxFlow()//getter de m_flowMax
{
    return m_flowMax;
}
std::string Trajet::getFermeture()//getter de m_fermeture
{
    return m_fermeture;
}
void Trajet::setFermeture(std::string fermer)//setter de m_fermeture
{
    m_fermeture=fermer;
}
