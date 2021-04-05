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
public:
    Lieu(std::string nom,float nbLieu,int altitude);
    ~Lieu();
    std::string getLieu();
    void afficher();
    int getAltitude();
    float getNbLieu();
    void setAltitude(int alt);
    void setColor(int color);
    void setVisite(int visite);
    void setTemps(float temps);
    int getColor();
    int getVisite();
    float getTemps();
};


#endif // SOMMET_H_INCLUDED
