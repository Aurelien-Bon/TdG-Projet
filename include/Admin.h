#ifndef ADMIN_H
#define ADMIN_H
#include <iostream>
#include <fstream>
#include <vector>


class Admin
{
    public:
        Admin(std::string file);///Constructeur prend en parametre le fichier de config
         ~Admin();///destructeur
        void Connexion();//permet de connecter un administrateur
        void Deconnexion();//permet de se deconnecter
        std::string getID();//geter de ID
        void CreerCompte();//ajout compte admin
        bool getConnect();//getter de m_connecte

    protected:

    private:
        std::vector<std::vector<std::string>> m_infoFile;//tout les compte et mot de passe administrateur
        std::string m_mdp;// mdp de la session actuel
        std::string m_file;//nom du fichier contenent les mot de passe et nom admin
        std::string m_idadmin;//nom de la session actuel
        bool m_connecte;// vrai si une session est connecter

};

#endif // ADMIN_H
