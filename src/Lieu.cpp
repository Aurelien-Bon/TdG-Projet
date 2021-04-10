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
void Lieu::setColor(int color)
{
    m_color=color;
}
void Lieu::setVisite(int nb)
{
    m_visite=nb;
}
int Lieu::getColor()
{
    return m_color;
}
int Lieu::getVisite()
{
    return m_visite;
}
float Lieu::getTemps(){
return m_temps;
}
void Lieu::setTemps(float temps){
    m_temps=temps;
}
void Lieu::setFermeture(std::string ferme)
{
    m_fermer=ferme;
}
std::string Lieu::getFermeture()
{
    return m_fermer;
}
