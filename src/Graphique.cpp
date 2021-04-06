#include "Graphique.h"
Graphique::Graphique()
{
}
Graphique::Graphique(int a)
{
    allegro_init();
    install_keyboard();
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    //register_png_file_type();
    //jpgalleg_init();
}
Graphique::~Graphique()
{

}
BITMAP* Graphique::charement(std::string chemin)
{
    BITMAP* image;
    // Chargement de l'image (l'allocation a lieu en même temps)
    image=load_bitmap(chemin.c_str(),NULL);

    // Vérification que l'image est bien chargée (dans le cas contraire image vaut NULL)
    // TOUJOURS LE FAIRE CAR ON N'EST JAMAIS CERTAIN DE BIEN TROUVER L'IMAGE
    if (!image)
    {
        allegro_message("pas pu trouver/charger");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    return image;

}
void Graphique::afficher()
{

}
