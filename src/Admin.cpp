#include "Admin.h"
#include <vector>
#include <windows.h>

Admin::Admin(std::string file)
{
    std::ifstream datafeed(file);
    std::string ligne;
    m_connecte=false;
    m_file=file;
    if(!datafeed){
        std::cerr<<"Probleme de connexion"<<std::endl;
    }
    while (!datafeed.eof())
    {
        std::string id1, mdp1;
        datafeed >>id1 >> mdp1;
        std::vector<std::string> n;
        n.push_back(id1);
        n.push_back(mdp1);
        m_infoFile.push_back(n);
    }
    datafeed.close();
}

Admin::~Admin()
{
    //dtor
}
void Gotox(int col, int nb) // fonction gotolicol proposé par Mr Fercoq
{
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = nb;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}
void Admin::Connexion()
{
    system("cls");
    int choix=1;
    while(choix==1&&m_connecte==false)
    {
        Gotox(0,3);
        std::cout<<"*****************************************";
        for(int i=3;i<20;i++){
            Gotox(0,i);
            std::cout<<"*";
            Gotox(40,i);
            std::cout<<"*";
        }
        Gotox(0,20);
        std::cout<<"*****************************************";
        Gotox(4,4);
        std::cout << "1. Connexion"<<std::endl;
        Gotox(4,5);
        std::cout << "2. Quitter"<<std::endl;
        Gotox(4,6);
        std::cout << "Que voulez vous faire: ";
        Gotox(30,6);
        do{
            std::cin>>choix;                // l'utilisateur fait une saisie d'un trajet
        }while(choix<0 || choix>2);
        if(choix==1)
        {
            std::string id,mdp, ligne;
            std::cout<<std::endl;
            std::cout<<"\t*******Connexion*********\n"<<std::endl;
            std::cout<<"\tNom d'utilisateur: ";
            std::cin>>id;
            std::cout<<std::endl;
            std::cout<<"\tMot de passe:";
            std::cin>>mdp;
            bool test=false;
            for(auto& elem:m_infoFile)
            {
                if(elem[0]==id&&elem[1]==mdp)
                {
                    test=true;
                }
            }
            if(!test){
                std::cout<<"Erreur dans votre nom d'utilisateur ou mot de passe"<<std::endl;
            }
            else{
                std::cout <<"Connexion reussie"<<std::endl;
                m_idadmin=id;
                m_mdp=mdp;
                m_connecte=true;
            }
        }
    }
}
void Admin::Deconnexion()
{
    system("cls");
    int choix;
    std::cout << "Voulez vous vraiment vous deconnecter? "<<std::endl;
    std::cout << "1. Oui"<<std::endl;
    std::cout << "2. Non"<<std::endl;
    do{
        std::cin>>choix;                // l'utilisateur fait une saisie d'un trajet
    }while(choix<0 || choix>2);
    if(choix==1)
    {
        m_idadmin="";
        m_mdp="";
        m_connecte=false;
    }
}
std::string Admin::getID()
{
    return m_idadmin;
}
void Admin::CreerCompte()
{
    system("cls");
    std::vector<std::string>newCompte;
    std::string id, mdp,ligne;
    std::cout<<"*********Creer un compte*********\n"<<std::endl;
    std::cout<<"Veuillez saisir votre nom d'utilisateur"<<std::endl;
    std::cin>>id;
    std::cout<<"Veuillez saisir votre mot de passe"<<std::endl;
    std::cin>>mdp;
    newCompte.push_back(id);
    newCompte.push_back(mdp);
    m_infoFile.push_back(newCompte);
    std::ofstream datafeed(m_file);
    if(!datafeed){
        std::cerr<<"Probleme d'ecriture"<<std::endl;
    }
    else{
        for(auto& elem:m_infoFile)
        {
            datafeed << elem[0]<<" "<< elem[1];
            datafeed << std::endl;
        }
    }
    std::cout<<"Compte crée!"<<std::endl;
}
bool Admin::getConnect()
{
    return m_connecte;
}


