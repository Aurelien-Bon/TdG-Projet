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
        std::string getID();//getter de ID
        void CreerCompte();//ajout compte admin
        bool getConnect();//getter de m_connecte

    protected:

    private:
        std::vector<std::vector<std::string>> m_infoFile;//tous les comptes et mot de passe administrateur
        std::string m_mdp;// mdp de la session actuelle
        std::string m_file;//nom du fichier contenant les mots de passes et nom admin
        std::string m_idadmin;//nom de la session actuelle
        bool m_connecte;// vrai si une session est connectee

};

#endif // ADMIN_H
