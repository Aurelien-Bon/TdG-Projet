#include "Trajet.h"
#include "windows.h"
void Goto(int col)
{
    COORD mycoord;
    mycoord.X = col;
    //mycoord.Y = getNb();
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}

Trajet::Trajet(int nbTrajet,std::string nomTrajet, std::string type,int a, int b,std::string fermer)
{
    m_nbTrajet = nbTrajet;
    m_nomTrajet = nomTrajet;
    m_type = type;
    m_A = a;
    m_B = b;
    m_fermeture=fermer;
}
Trajet::~Trajet() {}
float Trajet::getTemps()  // retourne le temps d'une arete
{
    return m_temps;
}
void Trajet::setTemps(float temps)
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
std::string Trajet::getType()
{
    return m_type;
}
std::string Trajet::getNomTrajet()
{
    return m_nomTrajet;
}
int Trajet::getNbTrajet()
{
    return m_nbTrajet;
}

std::string Trajet::TradType()
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
void Trajet::setReelTemps(float temps)
{
    m_reelTemps=temps;
}
float Trajet::getReelTemps()
{
    return m_reelTemps;
}
void Trajet::setSelec(bool selec)
{
    m_selec=selec;
}
bool Trajet::getSelec()
{
    return m_selec;
}
void Trajet::setFlow(int flow)
{
    m_flow=flow;
}
void Trajet::setMaxFlow(int flowMax)
{
    m_flowMax=flowMax;
}
int Trajet::getFlow()
{
    return m_flow;
}
int Trajet::getMaxFlow()
{
    return m_flowMax;
}
std::string Trajet::getFermeture()
{
    return m_fermeture;
}
void Trajet::setFermeture(std::string fermer)
{
    m_fermeture=fermer;
}
