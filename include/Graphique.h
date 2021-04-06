#ifndef GRAPHIQUE_H_INCLUDED
#define GRAPHIQUE_H_INCLUDED
#include <allegro.h>
#include <png.h>
#include <loadpng.h>
#include <jpgalleg.h>
#include <iostream>
class Graphique
{
private:

public:
    Graphique();
    Graphique(int a);
    ~Graphique();
    BITMAP* charement(std::string chemin);
    void afficher();
};


#endif // GRAPHIQUE_H_INCLUDED
