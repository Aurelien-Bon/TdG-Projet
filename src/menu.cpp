#include <iostream>
#include "menu.h"
//Menu::Menu(){}
Menu::Menu()
{
//    m_graphi=graph;
    Station lesArc("data_arcs.txt");
    m_station=lesArc;
}
Menu::~Menu(){}
void Menu::selection()
{
    bool quitter=false;
    do
    {
        std::cout << "1. Choisir un trajet"<<std::endl;
        std::cout << "2. Choisir un lieu"<<std::endl;
        std::cout << "3. Choix d'un chemin entre 2 lieu"<<std::endl;
        std::cout << "4. Critere de selection des chemins"<<std::endl;
        std::cout << "5. Flow maximum entre 2 point"<<std::endl;
        std::cout << "6. Quitter"<<std::endl;
        std::cout << "Que voulez-vous faire?: ";
        int choix=0;
        do
        {
            std::cin>>choix;
        }while(choix<0 || choix>6);
        switch(choix)
        {
        case 1:
            m_station.AffichageTrajet();
            break;
        case 2:
            m_station.AffichagePoint();
            break;
        case 3:
            m_station.Trajet2point();
            break;
        case 4:
            m_station.Critere();
            break;
        case 5:
            m_station.FordFercuson();
            break;
        case 6:
            quitter=true;
            //system("cls");
            break;
        }
    }while(quitter==false);
}
