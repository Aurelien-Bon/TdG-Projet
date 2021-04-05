#include "Station.h"
#include <fstream>
#include <string>
#include <queue>
#include <stack>
class myComparator///geeksforgeeks.org modifier par Aur�lien Bon
{
public:
    float operator()(Lieu& a1,Lieu& a2) // receives 2 edges
    {
        if(a1.getTemps()==a2.getTemps())    //if the first egde has the same weight as the second one
            return a1.getNbLieu() > a2.getNbLieu();
        return a1.getTemps() > a2.getTemps();
    }
};

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
        Lieu n(nomLieu,nbLieu,altitude);   // on rajoute � chaque fois une case
        m_lieu.push_back(n);
    }
    ifs >> m_nbTrajet;    // on associe la taille par rapport aux donn�es
    for(int i=0;i<m_nbTrajet;i++)
    {
        int nbTrajet,a , b;
        std::string nomTrajet,typeTrajet;
        ifs >>nbTrajet>>nomTrajet>>typeTrajet>> a >> b;
        Trajet n(nbTrajet,nomTrajet,typeTrajet,a,b);    // on cr�e une arete avec sommet de d�part et d'arriv�e en comptant � la suite du poids de cette arete
        n.setReelTemps(CalculTemps(n));
        m_trajet.push_back(n);
    }
    for(int i=0;i<12;i++)
    {
        int coef;
        ifs >> coef;
        m_coef.push_back(coef);
    }
    std::string test;
    while(std::getline(ifs,test))
    {
        m_mode+=test;
    }
}
Station::~Station()
{

}

float Station::CalculTempsCoef(Trajet traj)
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
void Station::afficher()
{
    std::cout<<"Lieu:"<<std::endl;
    for(auto& elem:m_lieu)
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
    std::cout<<"Choisissez un lieu parmi les suivants:"<<std::endl;
    for(auto& elem:m_lieu)
    {
        std::cout<<elem.getNbLieu()<<". Lieu: ";
        std::cout<<elem.getLieu()<<" a ";
        std::cout<<elem.getAltitude()<<"m d'altitude"<<std::endl;
    }
    int choix=0;
    do
    {
        std::cin>>choix;
    }while(choix<0 || choix>m_nbLieu);
    system("cls");
    std::cout<<"Depuis "<<m_lieu[choix-1].getLieu()<<", vous pouvez prendre: "<<std::endl;
    for(auto& elem:m_trajet)
    {
        if(elem.getDebut()==choix)
        {
            std::cout << "Le trajet numero " << elem.getNbTrajet() << " vers ";
            std::cout << m_trajet[elem.getFin()-1].getNomTrajet()<<" en utilisant ";
            std::cout << elem.TradType()<<" pour une duree de ";
            std::cout << affichageTemps(elem.getReelTemps()) << " minute"<<std::endl;
        }
    }
    std::cout<<"Vous pouvez aller a "<<m_lieu[choix-1].getLieu()<<" en prenant: "<<std::endl;
    for(auto& elem:m_trajet)
    {
        if(elem.getFin()==choix)
        {
            std::cout << "Le trajet numero " << elem.getNbTrajet() << " depuis ";
            std::cout << m_trajet[elem.getDebut()-1].getNomTrajet()<<" en utilisant ";
            std::cout << elem.TradType()<<" pour une duree de ";
            std::cout << affichageTemps(elem.getReelTemps())<<std::endl;
        }
    }
}
void Station::AffichageTrajet()
{

    std::cout<<"Veuillez saisir le trajet qui vous interesse"<<std::endl;
    for(auto& elem:m_trajet)
    {
        std::cout << "Le trajet numero " << elem.getNbTrajet() << " depuis ";
        std::cout << m_trajet[elem.getDebut()-1].getNomTrajet()<<" vers ";
        std::cout << m_trajet[elem.getFin()-1].getNomTrajet()<<" en utilisant ";
        std::cout << elem.TradType()<<" pour une duree de ";
        std::cout << affichageTemps(elem.getReelTemps())<<std::endl;
    }
    int choix=0;
    do{
        std::cin>>choix;
    }while(choix<0 || choix>m_nbTrajet);
    system("cls");
    std::cout<<"Vous empruntez le trajet : "<<m_trajet[choix-1].getNomTrajet();
    std::cout<<" pour aller de "<< m_lieu[m_trajet[choix-1].getDebut()-1].getLieu();
    std::cout<<" vers "<<m_lieu[m_trajet[choix-1].getFin()-1].getLieu();
    std::cout<<" en utilisant "<<m_trajet[choix-1].TradType();
    std::cout<<", vous mettrez " << affichageTemps(m_trajet[choix-1].getReelTemps())<<std::endl;
}
void Station::dijkstra()
{
    for(auto& elem:m_trajet)
    {
        elem.setTemps(CalculTempsCoef(elem));
        std::cout <<elem.getNbTrajet()<<" | "<<elem.getTemps()<<" ";
    }
    std::cout<<std::endl;
    std::cout << "De quel lieu voulez-vous partir?"<<std::endl;
    for(auto& elem:m_lieu)
    {
        std::cout<<elem.getNbLieu()<<". Lieu: ";
        std::cout<<elem.getLieu()<<" a ";
        std::cout<<elem.getAltitude()<<"m d'altitude"<<std::endl;
    }
    int debut=0;
    do
    {
        std::cin>>debut;
    }while(debut<0 || debut>m_nbLieu);
    system("cls");
    std::cout << "A quel endroit voulez-vous allez? "<<std::endl;
    for(auto& elem:m_lieu)
    {
        std::cout<<elem.getNbLieu()<<". Lieu: ";
        std::cout<<elem.getLieu()<<" a ";
        std::cout<<elem.getAltitude()<<"m d'altitude"<<std::endl;
    }
    int fin=0;
    do
    {
        std::cin>>fin;
    }while(fin<0 || fin>m_nbLieu||fin==debut);
    for(auto& elem:m_lieu)    // pour chaque sommetn on consid�re qu'ils n'ont pas encore �t� visit�, de plus on met leur couleur a blanc et on leur assigne un poids impossible
    {
        elem.setColor(0);
        elem.setVisite(-1);
        elem.setTemps(9999.99);
    }
    m_lieu[debut-1].setTemps(0.00);    // le sommet de d�part � son poids set a 0
    bool graphParcouru=false;   // bool�en utilis� comme condition de sortie
    std::priority_queue<Lieu,std::vector<Lieu>,myComparator>listeTraite; // cr�ation d'un vecteur de sommet pour la liste des donn�es trait�es
    for(auto& elem:m_lieu)
    {
        if(elem.getColor()==0)
        {
            listeTraite.push(elem);
        }
    }
    m_lieu[debut-1].setColor(1);
    do
    {
        for(auto& elem:m_lieu)
        {
            if(elem.getColor()==0)
            {
                listeTraite.push(elem);
            }
        }
        Lieu a=listeTraite.top();
        m_lieu[a.getNbLieu()-1].setColor(1);
        for(auto& elem:m_trajet)  // pour chaque element contenu dans la liste d'arete correspond � la case de liste trait�e la case passage
        {
            if(elem.getDebut()==a.getNbLieu())
            {
                if(m_lieu[elem.getFin()-1].getColor()!=1)   // si le sommet r�cup�r� a une couleur diff�rent de 1 (noir)
                {
                    if(m_lieu[elem.getFin()-1].getTemps()>(elem.getTemps()+m_lieu[elem.getDebut()-1].getTemps()))   // si le poids du sommet de fin de l'�l�ment �tudi� est sup�rieur � la somme du poids de l'�l�ment �tudi� et du sommet de d�part de l'�l�ment de d�part
                    {
                        m_lieu[elem.getFin()-1].setVisite(elem.getDebut()); // ce sommet en question a sa visite set � la meme valeur que le sommmet de d�part
                        m_lieu[elem.getFin()-1].setTemps(elem.getTemps()+m_lieu[elem.getDebut()-1].getTemps()); // son poids est modifi� de telle mani�re � avoir la somme du poids de notre �l�ment �tudi� et de notre �l�ment de d�part
                    }
                }
            }
        }
        for(auto& elem:m_lieu)//reactualisation des poids de tout les sommet
        {
            float newTemps=elem.getTemps(); // on recup l'�l�ment �tudi�
            for(auto& art:m_trajet)     // pour chaque �lement r�cup�r� par rapport aux aretes pr�c�dentes
            {
                if(art.getFin()==elem.getNbLieu())
                {
                    if(art.getDebut()==elem.getVisite())    // si l'elem correspond � l'�l�ment visit�
                    {
                        newTemps=art.getTemps()+m_lieu[art.getDebut()-1].getTemps();    // le new poids est modifi� par la somme des deux autres poids
                    }
                }
            }
            elem.setTemps(newTemps);    // on change le poids de l'�l�ment
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
    std::cout<<"----------------------------"<<std::endl;
    std::cout<<"Voici l'itineraire le plus rapide de "<<m_lieu[debut-1].getLieu()<<" jusqu'a "<<m_lieu[fin-1].getLieu()<<" avec le mode "<<m_mode<<" actif: "<<std::endl;
    anteDij=reponse.top();
    reponse.pop();
    float totalTemps=0;
    while(!reponse.empty())
    {
        for(auto& elem:m_trajet)
        {
            if(elem.getDebut()==anteDij&&elem.getFin()==reponse.top())
            {
                std::cout<<"Vous empruntez le trajet : "<<elem.getNomTrajet();
                std::cout<<" pour aller de "<< m_lieu[elem.getDebut()-1].getLieu();
                std::cout<<" vers "<<m_lieu[elem.getFin()-1].getLieu();
                std::cout<<" en utilisant "<<elem.TradType();
                std::cout<<", vous mettrez " << affichageTemps(elem.getReelTemps())<<std::endl;
                totalTemps+=elem.getReelTemps();
            }
        }
        anteDij=reponse.top();
        reponse.pop();
    }
    std::cout<< " Pour une duree totale de "<<affichageTemps(totalTemps)<<std::endl;
    std::cout<<"----------------------------"<<std::endl;
}
void Station::bfs()
{
    for(auto& elem:m_trajet)
    {
        elem.setTemps(CalculTemps(elem));
    }
    std::cout << "De quel lieu voulez-vous partir?"<<std::endl;
    for(auto& elem:m_lieu)
    {
        std::cout<<elem.getNbLieu()<<". Lieu: ";
        std::cout<<elem.getLieu()<<" a ";
        std::cout<<elem.getAltitude()<<"m d'altitude"<<std::endl;
    }
    int debut=0;
    do
    {
        std::cin>>debut;
    }while(debut<0 || debut>m_nbLieu);
    system("cls");

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
            if(succ.getDebut()==trait.getNbLieu())
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

    std::cout<<"----------------------------"<<std::endl;
    std::cout<<"Parcours du BFS a partir du lieu "<<debut<<": "<<std::endl;
    for(auto& elem:m_lieu)
    {
        int anteBfs = elem.getVisite();//on recupere le predecesseur de chaque sommet
        if(anteBfs!=(-1))//si le sommet a des perdecesseur
        {
            std::cout<<elem.getNbLieu();
            while(true)
            {
                if(anteBfs!=(-1))
                {
                    std::cout<<" <-- "<< anteBfs;
                    anteBfs= m_lieu[anteBfs-1].getVisite();//on recupere le predecesseur de chaque sommet
                }
                else break;
            }
            std::cout<<std::endl;
        }
    }
    std::cout<<"----------------------------"<<std::endl;
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
    std::cout<< "Mode actuellement selectionne: "<<m_mode<<std::endl;
    std::cout<< "1. Tres bon skieur (pas de V et peut de B)"<<std::endl;
    std::cout<< "2. Skieur Moyen (pas N)"<<std::endl;
    std::cout<< "3. Sans dechausser (pas de TDH,TC,BUS)"<<std::endl;
    std::cout<< "4. Peur du vide (Pas de TDS, TS)"<<std::endl;
    std::cout<< "5. Professionel (R,N prioriter)"<<std::endl;
    std::cout<< "6. Visite (priorite piste N,R,B,V)"<<std::endl;
    std::cout<< "7. Aucun"<<std::endl;
    std::cout<< "Quel mode voulez-vous choisir?: "<<std::endl;
    std::cout<< "/!\\ Pour acceder a certains endroits de la station, vous pourriez etre oblige d'emprunter certains chemins que vous souhaitez eviter /!\\ "<<std::endl;
    int choix=0;
    do
    {
        std::cin>>choix;
    }while(choix<0 || choix>7);
    for(auto& elem:m_coef)//reste des coef
    {
        elem=1;
    }
    switch(choix)
    {
    case 1:
        m_coef[0]=500;
        m_coef[1]=100;
        m_mode="Tres bon skieur";
        break;
    case 2:
        m_coef[3]=500;
        m_mode="Skieur moyen";
        break;
    case 3:
        m_coef[6]=500;
        m_coef[7]=500;
        m_coef[11]=500;
        m_mode="Sans dechausser";
        break;
    case 4:
        m_coef[8]=100;
        m_coef[9]=100;
        m_mode="Peur du vide";
        break;
    case 5:
        m_coef[0]=500;
        m_coef[1]=500;
        m_mode="Professionel";
        break;
    case 6:
        m_coef[6]=500;
        m_coef[7]=500;
        m_coef[8]=100;
        m_coef[9]=100;
        m_coef[10]=100;
        m_coef[11]=500;
        m_mode="Visite";
        break;
    case 7:
        m_mode="Defaut";
        system("cls");
        break;
    }
    system("cls");
    reecritureFicher();
}
void Station::reecritureFicher()
{
    std::vector<std::string> fichier;
    std::ifstream ifs{m_filename};  // ouverture du flux de lecture
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + m_filename );
    for (int i=0; i<m_nbLieu+m_nbTrajet+2; ++i)
    {
        std::string line;
        std::getline(ifs,line);
        fichier.push_back(line);
    }
    for(auto& elem:m_coef)
    {
        fichier.push_back(std::to_string(elem));
    }
    fichier.push_back(m_mode);
    std::ofstream ofs{m_filename};
    if(!ofs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + m_filename );
    for(auto& elem:fichier)
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
