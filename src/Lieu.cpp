#include "Lieu.h"
#include <iostream>
Lieu::Lieu(std::string nom,float nbLieu,int altitude)  // on set le sommet quand il est crée
{
    m_nom = nom;
    m_nbLieu= nbLieu;
    m_altitude = altitude;

}
Lieu::~Lieu() {}
std::string Lieu::getLieu() // retourne le numéro du sommet
{
    return m_nom;
}
void Lieu::afficher() // méthode d'affichage principale
{
    std::cout << "Lieu: " << m_nom << "\t\t| altitude: "<<m_altitude<< std::endl;
}
int Lieu::getAltitude()  // retourne le poids du précédent
{
    return m_altitude;
}
float Lieu::getNbLieu()
{
    return m_nbLieu;
}
void Lieu::setAltitude(int alt)   // on modifie le poids d'une arete
{
    m_altitude = alt;
}
void Lieu::setColor(int color)//setter de m_color
{
    m_color=color;
}
void Lieu::setVisite(int nb)//setter de m_visite
{
    m_visite=nb;
}
int Lieu::getColor()//getter de m_color
{
    return m_color;
}
int Lieu::getVisite()//getter de m_visite
{
    return m_visite;
}
float Lieu::getTemps(){//getter de m_temps
return m_temps;
}
void Lieu::setTemps(float temps){//setter de m_temps
    m_temps=temps;
}
void Lieu::setFermeture(std::string ferme)//setter de m_ferme
{
    m_fermer=ferme;
}
std::string Lieu::getFermeture()//getter de m_ferme
{
    return m_fermer;
}
