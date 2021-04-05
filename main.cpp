#include <iostream>
#include "Station.h"
#include "windows.h"
int main()
{
    Station test("data_arcs.txt");
    //Station test("testprojet.txt");
    bool quitter=false;
    do
    {
        std::cout << "1. Choisir un trajet"<<std::endl;
        std::cout << "2. Choisir un lieu"<<std::endl;
        std::cout << "3. Chemin le plus court entre 2 points"<<std::endl;
        std::cout << "4. Tout les chemins les plus courts a partir d'un point"<<std::endl;
        std::cout << "5. Critere de selection des chemins"<<std::endl;
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
            test.AffichageTrajet();
            break;
        case 2:
            test.AffichagePoint();
            break;
        case 3:
            test.dijkstra();
            break;
        case 4:
            test.bfs();
            break;
        case 5:
            test.Critere();
            break;
        case 6:
            quitter=true;
            system("cls");
            break;
        }
    }while(quitter==false);
    return 0;
    //yo
}
