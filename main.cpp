#include <iostream>
#include "Station.h"
#include "windows.h"
void Gotom(int col, int nb)
{
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = nb;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}
int main()
{
    std::cout<<"Ouvrez votre console en plein �cran"<<std::endl;
    system("mode con cols=200 lines=100");
    Station test("data_arcs.txt");
    //Station test("testprojet.txt");
    //test.Flotmin2pts();


    bool quitter=false;
    do
    {
         Gotom(90,4);
        std::cout<<"Menu"<<std::endl;
        Gotom(80,6);
        std::cout << "1. Choisir un trajet"<<std::endl;
          Gotom(80,7);
        std::cout << "2. Choisir un lieu"<<std::endl;
          Gotom(80,8);
        std::cout << "3. Choix d'un chemin entre 2 lieu"<<std::endl;
          Gotom(80,9);
        std::cout << "4. Critere de selection des chemins"<<std::endl;
          Gotom(80,10);
        std::cout << "5. Flow maximum entre 2 point"<<std::endl;
          Gotom(80,11);
        std::cout << "6. Quitter"<<std::endl;
          Gotom(80,12);
        std::cout << "Que voulez-vous faire?: ";
         Gotom(80,13);
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
            test.Trajet2point();
            break;
        case 4:
            test.Critere();
            break;
        case 5:
            test.FordFercuson();
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
