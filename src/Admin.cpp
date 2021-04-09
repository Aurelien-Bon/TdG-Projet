#include "Admin.h"
#include <vector>

Admin::Admin(std::string file)
{
    std::ifstream datafeed(file);
    if(!datafeed){
        std::cerr<<"Probleme de connexion"<<std::endl;
    }
    std::string id,mdp, ligne;
    std::cout<<"*********Connexion*********\n"<<std::endl;
    std::cout<<"Veuillez saisir votre nom d'utilisateur"<<std::endl;
    std::cin>>id;
    std::cout<<"Veuillez saisir votre mot de passe"<<std::endl;
    std::cin>>mdp;
    bool test=false;
    while(std::getline(datafeed,ligne)||test){
        std::string id1, mdp1;
        datafeed>>id1 >> mdp1;
        if(id1==id&&mdp1==mdp)
            test=true;
    }
    if(!test){
        std::cout<<"Erreur dans votre nom d'utilisateur ou mot de passe"<<std::endl;
    }
    else{
        std::cout <<"Connexion réussie"<<std::endl;
        m_idadmin=id;
        m_mdp=mdp;
        m_connecte=true;
        m_file=file;
    }
    datafeed.close();

}

Admin::~Admin()
{
    //dtor
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

