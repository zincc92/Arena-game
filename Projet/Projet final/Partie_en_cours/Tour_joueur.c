#include "../prototypes.h"
#include "../structures.h"

void affichage_hud_sorts(t_joueur* joueur, int i, int nb_joueurs, BITMAP* buffer, BITMAP* hud_icone, BITMAP* desc_sorts)
{
    masked_blit(hud_icone, buffer, 0, 0, 280, 660, SCREEN_W, SCREEN_H);
    masked_blit(joueur[i].classe.logo_attaque, buffer, 0, 0, 300, 670, SCREEN_W, SCREEN_H);
    blit(joueur[i].classe.spell[0].logo, buffer, 0, 0, 335, 670, SCREEN_W, SCREEN_H);
    blit(joueur[i].classe.spell[1].logo, buffer, 0, 0, 370, 670, SCREEN_W, SCREEN_H);
    blit(joueur[i].classe.spell[2].logo, buffer, 0, 0, 405, 670, SCREEN_W, SCREEN_H);
    blit(joueur[i].classe.spell[3].logo, buffer, 0, 0, 440, 670, SCREEN_W, SCREEN_H);
    if (mouse_x >= 300 && mouse_x <= 330 && mouse_y >= 670 && mouse_y <= 700) // attaque de bas
    {
        masked_blit(desc_sorts, buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H);
    }
    if (mouse_x >= 335 && mouse_x <= 365 && mouse_y >= 670 && mouse_y <= 700) // sort 1
    {
        masked_blit(desc_sorts, buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H); // affichage bitmap description
        masked_blit(joueur[i].classe.spell[0].description, buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H); // affichage description sort 1

    }
    if (mouse_x >= 370 && mouse_x <= 400 && mouse_y >= 670 && mouse_y <= 700) // sort 2
    {
        masked_blit(desc_sorts, buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H); // affichage stats sorts
        masked_blit(joueur[i].classe.spell[1].description, buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H); // affichage bitmap description sort 2

    }
    if (mouse_x >= 405 && mouse_x <= 435 && mouse_y >= 670 && mouse_y <= 700) // sort 3
    {
        masked_blit(desc_sorts, buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H); // affichage stats sorts
        masked_blit(joueur[i].classe.spell[2].description, buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H); // affichage description sort 3

    }
    if (mouse_x >= 440 && mouse_x <= 470 && mouse_y >= 670 && mouse_y <= 700) // sort 4
    {
        masked_blit(desc_sorts, buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H); // affichage stats sort
        masked_blit(joueur[i].classe.spell[3].description, buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H); // affichage description sort 4
    }
}

void affichage_hud_joueur(BITMAP* buffer, BITMAP* hud, t_joueur* joueur, int i)
{
    rectfill(buffer, 72, 650, 74 + joueur[i].pv * 3, 673, makecol(255, 0, 0)); // rectangle pv a reduire quand il perd des hp
    rectfill(buffer, 68, 675, 70 + joueur[i].pa * 30, 685, makecol(0, 0, 255)); // rectangle pa a reduire quand il perd des hp
    rectfill(buffer, 66, 685, 70 + joueur[i].pm * 60, 695, makecol(0, 255, 0)); // rectangle pm a reduire quand il perd des hp
    masked_blit(hud, buffer, 0, 0, 3, 640, SCREEN_W, SCREEN_H);
    textprintf_ex(buffer, font, 120, 658, makecol(255, 255, 255), -1, "PV : %d/55", joueur[i].pv);
    textprintf_ex(buffer, font, 120, 676, makecol(255, 255, 255), -1, "PA : %d/6", joueur[i].pa);
    textprintf_ex(buffer, font, 120, 687, makecol(255, 255, 255), -1, "PM : %d/3", joueur[i].pm);
}

void tour_joueur(BITMAP* buffer, BITMAP *cursor, t_joueur* joueur, int nb_joueurs)
{
    // Déclaration du pointeur sur BITMAP devant recevoir l'image
    BITMAP *map;
    BITMAP *hud_joueur;
    BITMAP *hud_icone;
    BITMAP *desc_sorts;
    FONT *kristen12;
    FONT *fixedsys;

    BITMAP *buffer2;
    BITMAP * buffer_pixels; // LE 2
    BITMAP * buffer_map; // LE 1
    BITMAP * croix_rouge;
    BITMAP * croix_bleue;

    int i = 0;
    t_bloc matrice[23][23];

    // Chargement de l'image (l'allocation a lieu en m�me temps)

    map = load_bitmap("BITMAP/map_reparation.bmp", NULL);
    hud_joueur = load_bitmap("BITMAP/hud_joueur2.bmp", NULL);
    hud_icone = load_bitmap("BITMAP/hud_icone_temp.bmp", NULL);
    desc_sorts = load_bitmap("BITMAP/desc_sorts.bmp", NULL);
    kristen12 = load_font("FONT/kristen12.pcx", NULL, NULL);
    fixedsys = load_font("FONT/fixedsys10.pcx", NULL, NULL);

    buffer =create_bitmap(SCREEN_W,SCREEN_H);
    buffer_map =create_bitmap(SCREEN_W,SCREEN_H);
    buffer2 =create_bitmap(SCREEN_W,SCREEN_H);
    buffer_pixels =create_bitmap(SCREEN_W,SCREEN_H);
    croix_rouge = load_bitmap("BITMAP/croix_rouge.bmp", NULL);
    croix_bleue = load_bitmap("BITMAP/croix_bleue.bmp", NULL);


    //creations des classes pour chaque joueurs
    creation_icones_classes(joueur);

    // creation des calques sous la map, et initialisation des cases innacessibles, pour avoir le systeme de souris sur les blocs
    distribution_couleur_blocs(buffer_map, matrice);
    definition_accessible(matrice);
    definition_occuper(matrice);

    if (!map)
    {
        allegro_message("pas pu trouver tour joueur/charger mon_image.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    if (!croix_bleue || !croix_rouge)
    {
        allegro_message("pas pu trouver les croix");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    clear_bitmap(buffer);
    time_t start = time(NULL);

    textout_ex(desc_sorts, font, "DEGATS:", 18, 20, makecol(255, 0, 0), -1);
    textout_ex(desc_sorts, font, "PA:", 18, 34, makecol(60, 0, 255), -1);
    textout_ex(desc_sorts, font, "PM:", 18, 48, makecol(0, 255, 0), -1);
    textout_ex(desc_sorts, font, "Portee:", 18, 62, makecol(255, 255, 255), -1);
    textout_ex(desc_sorts, font, "%", 18, 76, makecol(0, 0, 0), -1);
    textout_ex(desc_sorts, font, "chance:", 34, 76, makecol(0, 0, 0), -1);

    //textprintf_ex(desc_sorts, font, 80, 16, makecol(255, 0, 0), -1, "%d-%d", 1, joueur[i].classe.attaque);
    int ligne_souris, colonne_souris;

    int green_mouse, red_mouse, blue_mouse, green_mouse2, red_mouse2, blue_mouse2;
    int joueur_en_vie = nb_joueurs;
    int autorisation_dep = 0;
    time_t chrono1 = time (NULL);
    time_t chrono2 = time (NULL);

    int erreur1 = 0;
    int erreur2 = 0;
    int clic = 0;
    int deplacement_effectuer = 0;
    int nombre_pm = 3;

    /// initialisation des coordonnées de chaque jour a la case x = 0, y = 0
    for (int i = 0; i<nb_joueurs; i++)
    {
        joueur[i].x = i;
        joueur[i].y =  i;
    }
    int fini = 0, choix1= 0, choix2= 0, choix3= 0, choix4= 0;

    /// tant que tous les joueurs ne sont pas positionnés
    while(fini != nb_joueurs)
    {
        blit(map, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        /// dessin des zones de placement
        affichage_emplacement_depart(buffer, nb_joueurs, matrice, joueur);

        lecture_pixels_buffer_map(buffer_map, &red_mouse, &green_mouse, &blue_mouse);
        lecture_pixels_buffer_map(buffer, &red_mouse2, &green_mouse2, &blue_mouse2);
        /// condition de placement
        condition_positionnement_depart(&fini, ligne_souris, colonne_souris, matrice, joueur, &choix1, &choix2, &choix3, &choix4, red_mouse2, green_mouse2, blue_mouse2);

        textprintf_ex(buffer, font, 500, 100, makecol(255,255,255), -1, "%s, choisissez votre emplacement de depart", joueur[i].pseudo);
        reperage_bloc_souris(&ligne_souris, &colonne_souris, red_mouse, green_mouse, blue_mouse, matrice, &autorisation_dep);
        ///affichage de tous les joueurs en meme temps
        for (int j = 0; j< nb_joueurs; j++)
        {
            couleur_sous_joueur(buffer, joueur[j].x, joueur[j].y, matrice);
            circlefill(buffer, matrice[joueur[j].x][joueur[j].y].x_bloc, matrice[joueur[j].x][joueur[j].y].y_bloc, 9, makecol(joueur[j].red,joueur[j].green,joueur[j].blue));
        }
        textprintf_ex(buffer,font,96,36,makecol(0,255,0), makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);
        //affichage_croix_bleue(buffer, croix_bleue, ligne_souris, colonne_souris, matrice);
        //affichage_croix_rouge(buffer, croix_rouge, ligne_souris, colonne_souris, matrice);
        display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }

    // Boucle d'animation
    while (joueur_en_vie != 1)
    {
        if (joueur[i].vivant) // on fait joueur le joueur i car il est vivant
        {
            clear_bitmap(buffer);
            blit(map, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            affichage_hud_sorts(joueur, i, nb_joueurs, buffer, hud_icone, desc_sorts); // Blit de 5 logos (les mêmes pour la barre d'action, à changer après...)
            affichage_hud_joueur(buffer, hud_joueur, joueur, i); // affiche du hud joueur, avec pv, pa, pm
            textprintf_ex(buffer, font, 0, 0, makecol(0, 0, 0), -1, "Mouse X : %d", mouse_x);
            textprintf_ex(buffer, font, 0, 10, makecol(0, 0, 0), -1, "Mouse Y : %d", mouse_y);
            textprintf_ex(buffer, font, 0, 20, makecol(0, 0, 0), -1, "Temps: %f", (float)((time(NULL)) - start));
            rectfill(buffer, 1000, 650, 1000 - (int)((time(NULL)) - start) * 5, 673, makecol(255, 0, 0)); // barre de temps

            lecture_pixels_buffer_map(buffer_map, &red_mouse, &green_mouse, &blue_mouse);
            reperage_bloc_souris(&ligne_souris, &colonne_souris, red_mouse, green_mouse, blue_mouse, matrice, &autorisation_dep, joueur, i);
            reperage_chemin(buffer, joueur[i].x, joueur[i].y, ligne_souris, colonne_souris, matrice, joueur, i, &autorisation_dep);

            if(autorisation_dep == 1)
            {
                /*/// variables contenant les parametres de la souris au moment du clic
                lecture_pixels_buffer_map(buffer_map, &red_mouse, &green_mouse, &blue_mouse);
                /// recherche du bloc correspondant sous la souris au moment du clic
                reperage_bloc_souris(&ligne_souris, &colonne_souris, red_mouse, green_mouse, blue_mouse, matrice, &autorisation_dep);*/

                /*/// condition si la souris clic sur un bloc valable
                if (matrice[ligne_souris][colonne_souris].accessible == 0)
                {
                    textout_ex(screen, font,"Vous ne pouvez pas vous deplacer en dehors de la carte !! ",15, 30, makecol(255,0,0), -1); /////// A CHANGER PLUS TARD
                    sleep(3); ///////// A CHANGER PLUS TARD
                    chrono1 = time(NULL);
                    erreur1 =1;
                }
                else if (matrice[ligne_souris][colonne_souris].occuper == 1)
                {
                    textout_ex(screen, font,"Cette case est deja occupee par un joueur ou un obstacle !! ", 800, 30, makecol(255,255,0), -1); /////// A CHANGER PLUS TARD
                    sleep(3); ///////// A CHANGER PLUS TARD
                    chrono2 = time(NULL);
                    erreur2 =1;
                }
                else
                {*/
                deplacement_personnage(buffer, map, joueur, i, ligne_souris, colonne_souris, matrice, &deplacement_effectuer, nb_joueurs);
                autorisation_dep = 0;
                //}
            }
            //lecture_pixels_buffer_map(buffer_map, &red_mouse, &green_mouse, &blue_mouse); // ca bug
            quadrillage_test(buffer);
            //encadrement_souris(buffer, red_mouse, green_mouse, blue_mouse);
            display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
            //affichage_croix_bleue(buffer, croix_bleue, &ligne_souris, &colonne_souris, matrice); // bug avec classe chevalier // assassin
            //affichage_croix_rouge(buffer, croix_rouge, &ligne_souris, &colonne_souris, matrice); // bug avec classe chevalier // assassin
            //deplacement_nombre_pm(buffer_pixels, buffer, joueur[i].x, joueur[i].y, matrice, &nombre_pm, &clic, cursor);
            for (int j = 0; j< nb_joueurs; j++)
            {
                if (joueur[j].vivant)
                {
                    //couleur_sous_joueur(buffer, joueur[j].x, joueur[j].y, matrice);
                    masked_blit(joueur[j].classe.deplacement[0][0], buffer, 0, 0, matrice[joueur[j].x][joueur[j].y].x_bloc - 22, matrice[joueur[j].x][joueur[j].y].y_bloc - 52, 49, 64);
                }
            }
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            if ((int)(time(NULL) - start >= TEMPS_TOUR) || (mouse_b&1 && (mouse_x >= 900 && mouse_x <= 1000 && mouse_y >= 600 && mouse_y <= 700)))
            {
                start = time(NULL);
                joueur[i].pm = 3; // on remet les pm et pa du joueur au nombre initial
                joueur[i].pa = 6;
                i = (i + 1) % nb_joueurs; // On boucle car temps finis ou on a cliqué sur le bouton
            }
        }
        else
        {
            i = (i + 1) % nb_joueurs; // On boucle car le joueur est mort
        }
        rest(20);
    }
    /// On fera une espèce d'animation de fin de jeu, on affiche le classement et on appuie sur un bouton quand on veut continuer
    /// on revient donc au menu (insérez le programme de Sarah)

    for (int i = 0; i < 4; i++)
    {
        destroy_bitmap(joueur[i].classe.logo_attaque);
        for (int j = 0; j < NB_SORTS; j++)
        {
            destroy_bitmap(joueur[i].classe.spell[j].description);
            destroy_bitmap(joueur[i].classe.spell[j].logo);
        }
    }
    destroy_bitmap(map);
    destroy_bitmap(hud_joueur);
    destroy_bitmap(hud_icone);
}
