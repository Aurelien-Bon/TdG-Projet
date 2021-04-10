#include "Station.h"
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include "chrono"
#include "thread"
#include <windows.h>
#include<conio.h>
class myComparator///geeksforgeeks.org modifier par Aurélien Bon
{
public:
    float operator()(Lieu& a1,Lieu& a2) // receives 2 edges
    {
        if(a1.getTemps()==a2.getTemps())    //if the first egde has the same weight as the second one
            return a1.getNbLieu() > a2.getNbLieu();
        return a1.getTemps() > a2.getTemps();
    }
};
void Goto(int col, int nb)
{
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = nb;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}
void delay(int delay_time){ // Créer un temps d'attente

    std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));
}
void leave()
{   // fonction utilisée pour retourner au menu
    std::cout<<"\n\n\n\n-------------------------------------------------------------------------------------------------------"<<std::endl;
    std::cout <<"\t\t\nAppuyez sur ESC pour revenir au menu"<<std::endl;
    std::cout<<"\n\n\n\n-------------------------------------------------------------------------------------------------------"<<std::endl;
    char key_press;
    int ascii_value;
    while(1)///https://fahad-cprogramming.blogspot.com
    {
        key_press=getch();
        ascii_value=key_press;
        if(ascii_value==27) // For ESC
            break;
    }

}
void CouleurCase(std::string type){
    HANDLE console;                                 //couleur console
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    if(type=="V")
      SetConsoleTextAttribute(console,10);
    if(type=="R")
        SetConsoleTextAttribute(console,12);
    if(type=="B")
        SetConsoleTextAttribute(console,9);
    if(type=="N")
        SetConsoleTextAttribute(console,15);
    if(type=="SURF"||type=="BUS")
        SetConsoleTextAttribute(console,13);
    if(type=="TPH"||type=="TC"||type=="TSD"||type=="TS"||type=="TK")
        SetConsoleTextAttribute(console,2);
    if(type=="KL")
        SetConsoleTextAttribute(console,3);
}
void CouleurReset(){
    HANDLE console;                                 //couleur console
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console,7);
}
Station::Station(std::string filename)
{
    m_filename=filename;
    std::ifstream ifs{filename};  // ouverture du flux de lecture
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + filename );
    ifs >> m_nbLieu;
    for (int i=0; i<m_nbLieu; ++i)
    {
        float nbLieu;
        std::string nomLieu;
        int altitude;
        ifs >> nbLieu >> nomLieu >> altitude;
        Lieu n(nomLieu,nbLieu,altitude);   // on crée le lieu qu 'on push dans notre vec apres la lecture de la ligne
        m_lieu.push_back(n);
    }
    ifs >> m_nbTrajet;    // on associe la taille par rapport aux données
    for(int i=0;i<m_nbTrajet;i++)
    {
        int nbTrajet,a , b;
        std::string nomTrajet,typeTrajet,ferme;
        ifs >>nbTrajet>>nomTrajet>>typeTrajet>> a >> b >> ferme;
        Trajet n(nbTrajet,nomTrajet,typeTrajet,a,b,ferme);    // on crée un trajet à partir des composantes lues dans le fichier
        n.setReelTemps(CalculTemps(n));     // on enregistre les temps de chaque trajet après les avoir calculer
        n.setMaxFlow(CalculFlow(n));        // on attribue une valeur max à notre flow pour pert
        m_trajet.push_back(n);
    }
    for(int i=0;i<12;i++)
    {
        int coef;       // on enregistre les coef des critères pour notre vec (sert pour le faux temps)
        ifs >> coef;
        m_coef.push_back(coef);
    }
    std::string test;
    while(std::getline(ifs,test))   // on récupère la dernière ligne qui correspond au mode de l'utilisateur
    {
        m_mode+=test;
    }
}
Station::~Station()
{

}
float Station::CalculTempsCoef(Trajet traj)     // Fonction utilisée pour faire augmenter le faux temps lors de la sélection d'un critère pour l'utilisateur
{
    float temps=0;
    float altdep=m_lieu[traj.getDebut()-1].getAltitude();
    float altarv=m_lieu[traj.getFin()-1].getAltitude();
    float distance=0;
    if(altdep<altarv){
        distance=altarv-altdep;
    }
    else{
        distance=altdep-altarv;
    }

    if(traj.getType()=="V")
    {
        temps=((distance*5)/100)*m_coef[0];
    }

    if(traj.getType()=="B")
    {
       temps=((distance*4)/100)*m_coef[1];
    }
    if(traj.getType()=="R")
    {
        temps=((distance*3)/100)*m_coef[2];
    }
    if(traj.getType()=="N")
    {
        temps=((distance*2)/100)*m_coef[3];
    }
    if(traj.getType()=="KL")
    {
        temps=((distance*1/6)/100)*m_coef[4];
    }
    if(traj.getType()=="SURF")
    {
        temps=((distance*10)/100)*m_coef[5];
    }
    if(traj.getType()=="TPH")
    {
        temps=(4+((distance*2)/100))*m_coef[6];
    }
    if(traj.getType()=="TC")
    {
        temps=(2+((distance*3)/100))*m_coef[7];
    }
    if(traj.getType()=="TSD")
    {
        temps=(1+((distance*3)/100))*m_coef[8];
    }
    if(traj.getType()=="TS")
    {
        temps=(1+((distance*4)/100))*m_coef[9];
    }
    if(traj.getType()=="TK")
    {
        temps=(1+((distance*4)/100))*m_coef[10];
    }
    if(traj.getType()=="BUS")
    {
        if(traj.getNomTrajet()=="navette1600-1800"||traj.getNomTrajet()=="navette1800-1600")
            temps=30*m_coef[11];
        if(traj.getNomTrajet()=="navette1600-2000"||traj.getNomTrajet()=="navette2000-1600")
            temps=40*m_coef[11];
    }
    return temps;
}
int Station::CalculFlow(Trajet traj)        // on set le flow en fonction du trajet reçu en paramètre
{
    int flow=9999;
    if(traj.getType()=="V")     // les flow pour les pistes ont été attribués après réflexion tandis que les remontées --> énoncé
    {
        flow=3000;
    }
    if(traj.getType()=="B")
    {
       flow=2700;
    }
    if(traj.getType()=="R")
    {
        flow=2100;
    }
    if(traj.getType()=="N")
    {
        flow=1200;
    }
    if(traj.getType()=="KL")
    {
        flow=600;
    }
    if(traj.getType()=="SURF")
    {
        flow=1000;
    }
    if(traj.getType()=="TPH")
    {
        flow=1200;
    }
    if(traj.getType()=="TC")
    {
        flow=2200;
    }
    if(traj.getType()=="TSD")
    {
        flow=2500;
    }
    if(traj.getType()=="TS")
    {
        flow=1800;
    }
    if(traj.getType()=="TK")
    {
        flow=800;
    }
    if(traj.getType()=="BUS")
    {
        flow=300;
    }
    return flow;
}
void Station::afficher()
{
    std::cout<<"Lieu:"<<std::endl;
    for(auto& elem:m_lieu)      // pour chaque lieu et trajet dans nos vecteurs respectifs, on display ça
    {
        elem.afficher();
    }
    std::cout<<"Trajet:"<<std::endl;
    for(auto& elem:m_trajet)
    {
        elem.afficher();
    }
}
void Station::AffichagePoint()
{
    system("cls");                  // On affiche ici tous les lieux du domaine
    Goto(0,3);
        std::cout<<"*************************************************************";
        for(int i=3;i<45;i++){
            Goto(0,i);
            std::cout<<"*";
            Goto(60,i);
            std::cout<<"*";
        }
        Goto(0,45);
        std::cout<<"*************************************************************";
    Goto(4,5);
    int cpt=1;
    std::cout<<"Choisissez un lieu parmi les suivants:"<<std::endl;
    for(auto& elem:m_lieu)
    {
        Goto(4,cpt+6);
        std::cout<<elem.getNbLieu()<<". Lieu: ";
        std::cout<<elem.getLieu()<<" a ";
        std::cout<<elem.getAltitude()<<"m d'altitude"<<std::endl;
        cpt++;
    }
    Goto(48,5);     // on propose à l'utilisateur de s'intéresser à un lieu.
    int choix=0;
    do
    {
        std::cin>>choix;
    }while(choix<0 || choix>m_nbLieu);
    system("cls");
    Goto(1,5);
    std::cout<<"Depuis "<<m_lieu[choix-1].getLieu()<<", vous pouvez prendre: "<<std::endl;  // on écupère tous les trajets qui ont comme pt commun, le pt de départ ou le pt d'arrivé identique à notre lieu sélectionné

    cpt=1;
    for(auto& elem:m_trajet)
    {
        if(elem.getDebut()==choix)
        {
            CouleurCase(elem.getType());
            Goto(1,cpt+6);
            std::cout << "Le trajet numero " << elem.getNbTrajet() << " vers ";
            std::cout << m_trajet[elem.getFin()-1].getNomTrajet()<<" en utilisant ";
            std::cout << elem.TradType()<<" pour une duree de ";
            std::cout << affichageTemps(elem.getReelTemps())<<std::endl;
            cpt++;
            CouleurReset();
        }
    }
    Goto(1,9+cpt);
    std::cout<<"Vous pouvez aller a "<<m_lieu[choix-1].getLieu()<<" en prenant: "<<std::endl;

    for(auto& elem:m_trajet)
    {
        if(elem.getFin()==choix){

            Goto(1,cpt+11);
            CouleurCase(elem.getType());
            std::cout << "Le trajet numero " << elem.getNbTrajet() << " depuis ";
            std::cout << m_trajet[elem.getDebut()-1].getNomTrajet()<<" en utilisant ";
            std::cout << elem.TradType()<<" pour une duree de ";
            std::cout << affichageTemps(elem.getReelTemps())<<std::endl;
            cpt++;
            CouleurReset();
        }
    }


    leave();
}
void Station::AffichageTrajet()
{
    int cpt=5;
    system("cls");          // on affiche chaque trajet existant dans le domaine skiable

    int choix=0;
    Goto(0,3);
        std::cout<<"*************************************************************";
        for(int i=3;i<16;i++){
            Goto(0,i);
            std::cout<<"*";
            Goto(60,i);
            std::cout<<"*";
        }
        Goto(0,16);
        std::cout<<"*************************************************************";
        Goto(5,cpt);
    std::cout <<"Souhaitez-vous regarder un type de trajet precis ?"<<std::endl;
    Goto(5,cpt+1);
    std::cout<<"1.Pistes Vertes"<<std::endl;
    Goto(5,cpt+2);
    std::cout<<"2.Pistes Bleues"<<std::endl;
    Goto(5,cpt+3);
    std::cout<<"3.Pistes Rouges"<<std::endl;
    Goto(5,cpt+4);
    std::cout<<"4.Pistes Noires"<<std::endl;
    Goto(5,cpt+5);
    std::cout<<"5.Pistes Kilometrelance";
    Goto(5,cpt+6);
    std::cout<<"6.SnowPark";
    Goto(5,cpt+7);
    std::cout<<"7.Remontees mecaniques";
    Goto(5,cpt+8);
    std::cout<<"8.Tout voir";
    Goto(5,cpt+9);
    std::cout <<"Choix:";
    std::vector<Trajet>copie;

    do{
        std::cin>>choix;
    }while(choix<1 ||choix >8);
    system("cls");
    int n;
    switch(choix){
    case 1:
        n =1;
        for(auto& elem:m_trajet){
            if(elem.getType()=="V"){
                Goto(4,cpt);
                CouleurCase(elem.getType());
                std::cout <<n<<". ";
                n++;
                std::cout << "Trajet n" << elem.getNbTrajet();
                Goto(40,cpt);
                std::cout << "Depart: "<< m_lieu[elem.getDebut()-1].getLieu();
                Goto(70,cpt);
                std::cout <<"Arrivee "<<m_lieu[elem.getFin()-1].getLieu();
                Goto(110,cpt);
                std::cout <<"via "<< elem.TradType();
                Goto(150,cpt);
                std::cout <<"Temps "<< affichageTemps(elem.getReelTemps());
                std::cout <<"\test actuellement: "<<elem.getFermeture()<<std::endl;
                cpt++;
                copie.push_back(elem);

            }
        }
        break;
    case 2:
        n = 1;
        for(auto& elem:m_trajet){
            if(elem.getType()=="B"){
                Goto(4,cpt);
                CouleurCase(elem.getType());
                std::cout <<n<<". ";
                n++;
                std::cout << "Trajet n" << elem.getNbTrajet();
                Goto(40,cpt);
                std::cout << "Depart: "<< m_lieu[elem.getDebut()-1].getLieu();
                Goto(70,cpt);
                std::cout <<"Arrivee "<<m_lieu[elem.getFin()-1].getLieu();
                Goto(110,cpt);
                std::cout <<"via "<< elem.TradType();
                Goto(150,cpt);
                std::cout <<"Temps "<< affichageTemps(elem.getReelTemps());
                std::cout <<"\test actuellement: "<<elem.getFermeture()<<std::endl;
                cpt++;
                copie.push_back(elem);
            }
        }
        break;
    case 3:
        n = 1;
        for(auto& elem:m_trajet){
            if(elem.getType()=="R"){
                 Goto(4,cpt);
                CouleurCase(elem.getType());
                std::cout <<n<<". ";
                n++;
                std::cout << "Trajet n" << elem.getNbTrajet();
                Goto(40,cpt);
                std::cout << "Depart: "<< m_lieu[elem.getDebut()-1].getLieu();
                Goto(70,cpt);
                std::cout <<"Arrivee "<<m_lieu[elem.getFin()-1].getLieu();
                Goto(110,cpt);
                std::cout <<"via "<< elem.TradType();
                Goto(150,cpt);
                std::cout <<"Temps "<< affichageTemps(elem.getReelTemps());
                std::cout <<"\test actuellement: "<<elem.getFermeture()<<std::endl;
                cpt++;
                copie.push_back(elem);
            }
        }
        break;
    case 4:
        n =1;
        for(auto& elem:m_trajet){
            if(elem.getType()=="N"){
                 Goto(4,cpt);
                CouleurCase(elem.getType());

                std::cout <<n<<". ";
                n++;
                std::cout << "Trajet n" << elem.getNbTrajet();
                Goto(40,cpt);
                std::cout << "Depart: "<< m_lieu[elem.getDebut()-1].getLieu();
                Goto(70,cpt);
                std::cout <<"Arrivee "<<m_lieu[elem.getFin()-1].getLieu();
                Goto(110,cpt);
                std::cout <<"via "<< elem.TradType();
                Goto(150,cpt);
                std::cout <<"Temps "<< affichageTemps(elem.getReelTemps());
                std::cout <<"\test actuellement: "<<elem.getFermeture()<<std::endl;
                cpt++;
                copie.push_back(elem);
            }
        }
        break;
    case 5:
        n =1;
        for(auto& elem:m_trajet){
            if(elem.getType()=="KL"){
                Goto(4,cpt);
                CouleurCase(elem.getType());
                std::cout <<n<<". ";
                n++;
                std::cout << "Trajet n" << elem.getNbTrajet();
                Goto(40,cpt);
                std::cout << "Depart: "<< m_lieu[elem.getDebut()-1].getLieu();
                Goto(70,cpt);
                std::cout <<"Arrivee "<<m_lieu[elem.getFin()-1].getLieu();
                Goto(110,cpt);
                std::cout <<"via "<< elem.TradType();
                Goto(150,cpt);
                std::cout <<"Temps "<< affichageTemps(elem.getReelTemps());
                std::cout <<"\test actuellement: "<<elem.getFermeture()<<std::endl;
                cpt++;
                copie.push_back(elem);
            }
        }
        break;
    case 6:
        n =1;
        for(auto& elem:m_trajet){
            if(elem.getType()=="SURF"){
                 Goto(4,cpt);
                CouleurCase(elem.getType());
                std::cout <<n<<". ";
                n++;
                std::cout << "Trajet n" << elem.getNbTrajet();
                Goto(40,cpt);
                std::cout << "Depart: "<< m_lieu[elem.getDebut()-1].getLieu();
                Goto(70,cpt);
                std::cout <<"Arrivee "<<m_lieu[elem.getFin()-1].getLieu();
                Goto(110,cpt);
                std::cout <<"via "<< elem.TradType();
                Goto(150,cpt);
                std::cout <<"Temps "<< affichageTemps(elem.getReelTemps());
                std::cout <<"\test actuellement: "<<elem.getFermeture()<<std::endl;
                cpt++;
                copie.push_back(elem);
            }
        }
        break;
    case 7:
        n =1;
        for(auto& elem:m_trajet){
            if(elem.getType()=="TPH"||elem.getType()=="TC"||elem.getType()=="TSD"||elem.getType()=="TS"||elem.getType()=="TK"){
                Goto(4,cpt);
                CouleurCase(elem.getType());
                std::cout <<n<<". ";
                n++;
                std::cout << "Trajet n" << elem.getNbTrajet();
                Goto(40,cpt);
                std::cout << "Depart: "<< m_lieu[elem.getDebut()-1].getLieu();
                Goto(70,cpt);
                std::cout <<"Arrivee "<<m_lieu[elem.getFin()-1].getLieu();
                Goto(110,cpt);
                std::cout <<"via "<< elem.TradType();
                Goto(150,cpt);
                std::cout <<"Temps "<< affichageTemps(elem.getReelTemps());
                std::cout <<"\test actuellement: "<<elem.getFermeture()<<std::endl;
                cpt++;
                copie.push_back(elem);
            }

        }
        break;
    case 8:
        n =1;
        for(auto& elem:m_trajet)
        {
            Goto(4,cpt);
            CouleurCase(elem.getType());
            std::cout <<n<<". ";
            n++;
            std::cout << "Trajet n" << elem.getNbTrajet();
            Goto(40,cpt);
            std::cout << "Depart: "<< m_lieu[elem.getDebut()-1].getLieu();
            Goto(70,cpt);
            std::cout <<"Arrivee "<<m_lieu[elem.getFin()-1].getLieu();
            Goto(110,cpt);
            std::cout <<"via "<< elem.TradType();
            Goto(150,cpt);
            std::cout <<"Temps "<< affichageTemps(elem.getReelTemps());
            std::cout <<"\test actuellement: "<<elem.getFermeture()<<std::endl;
            copie.push_back(elem);
            cpt++;
        }
        break;
    }

    Goto(1,0);
    CouleurReset();
    int choixe=0;
    if(!copie.empty())
    {
        std::cout<<"\n\nVeuillez saisir un nombre correspondant au trajet qui vous interesse ";

        bool test=false;
        do{
            std::cin>>choixe;                // l'utilisateur fait une saisie d'un trajet
            for(auto& elem:m_trajet){
                if(elem.getNbTrajet()==copie[choixe-1].getNbTrajet())
                    test=true;
            }
        }while((choixe<0 || choixe>m_nbTrajet)&&!test);
        system("cls");                                                          // on affiche toutes les infos relatives à ce trajet
        Goto(1,5);
        CouleurCase(copie[choixe-1].getType());
        std::cout<<"Vous empruntez le trajet : "<<copie[choixe-1].getNomTrajet();
        std::cout<<" pour aller de "<< m_lieu[copie[choixe-1].getDebut()-1].getLieu();
        std::cout<<" vers "<<m_lieu[copie[choixe-1].getFin()-1].getLieu();
        std::cout<<" en utilisant "<<copie[choixe-1].TradType();
        std::cout<<", vous mettrez " << affichageTemps(copie[choixe-1].getReelTemps());
        std::cout <<" ce chemin est: "<<copie[choixe-1].getFermeture()<<std::endl;
        CouleurReset();
    }
    else
    {
        std::cout << "Il n'y en a pas"<<std::endl;
    }
    leave();
}
void Station::dijkstra(int debut, int fin)
{
    for(auto& elem:m_trajet)
    {
        elem.setTemps(CalculTempsCoef(elem));
    }
    for(auto& elem:m_lieu)    // pour chaque sommetn on considère qu'ils n'ont pas encore été visité, de plus on met leur couleur a blanc et on leur assigne un poids impossible (temps)
    {
        elem.setColor(0);
        elem.setVisite(-1);
        elem.setTemps(9999.99);
    }
    m_lieu[debut-1].setTemps(0.00);    // le sommet de départ à son poids set a 0
    bool graphParcouru=false;   // booléen utilisé comme condition de sortie
    std::priority_queue<Lieu,std::vector<Lieu>,myComparator>listeTraite; // création d'une pq pour la liste des données traitées
    for(auto& elem:m_lieu)
    {
        if(elem.getColor()==0)  // on push si un elem n'a pas encore été traité
        {
            listeTraite.push(elem);
        }
    }
    m_lieu[debut-1].setColor(1);      // on considère le lieu de départ traité
    do
    {
        for(auto& elem:m_lieu)
        {
            if(elem.getColor()==0)      // si l'elem n'a pas été traité on le push dans la pq
            {
                listeTraite.push(elem);
            }
        }
        Lieu a=listeTraite.top();   // on récupère le lieu en haut de la pq
        m_lieu[a.getNbLieu()-1].setColor(1);    // on le traite
        for(auto& elem:m_trajet)  // pour chaque element contenu dans la liste d'arete
        {
            if(elem.getDebut()==a.getNbLieu()&&elem.getFermeture()=="Ouvert")
            {
                if(m_lieu[elem.getFin()-1].getColor()!=1)   // si le sommet récupéré a une couleur différent de 1 (noir)
                {
                    if(m_lieu[elem.getFin()-1].getTemps()>(elem.getTemps()+m_lieu[elem.getDebut()-1].getTemps()))   // si le poids du sommet de fin de l'élément étudié est supérieur à la somme du poids de l'élément étudié et du sommet de départ de l'élément de départ
                    {
                        m_lieu[elem.getFin()-1].setVisite(elem.getDebut()); // ce sommet en question a sa visite set à la meme valeur que le sommmet de départ
                        m_lieu[elem.getFin()-1].setTemps(elem.getTemps()+m_lieu[elem.getDebut()-1].getTemps()); // son poids est modifié de telle manière à avoir la somme du poids de notre élément étudié et de notre élément de départ
                    }
                }
            }
        }
        for(auto& elem:m_lieu)//reactualisation des poids de tout les sommet
        {
            float newTemps=elem.getTemps(); // on recup le time de l'élément étudié
            for(auto& art:m_trajet)     // pour chaque élement récupéré par rapport aux aretes précédentes
            {
                if(art.getFin()==elem.getNbLieu())
                {
                    if(art.getDebut()==elem.getVisite())    // si l'elem correspond à l'élément visité
                    {
                        newTemps=art.getTemps()+m_lieu[art.getDebut()-1].getTemps();    // le new poids est modifié par la somme des deux autres poids
                    }
                }
            }
            elem.setTemps(newTemps);    // on change le poids de l'élément
        }
        graphParcouru=true;
        for(auto& elem:m_lieu)
        {
            if(elem.getColor()!=1)  // si un elem a sa couleur diff de noir
            {
                graphParcouru=false;    // la recherche est pas finie
            }
            ///DEBUG
            //std::cout<<elem.getNbLieu()<<": "<<elem.getVisite()<<" "<<elem.getTemps()<<" "<<elem.getColor()<<" | ";
        }
        while(!listeTraite.empty())
        {
            Lieu n=listeTraite.top();
            //std::cout<<n.getNbLieu()<<": "<<n.getVisite()<<" "<<n.getTemps()<<" "<<n.getColor()<<" | ";
            listeTraite.pop();
        }
        //std::cout<<std::endl;
    }while(!graphParcouru);
    if(m_lieu[fin-1].getVisite()!=-1)
    {
        int anteDij = m_lieu[fin-1].getVisite();//on recupere le predecesseur de chaque sommet
        std::stack<int> reponse;
        if(anteDij!=(-1))//si le sommet a des predecesseur
        {
            reponse.push(m_lieu[fin-1].getNbLieu());
            while(true)
            {
                if(anteDij!=(-1))
                {
                    reponse.push(m_lieu[anteDij-1].getNbLieu());
                    anteDij= m_lieu[anteDij-1].getVisite();//on recupere le predecesseur de chaque sommet
                }
                else break;
            }
        }
        system("cls");
        int cpt=1;
        Goto(1,cpt+5);
        std::cout<<"-----------------------------------------------------------------------------------------------------"<<std::endl;      // Affichage du trajet les plus rapides
        Goto(1,cpt+6);
        std::cout<<"Voici l'itineraire le plus rapide de "<<m_lieu[debut-1].getLieu()<<" jusqu'a "<<m_lieu[fin-1].getLieu()<<" avec le mode "<<m_mode<<" actif:\n "<<std::endl;
        anteDij=reponse.top();
        reponse.pop();
        float totalTemps=0;
        while(!reponse.empty())
        {
            for(auto& elem:m_trajet)
            {
                if(elem.getDebut()==anteDij&&elem.getFin()==reponse.top())
                {
                    Goto(1,cpt+8);
                    CouleurCase(elem.getType());
                    std::cout<<"Vous empruntez le trajet : "<<elem.getNomTrajet();
                    std::cout<<" pour aller de "<< m_lieu[elem.getDebut()-1].getLieu();
                    std::cout<<" vers "<<m_lieu[elem.getFin()-1].getLieu();
                    std::cout<<" en utilisant "<<elem.TradType();
                    std::cout<<", vous mettrez " << affichageTemps(elem.getReelTemps())<<std::endl;
                    totalTemps+=elem.getReelTemps();
                    CouleurReset();
                    cpt++;
                }
            }
            anteDij=reponse.top();
            reponse.pop();
        }
        Goto(1,10+cpt);
        std::cout<< " Pour une duree totale de "<<affichageTemps(totalTemps)<<std::endl;
        Goto(1,11+cpt);
        std::cout<<"---------------------------------------------------------------------------------------------------"<<std::endl;
    }
    else
    {
        std::cout<<"Impossible d'atteindre "<<m_lieu[fin-1].getLieu()<<" depuis "<<m_lieu[debut-1].getLieu()<<", un des acces est fermer "<<std::endl;
    }

}
bool Station::bfs(int debut, int fin)
{
    bool possible;
    std::queue<Lieu> fileTrait;//file pour la traite du BFS
    for(auto& elem:m_lieu)
    {
        elem.setColor(0);//mise a blanc de tout les sommet
        elem.setVisite(-1);//set des predecesseur de tout les sommet comme inexistant
    }
    m_lieu[debut-1].setColor(1);//mise a gris du premier sommet traiter
    fileTrait.push(m_lieu[debut-1]);//ajout du premier sommet traiter a la pile de traite
    while(!fileTrait.empty())//traite de toute la pile
    {
        Lieu trait=fileTrait.front();//copie du sommet a traiter
        for(auto& succ:m_trajet)//lecture de tout ses successeur
        {
            if(succ.getDebut()==trait.getNbLieu()&&succ.getSelec()==true)
                if(m_lieu[succ.getFin()-1].getColor()==0)//on recupere tout les sommet pas encore visiter
                {
                    m_lieu[succ.getFin()-1].setColor(1);//on les passe en gris
                    m_lieu[succ.getFin()-1].setVisite(trait.getNbLieu());//on lui set son predecesseur
                    fileTrait.push(m_lieu[succ.getFin()-1]);//on l'ajoute a la file
                }
        }
        trait.setColor(2);//on met en noir le sommet on l'on a deja visiter tout ses suivant
        fileTrait.pop();//on enleve le sommet traiter de la pile
    }
    if(m_lieu[fin-1].getVisite()==-1)
    {
        possible=false;
    }
    else
    {
        possible=true;
    }
    return possible;
}

float Station::CalculTemps(Trajet traj)
{
    float temps=0;
    float altdep=m_lieu[traj.getDebut()-1].getAltitude();
    float altarv=m_lieu[traj.getFin()-1].getAltitude();
    float distance=0;
    if(altdep<altarv){
        distance=altarv-altdep;
    }
    else{
        distance=altdep-altarv;
    }

    if(traj.getType()=="V")
    {
        temps=((distance*5)/100);
    }

    if(traj.getType()=="B")
    {
       temps=((distance*4)/100);
    }
    if(traj.getType()=="R")
    {
        temps=((distance*3)/100);
    }
    if(traj.getType()=="N")
    {
        temps=((distance*2)/100);
    }
    if(traj.getType()=="KL")
    {
        temps=((distance*1/6)/100);
    }
    if(traj.getType()=="SURF")
    {
        temps=((distance*10)/100);
    }
    if(traj.getType()=="TPH")
    {
        temps=(4+((distance*2)/100));
    }
    if(traj.getType()=="TC")
    {
        temps=(2+((distance*3)/100));
    }
    if(traj.getType()=="TSD")
    {
        temps=(1+((distance*3)/100));
    }
    if(traj.getType()=="TS")
    {
        temps=(1+((distance*4)/100));
    }
    if(traj.getType()=="TK")
    {
        temps=(1+((distance*4)/100));
    }
    if(traj.getType()=="BUS")
    {
        if(traj.getNomTrajet()=="navette1600-1800"||traj.getNomTrajet()=="navette1800-1600")
            temps=30;
        if(traj.getNomTrajet()=="navette1600-2000"||traj.getNomTrajet()=="navette2000-1600")
            temps=40;
    }
    return temps;
}

void Station::Critere()
{
    system("cls");
    Goto(1,5);
    std::cout<< "Mode actuellement selectionne: "<<m_mode<<std::endl;
     Goto(1,7);
    std::cout<< "1. Tres bon skieur (pas de piste verte et un minimum de piste bleu)"<<std::endl;
      Goto(1,8);
    std::cout<< "2. Skieur Moyen (pas de piste noir)"<<std::endl;
      Goto(1,9);
    std::cout<< "3. Sans dechausser (pas de telepherique, de telecabine ou de bus)"<<std::endl;
      Goto(1,10);
    std::cout<< "4. Peur du vide (pas de telesiege)"<<std::endl;
      Goto(1,11);
    std::cout<< "5. Professionel (piste noir et rouge en priorite)"<<std::endl;
      Goto(1,12);
    std::cout<< "6. Visite  (priorite piste noir, rouge , bleu et verte"<<std::endl;
      Goto(1,13);
    std::cout<< "7. Mode personnalise (selectionner vos propres criteres)"<<std::endl;
      Goto(1,14);
    std::cout<< "8. Aucun"<<std::endl;
      Goto(1,15);
    std::cout<< "Quel mode voulez-vous choisir?: "<<std::endl;
      Goto(1,16);
    std::cout<< "/!\\ Pour acceder a certains endroits de la station, vous pourriez etre oblige d'emprunter certains chemins que vous souhaitez eviter /!\\ "<<std::endl;
    Goto(33,15);
    int choix=0;
    do
    {
        std::cin>>choix;
    }while(choix<0 || choix>8);
    if(choix!=7)
    {// L'utilisateur choisit le critère qui lui correspond le plus
        for(auto& elem:m_coef)//reste des coef
        {
            elem=1;
        }
    }
    switch(choix)                                                           // on modif les valeurs de certains coeff, pour faire "bug" notre algorithme pour qu'il évitent de prendre certains trajets en fonction du type
    {
    case 1:
        m_coef[0]=200;
        m_coef[1]=50;
        m_mode="Tres bon skieur";
        break;
    case 2:
        m_coef[3]=200;
        m_mode="Skieur moyen";
        break;
    case 3:
        m_coef[6]=200;
        m_coef[7]=200;
        m_coef[11]=200;
        m_mode="Sans dechausser";
        break;
    case 4:
        m_coef[8]=100;
        m_coef[9]=100;
        m_mode="Peur du vide";
        break;
    case 5:
        m_coef[0]=200;
        m_coef[1]=200;
        m_mode="Professionel";
        break;
    case 6:
        m_coef[6]=200;
        m_coef[7]=200;
        m_coef[8]=100;
        m_coef[9]=100;
        m_coef[10]=200;
        m_coef[11]=200;
        m_mode="Visite";
        break;
    case 7:
        Personnaliser();
        m_mode="Personnalise";
        break;
    case 8:
        m_mode="Defaut";        // rien ne change
        system("cls");
        break;
    }
    system("cls");
    reecritureFicher();     // on réécrit dans le fichier les nouveaux critères avec retour au menu par la suite,
}
void Station::Personnaliser()
{
    int choix;
    do
    {
        std::cout << "Mode personnalise (selectionner vos propres criteres): "<<std::endl;
        CouleurCase("V");
        std::cout << "1. Piste Verte: ";
        if(m_coef[0]==200)
        {
            std::cout<<" OFF "<<std::endl;
        }
        else
        {
           std::cout<<" ON "<<std::endl;
        }
        CouleurCase("B");
        std::cout << "2. Piste Bleue: ";
        if(m_coef[1]==200)
        {
            std::cout<<" OFF "<<std::endl;
        }
        else
        {
           std::cout<<" ON "<<std::endl;
        }
        CouleurCase("R");
        std::cout << "3. Piste Rouge: ";
        if(m_coef[2]==200)
        {
            std::cout<<" OFF "<<std::endl;
        }
        else
        {
           std::cout<<" ON "<<std::endl;
        }
        CouleurCase("N");
        std::cout << "4. Piste Noire: ";
        if(m_coef[3]==200)
        {
            std::cout<<" OFF "<<std::endl;
        }
        else
        {
           std::cout<<" ON "<<std::endl;
        }
        CouleurCase("KL");
        std::cout << "5. Kilometre lance: ";
        if(m_coef[4]==200)
        {
            std::cout<<" OFF "<<std::endl;
        }
        else
        {
           std::cout<<" ON "<<std::endl;
        }
        CouleurCase("SURF");
        std::cout << "6. SnowPark: ";
        if(m_coef[5]==200)
        {
            std::cout<<" OFF "<<std::endl;
        }
        else
        {
           std::cout<<" ON "<<std::endl;
        }
        CouleurCase("TPH");
        std::cout << "7. Telepherique: ";
        if(m_coef[6]==200)
        {
            std::cout<<" OFF "<<std::endl;
        }
        else
        {
           std::cout<<" ON "<<std::endl;
        }
        CouleurCase("TC");
        std::cout << "8. Telecabine: ";
        if(m_coef[7]==200)
        {
            std::cout<<" OFF "<<std::endl;
        }
        else
        {
           std::cout<<" ON "<<std::endl;
        }
        CouleurCase("TSD");
        std::cout << "9. Telesiege Debrayable: ";
        if(m_coef[8]==100)
        {
            std::cout<<" OFF "<<std::endl;
        }
        else
        {
           std::cout<<" ON "<<std::endl;
        }
        CouleurCase("TS");
        std::cout << "10. Telesiege: ";
        if(m_coef[9]==100)
        {
            std::cout<<" OFF "<<std::endl;
        }
        else
        {
           std::cout<<" ON "<<std::endl;
        }
        CouleurCase("TK");
        std::cout << "11. Teleski: ";
        if(m_coef[10]==200)
        {
            std::cout<<" OFF "<<std::endl;
        }
        else
        {
           std::cout<<" ON "<<std::endl;
        }
        CouleurCase("BUS");
        std::cout << "12. Bus: ";
        if(m_coef[11]==200)
        {
            std::cout<<" OFF "<<std::endl;
        }
        else
        {
           std::cout<<" ON "<<std::endl;
        }
        CouleurReset();
        std::cout << "13. quitter"<<std::endl;
        std::cout << "Que voulez vous modifier? "<<std::endl;
        do
        {
            std::cin>>choix;
        }while(choix<0 || choix>13);
        if(choix!=13&&choix!=9&&choix!=10)
        {
            if(m_coef[choix-1]==200)
            {
                m_coef[choix-1]=1;
            }
            else
            {
               m_coef[choix-1]=200;
            }
        }
        if(choix==9||choix==10)
        {
            if(m_coef[choix-1]==100)
            {
                m_coef[choix-1]=1;
            }
            else
            {
               m_coef[choix-1]=100;
            }
        }
        system("cls");
    }while(choix!=13);
}
void Station::reecritureFicher()
{
    std::vector<std::string> fichier;
    std::string line;
    std::string test;
    std::ifstream ifs{m_filename};  // ouverture du flux de lecture
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + m_filename );
    for (int i=0; i<m_nbLieu+2; ++i)     // on lit tout le fichier et on save tt dans un vec
    {
        std::getline(ifs,line);
        fichier.push_back(line);
    }
    for (int i=0; i<m_nbTrajet; ++i)     // on lit tout le fichier et on save tt dans un vec
    {
        std::string nbTrajet,a,b;
        std::string nomTrajet,typeTrajet,fermer;
        ifs >>nbTrajet>>nomTrajet>>typeTrajet>> a >> b >>fermer;
        test=nbTrajet+"\t"+nomTrajet+"\t"+typeTrajet+"\t"+a+"\t"+b+"\t"+m_trajet[i].getFermeture();
        fichier.push_back(test);
    }
    for(auto& elem:m_coef)      // on rajoute les nouveaux coeff dans notre vec
    {
        fichier.push_back(std::to_string(elem));
    }
    fichier.push_back(m_mode);

    std::ofstream ofs{m_filename};  // ouverture du flux d'écriture
    if(!ofs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + m_filename );
    for(auto& elem:fichier)     // on réécrit dans notre file chaque elem de notre vecteur comportant tt les infos
    {
        ofs << elem << std::endl;
    }
}
std::string Station::affichageTemps(float temps)
{
    size_t pos = 0;
    std::string finalhour;
    std::string tempsString=std::to_string(temps);
    std::string delimiter = ".";
    std::string minuteHeur = tempsString.substr(0, tempsString.find(delimiter));
    pos=tempsString.find(delimiter);
    tempsString.erase(0, pos + delimiter.length());
    std::string seconde = tempsString.substr(0,2);
    int hour=0;
    int minute=std::stoi(minuteHeur);
    int seconds=std::stoi(seconde)*60/100;
    while(minute>=60)
    {
        if(minute>=60)
        {
            minute-=60;
            hour++;
        }
    }
    if(hour!=0)
    {
        finalhour=std::to_string(hour)+"h ";
    }
    finalhour+=std::to_string(minute)+"m "+std::to_string(seconds)+"s";
    return finalhour;

}
void Station::Trajet2point()
{
    int cpt=1;
    system("cls");
    Goto(0,3);
    std::cout<<"*************************************************************";
    for(int i=3;i<11;i++){
        Goto(0,i);
        std::cout<<"*";
        Goto(60,i);
        std::cout<<"*";
    }
    Goto(0,11);
    std::cout<<"*************************************************************";
    Goto(1,5+cpt);
    std::cout << "\tQue voulez vous faire ?"<<std::endl;
    std::cout << "\t1. Plus court trajet en nombre d'etape(s)."<<std::endl;
    std::cout << "\t2. Plus court trajet en terme de temps."<<std::endl;
    int choix;
    Goto(35,5+cpt);
    do
    {
        std::cin>>choix;
    }while(choix<0 || choix>2);     // en fonction des cas, l'utilisateur peut décider de prendre un trajet qui ne respecte pas forcément, autrement retour au menu
    system("cls");
    Goto(0,3);
    std::cout<<"*************************************************************";
    for(int i=3;i<45;i++){
        Goto(0,i);
        std::cout<<"*";
        Goto(60,i);
        std::cout<<"*";
    }
    Goto(0,45);
    std::cout<<"*************************************************************";
    if(choix==1)
    {
        Goto(4,5);             // on propose un lieu de départ et un lieu d'arrivée à étudier
        std::cout << "De quel lieu voulez-vous partir?"<<std::endl;
        cpt=1;
        for(auto& elem:m_lieu)  //  Pour chaque elem dans le vecteur, on affiche les elem correspondant à chaque lieu
        {
            Goto(4,cpt+6);
            std::cout<<elem.getNbLieu()<<". Lieu: ";
            std::cout<<elem.getLieu()<<" a ";
            std::cout<<elem.getAltitude()<<"m d'altitude"<<std::endl;
            cpt++;
        }

        int debut=0;
        Goto(40,5);
        do
        {
            std::cin>>debut;
        }while(debut<0 || debut>m_nbLieu);
        system("cls");
        cpt=1;
         Goto(0,3);
        std::cout<<"*************************************************************";
        for(int i=3;i<45;i++){
            Goto(0,i);
            std::cout<<"*";
            Goto(60,i);
            std::cout<<"*";
        }
        Goto(0,45);
        std::cout<<"*************************************************************";

        for(auto& elem:m_lieu)
        {
            Goto(4,cpt+6);
            std::cout<<elem.getNbLieu()<<". Lieu: ";
            std::cout<<elem.getLieu()<<" a ";
            std::cout<<elem.getAltitude()<<"m d'altitude"<<std::endl;
            cpt++;
        }
        Goto(4,5);
        std::cout << "A quel endroit voulez-vous allez? "<<std::endl;
        Goto(40,5);
        int fin=0;
        do
        {
            std::cin>>fin;
        }while(fin<0 || fin>m_nbLieu||fin==debut);
        system("cls");                  // on fait à l'appel pour chercher le trajet à adopter
        SelectionTrajet();
        if(bfs(debut,fin)==false)       // dans le cas ou ce n'est pas possible avec le critère, on propose deux choix
        {
            Goto(1,5+cpt);
            std::cout << "Impossible d'atteindre le point ";
            std::cout << m_lieu[fin-1].getLieu() << " depuis ";
            std::cout << m_lieu[debut-1].getLieu() << " avec le critere "<<m_mode<<"!"<<std::endl;
        }
        else
        {
            std::cout << "Plus court trajet en nombre d'etape(s) pour atteindre ";
            std::cout << m_lieu[fin-1].getLieu() << " depuis ";
            std::cout << m_lieu[debut-1].getLieu() << " avec le critere "<<m_mode<<"!"<<std::endl;
            std::queue<int> resultat;
            int anteBfs = m_lieu[fin-1].getVisite();//on recupere le predecesseur de chaque sommet
            if(anteBfs!=(-1))//si le sommet a des predecesseurs
            {
                resultat.push(m_lieu[fin-1].getNbLieu());
                while(true)
                {
                    if(anteBfs!=(-1))
                    {
                        resultat.push(m_lieu[anteBfs-1].getNbLieu());
                        anteBfs= m_lieu[anteBfs-1].getVisite();//on recupere le predecesseur de chaque sommet
                    }
                    else break;
                }
            }
            int r1;
            r1=resultat.front();
            resultat.pop();
            float tempTotal=0;
            while(!resultat.empty())//on recupere l'arete avec le moins de flow
            {
                std::cout<<std::endl;
                for(auto& elem:m_trajet)
                {
                    if(elem.getFin()==r1&&elem.getDebut()==resultat.front()&&elem.getSelec())
                    {
                        CouleurCase(elem.getType());
                        std::cout<<"Vous empruntez le trajet : "<<elem.getNomTrajet();
                        std::cout<<" pour aller de "<< m_lieu[elem.getDebut()-1].getLieu();
                        std::cout<<" vers "<<m_lieu[elem.getFin()-1].getLieu();
                        std::cout<<" en utilisant "<<elem.TradType();
                        std::cout<<", vous mettrez " << affichageTemps(elem.getReelTemps())<<std::endl;
                        tempTotal+=elem.getReelTemps();
                    }
                }
                r1=resultat.front();
                resultat.pop();
                CouleurReset();
            }
            std::cout << "\nPour une duree totale de "<<affichageTemps(tempTotal);
        }
    }
    else
    {
        Goto(0,3);
        std::cout<<"*************************************************************";
        for(int i=3;i<45;i++){
            Goto(0,i);
            std::cout<<"*";
            Goto(60,i);
            std::cout<<"*";
        }
        Goto(0,45);
        std::cout<<"*************************************************************";
        cpt=1;
        for(auto& elem:m_lieu)  //  Pour chaque elem dans le vecteur, on affiche les elem correspondant à chaque lieu
        {
            Goto(4,cpt+6);
            std::cout<<elem.getNbLieu()<<". Lieu: ";
            std::cout<<elem.getLieu()<<" a ";
            std::cout<<elem.getAltitude()<<"m d'altitude"<<std::endl;
            cpt++;
        }
        Goto(4,5);             // on propose un lieu de départ et un lieu d'arrivée à étudier
        std::cout << "De quel lieu voulez-vous partir?"<<std::endl;
        int debut=0;
        Goto(40,5);
        do
        {
            std::cin>>debut;
        }while(debut<0 || debut>m_nbLieu);
        system("cls");
        cpt=1;
        Goto(0,3);
        std::cout<<"*************************************************************";
        for(int i=3;i<45;i++){
            Goto(0,i);
            std::cout<<"*";
            Goto(60,i);
            std::cout<<"*";
        }
        Goto(0,45);
        std::cout<<"*************************************************************";

        for(auto& elem:m_lieu)
        {
            Goto(4,cpt+6);
            std::cout<<elem.getNbLieu()<<". Lieu: ";
            std::cout<<elem.getLieu()<<" a ";
            std::cout<<elem.getAltitude()<<"m d'altitude"<<std::endl;
            cpt++;
        }
        Goto(4,5);
        std::cout << "A quel endroit voulez-vous allez? "<<std::endl;

        int fin=0;
        Goto(40,5);
        do
        {
            std::cin>>fin;
        }while(fin<0 || fin>m_nbLieu||fin==debut);
        system("cls");                  // on fait à l'appel pour chercher le trajet à adopter
        SelectionTrajet();
        for(auto& elem:m_trajet)
        {
            elem.setTemps(CalculTemps(elem));
        }
        cpt=1;
        if(bfs(debut,fin)==false)       // dans le cas ou ce n'est pas possible avec le critère, on propose deux choix
        {
            Goto(1,5+cpt);
            std::cout << "Impossible d'atteindre le point ";
            std::cout << m_lieu[fin-1].getLieu() << " depuis ";
            std::cout << m_lieu[debut-1].getLieu() << " avec le critere "<<m_mode<<"!"<<std::endl;
            std::cout << "Que voulez vous faire ?"<<std::endl;
            std::cout << "1. Y allez quand meme mais en respectant au maximum mes condition."<<std::endl;
            std::cout << "2. Quitter."<<std::endl;
            int choix;
            do
            {
                std::cin>>choix;
            }while(choix<0 || choix>2);     // en fonction des cas, l'utilisateur peut décider de prendre un trajet qui ne respecte pas forcément, autrement retour au menu
            if(choix==1)
            {
                dijkstra(debut,fin);
            }
        }
        else
        {
            dijkstra(debut,fin);
        }
    }
    leave();
}
void Station::SelectionTrajet()
{
    for(auto& elem:m_trajet)//reset de la selection des aretes
    {
        elem.setSelec(true);
    }
    for(auto& elem:m_trajet)
    {
        if(elem.getType()=="V"&&m_coef[0]==200)
        {
            elem.setSelec(false);
        }
        if(elem.getType()=="B"&&m_coef[1]==200)
        {
            elem.setSelec(false);
        }
        if(elem.getType()=="R"&&m_coef[2]==200)
        {
            elem.setSelec(false);
        }
        if(elem.getType()=="N"&&m_coef[3]==200)
        {
            elem.setSelec(false);
        }
        if(elem.getType()=="KL"&&m_coef[4]==200)
        {
            elem.setSelec(false);
        }
        if(elem.getType()=="SURF"&&m_coef[5]==200)
        {
            elem.setSelec(false);
        }
        if(elem.getType()=="TPH"&&m_coef[6]==200)
        {
            elem.setSelec(false);
        }
        if(elem.getType()=="TC"&&m_coef[7]==200)
        {
            elem.setSelec(false);
        }
        if(elem.getType()=="TSD"&&m_coef[8]==100)
        {
            elem.setSelec(false);
        }
        if(elem.getType()=="TS"&&m_coef[9]==100)
        {
            elem.setSelec(false);
        }
        if(elem.getType()=="TK"&&m_coef[10]==200)
        {
            elem.setSelec(false);
        }
        if(elem.getType()=="BUS"&&m_coef[11]==200)
        {
            elem.setSelec(false);
        }
    }
    for(auto& elem:m_trajet)
    {
        if(elem.getFermeture()=="Fermer")
        {
            elem.setSelec(false);
        }
    }
}
void Station::FordFercuson()
{
    system("cls");
    std::cout<<std::endl;
    Goto(0,3);
    int cpt=1;
    int arretefinal;
    int arreteminimun=-1;
    std::cout<<"*************************************************************";
    for(int i=3;i<45;i++){
        Goto(0,i);
        std::cout<<"*";
        Goto(60,i);
        std::cout<<"*";
    }
    Goto(0,45);
    std::cout<<"*************************************************************";
    Goto(4,5);
    std::cout << "De quel lieu voulez-vous partir?"<<std::endl;     // choix du départ de l'arrivée
    for(auto& elem:m_lieu)
    {
        Goto(4,6+cpt);
        std::cout<<elem.getNbLieu()<<". Lieu: ";
        std::cout<<elem.getLieu()<<" a ";
        std::cout<<elem.getAltitude()<<"m d'altitude"<<std::endl;
    cpt++;
    }
    int debut=0;
    Goto(45,5);
    do
    {
        std::cin>>debut;
    }while(debut<0 || debut>m_nbLieu);
    system("cls");
    Goto(0,3);
     std::cout<<"*************************************************************";
    for(int i=3;i<45;i++){
        Goto(0,i);
        std::cout<<"*";
        Goto(60,i);
        std::cout<<"*";
    }
    Goto(0,45);
    std::cout<<"*************************************************************";
    Goto(4,5);
    cpt=1;
    std::cout << "A quel endroit voulez-vous allez? "<<std::endl;
    for(auto& elem:m_lieu)
    {
        Goto(1,cpt+6);
        std::cout<<elem.getNbLieu()<<". Lieu: ";
        std::cout<<elem.getLieu()<<" a ";
        std::cout<<elem.getAltitude()<<"m d'altitude"<<std::endl;
        cpt++;
    }
    int fin=0;
    Goto(45,5);
    do
    {
        std::cin>>fin;
    }while(fin<0 || fin>m_nbLieu||fin==debut);
    system("cls");
    for(auto& elem:m_trajet)        // on set tout les trajet, le flow a 0
    {
        elem.setFlow(0);
        elem.setSelec(true);
    }
    std::queue<int> resultat;
    int flowfinal=0;
    int flowmin=0;
    std::queue<float> resultPetit;
    while(bfs(debut,fin)==true)//si chemin trouver (antecedent de lieu fin existant) retourne true , sinon false
    {
        int anteBfs = m_lieu[fin-1].getVisite();//on recupere le predecesseur de chaque sommet
        if(anteBfs!=(-1))//si le sommet a des predecesseurs
        {
            resultat.push(m_lieu[fin-1].getNbLieu());
            while(true)
            {
                if(anteBfs!=(-1))
                {
                    resultat.push(m_lieu[anteBfs-1].getNbLieu());
                    anteBfs= m_lieu[anteBfs-1].getVisite();//on recupere le predecesseur de chaque sommet
                }
                else break;
            }
        }
        int r1;
        std::queue<int> resul2; // on crée notre 2nde queue qui va nous servir
        r1=resultat.front();
        resultat.pop();
        int flowmax=9999;
        while(!resultat.empty())//on recupere l'arete avec le moins de flow
        {
            for(auto& elem:m_trajet)
            {
                if(elem.getFin()==r1&&elem.getDebut()==resultat.front()&&elem.getSelec())
                {
                    if(elem.getMaxFlow()-elem.getFlow()<flowmax)
                    {
                        flowmax=elem.getMaxFlow()-elem.getFlow();
                        arreteminimun=elem.getNbTrajet();
                    }
                    resul2.push(elem.getNbTrajet());
                }
            }
            r1=resultat.front();
            resultat.pop();
        }
        int r2;
        std::queue<float>save;
        while(!resul2.empty())//on ajoute le flow a chaque arrete
        {
            r2=resul2.front();
            m_trajet[r2-1].setFlow(m_trajet[r2-1].getFlow()+flowmax);
            save.push(r2);
            resul2.pop();
        }
        flowfinal+=flowmax;
        for(auto& elem:m_trajet)
        {
            if(elem.getFlow()==elem.getMaxFlow())
            {
                elem.setSelec(false);
            }
        }
        if(flowmin<flowmax)
        {
            arretefinal=arreteminimun;
            flowmin=flowmax;
        }
    }
    Goto(1,5);
    std::cout<<"La capacite maximale du lieu ";
    std::cout<<m_lieu[debut-1].getLieu()<<" a ";
    std::cout<<m_lieu[debut-1].getAltitude()<<"m d'altitude"<<std::endl;
    Goto(1,7);
    std::cout<<"Au lieu ";
    std::cout<<m_lieu[fin-1].getLieu()<<" a ";
    std::cout<<m_lieu[fin-1].getAltitude()<<"m d'altitude"<<std::endl;
    Goto(1,9);
    std::cout<<"Est de "<<flowfinal<<" personne(s) par heure."<<std::endl;
    Goto(1,11);
    std::cout<< "Les trajets satures sont: "<<std::endl;
    for(auto& elem:m_trajet)
    {
        if(elem.getMaxFlow()==elem.getFlow())
        {
            CouleurCase(elem.getType());
            std::cout<<std::endl;
            std::cout<<elem.getNomTrajet()<<" qui est ";
            std::cout<<elem.TradType()<<" qui a pour capacite de ";
            std::cout<<elem.getFlow()<<" personne(s) par heure."<<std::endl;
        }
    }
   // delay(20000);
   // system("cls");
   CouleurReset();
    leave();

}
void Station::fermeturePiste()
{
    int choix=0;
    system("cls");
    std::cout << "Parametrage d'ouverture et fermeture des pistes: "<<std::endl;
    do
    {
        int cpt=5;

             for(auto& elem:m_trajet)
        {
            if(elem.getFermeture()=="Ouvert"){
                CouleurCase("V");
            }
            else{
                CouleurCase("R");
            }

            Goto(4,cpt);
            std::cout << "Trajet n" << elem.getNbTrajet();
            Goto(40,cpt);
            std::cout << "Depart: "<< m_trajet[elem.getDebut()-1].getNomTrajet();
            Goto(70,cpt);
            std::cout <<"Arrivee "<<m_trajet[elem.getFin()-1].getNomTrajet();
            Goto(110,cpt);
            std::cout <<"via "<< elem.TradType();
            Goto(150,cpt);
            std::cout <<"Temps "<< affichageTemps(elem.getReelTemps());
            std::cout <<" est actuellement: "<<elem.getFermeture()<<std::endl;;
            cpt++;
        }
        std::cout<<"\n"<<m_nbTrajet+1<<". Quitter"<<std::endl;
        Goto(200,150);
        std::cout<<"\n\nVeuillez saisir le trajet qui vous interesse: ";
        do{
            std::cin>>choix;                // l'utilisateur fait une saisie d'un trajet
        }while(choix<0 || choix>m_nbTrajet+1);
        system("cls");
        if(choix!=m_nbTrajet+1)
        {
            if(m_trajet[choix-1].getFermeture()=="Fermer")
            {
                m_trajet[choix-1].setFermeture("Ouvert");
            }
            else
            {
                m_trajet[choix-1].setFermeture("Fermer");
            }
        }
        }while(choix!=m_nbTrajet+1);
        reecritureFicher();
        CouleurReset();
    }


