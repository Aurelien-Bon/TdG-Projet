#include "Admin.h"
#include <vector>

Admin::Admin(std::string file)
{
    std::ifstream datafeed(file);
    std::string ligne;
    m_connecte=false;
    m_file=file;
    if(!datafeed){
        std::cerr<<"Probleme de connexion"<<std::endl;
    }
    while(std::getline(datafeed,ligne))
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

void Admin::Connection()
{
    int choix=1;
    while(choix==1)
    {
        std::cout << "1. Connection"<<std::endl;
        std::cout << "2. Quitter"<<std::endl;
        std::cout << "Que voulez vous faire: ";
        do{
            std::cin>>choix;                // l'utilisateur fait une saisie d'un trajet
        }while(choix<0 || choix>2);
        if(choix==1)
        {
            std::string id,mdp, ligne;
            std::cout<<"*********Connexion*********\n"<<std::endl;
            std::cout<<"Veuillez saisir votre nom d'utilisateur"<<std::endl;
            std::cin>>id;
            std::cout<<"Veuillez saisir votre mot de passe"<<std::endl;
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
                std::cout <<"Connexion réussie"<<std::endl;
                m_idadmin=id;
                m_mdp=mdp;
                m_connecte=true;
            }
            //for(auto& elem:m_)
        }
    }
}
std::string Admin::getID(){
    return m_idadmin;
}
void Admin::CreerCompte(){
    std::vector<std::string>copie;
    std::string id, mdp,ligne;
    std::cout<<"*********Creer un compte*********\n"<<std::endl;
    std::cout<<"Veuillez saisir votre nom d'utilisateur"<<std::endl;
    std::cin>>id;
    std::cout<<"Veuillez saisir votre mot de passe"<<std::endl;
    std::cin>>mdp;
    std::ifstream ifs{m_file};  // ouverture du flux de lecture
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + m_file );
    while(std::getline(ifs,ligne)){
        copie.push_back(ligne);
    }
    ifs.close();
    std::ofstream datafeed(m_file);

    if(!datafeed){
        std::cerr<<"Probleme d'écriture"<<std::endl;
    }
    else{
        for(int i=0;i<copie.size();i++){
        datafeed << copie[i] << copie[i+1];
        }
        datafeed<<id << " "<< mdp;
    }
    datafeed.close();
}
bool Admin::getConnect()
{
    return m_connecte;
}


