#ifndef ADMIN_H
#define ADMIN_H
#include <iostream>
#include <fstream>
#include <vector>


class Admin
{
    public:
        Admin(std::string file);
         ~Admin();
        void Connection();
        std::string getID();
        void CreerCompte();
        bool getConnect();

    protected:

    private:
        std::vector<std::vector<std::string>> m_infoFile;
        std::string m_mdp;
        std::string m_file;
        std::string m_idadmin;
        bool m_connecte;

};

#endif // ADMIN_H
