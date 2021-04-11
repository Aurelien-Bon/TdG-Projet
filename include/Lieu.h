#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <iostream>
class Lieu
{
private:        // chaque sommet dispose d'un numéro, d'une couleur, visite correspondant au prédécesseur avec le poids de ce dernier
    float m_nbLieu;
    std::string m_nom;
    int m_altitude;
    int m_color;
    int m_visite;
    float m_temps;
    std::string m_fermer;
public:
    Lieu(std::string nom,float nbLieu,int altitude);///Constucteur
    ~Lieu();
    std::string getLieu();//getter m_lieu
    void afficher();//methode d'affichage
    int getAltitude();//getter de m_altitude
    float getNbLieu();//getter de m_nbLieu
    void setAltitude(int alt);//setter de m_altitude
    void setColor(int color);//setter de m_color
    void setVisite(int visite);//setter de m_visite
    void setTemps(float temps);//setter de m_temps
    int getColor();//getter de m_color
    int getVisite();//getter de m_visite
    float getTemps();//getter de m_temps
    void setFermeture(std::string fermer);//setter de m_fermer
    std::string getFermeture();//getter de m_fermer
};


#endif // SOMMET_H_INCLUDED
