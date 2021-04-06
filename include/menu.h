#ifndef MENUE_H_INCLUDED
#define MENUE_H_INCLUDED
#include "Station.h"
class Menu
{
private:
    //Graphique m_graphi;
    Station m_station;
public:
    Menu();
    //Menu(Graphique graph);
    ~Menu();
    void selection();
};


#endif // MENUE_H_INCLUDED
