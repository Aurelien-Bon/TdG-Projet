#include <iostream>
#include "Station.h"
#include "windows.h"
#include "Admin.h"
void Gotom(int col, int nb) // fonction gotolicol proposé par Mr Fercoq
{
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = nb;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}
int main()
{
    Admin administrateur("id.txt");
    std::cout<<"Ouvrez votre console en plein écran"<<std::endl;
    system("mode con cols=200 lines=100");
    Station test("data_arcs.txt");
    bool quitter=false;
    do
    {
        system("cls");
        Gotom(0,3);
        std::cout<<"*****************************************";
        for(int i=3;i<17;i++){
            Gotom(0,i);
            std::cout<<"*";
            Gotom(40,i);
            std::cout<<"*";
        }
        Gotom(0,17);
        std::cout<<"*****************************************";
        Gotom(20,4);
        std::cout<<"Menu"<<std::endl;

        Gotom(4,6);
        std::cout << "1. Choisir un trajet"<<std::endl;         // switch proposant les différents choix à l'utilisateur
        Gotom(4,7);

        std::cout << "2. Choisir un lieu"<<std::endl;
        Gotom(4,8);

        std::cout << "3. Choix d'un chemin entre 2 lieux"<<std::endl;

        Gotom(4,9);
        std::cout << "4. Critere de selection des chemins"<<std::endl;

        Gotom(4,10);
        std::cout << "5. Flow maximum entre 2 points"<<std::endl;
        Gotom(4,11);
        std::cout << "6. Information des piste"<<std::endl;
        Gotom(4,12);
        if(administrateur.getConnect()==false)
            std::cout << "7. Connexion administrateur"<<std::endl;
        else
            std::cout << "7. Gestion fermeture des pistes"<<std::endl;
        Gotom(4,13);
        if(administrateur.getConnect()==false)
            std::cout << "8. Quitter"<<std::endl;
        else
            std::cout << "8. Ajouter un compte administrateur"<<std::endl;
        if(administrateur.getConnect()==true)
        {
            Gotom(4,14);
            std::cout << "9. Deconnexion"<<std::endl;
        }
        if(administrateur.getConnect()==true)
        {
            Gotom(4,15);
            std::cout << "10. Quitter"<<std::endl;
        }

        if(administrateur.getConnect()==false)
            Gotom(4,14);
        else
            Gotom(1,16);
        std::cout << "Que voulez-vous faire?: ";
        if(administrateur.getConnect()==false)
            Gotom(28,14);
        else
            Gotom(25,16);
        int choix=0;
        int maxchoix=8;
        if(administrateur.getConnect()==true)
            maxchoix=10;
        do
        {
            std::cin>>choix;
        }while(choix<0 || choix>maxchoix);
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
            test.InfoPiste();
            break;
        case 7:
            if(administrateur.getConnect()==false)
                administrateur.Connexion();
            else
                test.fermeturePiste();
            break;
        case 8:
            if(administrateur.getConnect()==false)
            {
               quitter=true;
                system("cls");
            }
            else
                administrateur.CreerCompte();
            break;
        case 9:
            administrateur.Deconnexion();
            break;
        case 10:
            quitter=true;
            system("cls");
            break;
        }
    }while(quitter==false);
    return 0;
    //yo
}
