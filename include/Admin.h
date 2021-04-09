#ifndef ADMIN_H
#define ADMIN_H
#include <iostream>
#include <fstream>


class Admin
{
    public:
        Admin(std::string file);
         ~Admin();
        std::string getID();
        void CreerCompte();

    protected:

    private:
        std::string m_idadmin;
        std::string m_mdp;
        std::string m_file;
        bool m_connecte;

};

#endif // ADMIN_H
