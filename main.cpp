#include <iostream>
#include "Station.h"
#include "windows.h"
void Gotom(int col, int nb) // fonction gotolicol propos� par Mr Fercoq
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
    //HANDLE console;                                 //couleur console
    //console = GetStdHandle(STD_OUTPUT_HANDLE);

    //SetConsoleTextAttribute(console,31);
   //system("Color 3F");
    bool quitter=false;
    do
    {
        system("cls");
        Gotom(20,4);
        std::cout<<"Menu"<<std::endl;
        Gotom(1,6);
        std::cout << "1. Choisir un trajet"<<std::endl;         // switch proposant les diff�rents choix � l'utilisateur
        Gotom(1,7);

        std::cout << "2. Choisir un lieu"<<std::endl;
        Gotom(1,8);

        std::cout << "3. Choix d'un chemin entre 2 lieu"<<std::endl;

        Gotom(1,9);
        std::cout << "4. Critere de selection des chemins"<<std::endl;

        Gotom(1,10);
        std::cout << "5. Flow maximum entre 2 point"<<std::endl;
        Gotom(1,11);
        std::cout << "6. Modification des ouverture des piste"<<std::endl;
        Gotom(1,12);
        std::cout << "7. Quitter"<<std::endl;
        Gotom(1,13);
        std::cout << "Que voulez-vous faire?: ";
         Gotom(25,13);
        int choix=0;
        do
        {
            std::cin>>choix;
        }while(choix<0 || choix>7);
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
            test.fermeturePiste();
            break;
        case 7:
            quitter=true;
            system("cls");
            break;
        }
    }while(quitter==false);
    return 0;
    //yo
}
