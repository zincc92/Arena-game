#include "../prototypes.h"
#include "../structures.h"

void sort1_vampire(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, BITMAP* buffer_map, t_bloc matrice[23][23], int x_souris, int y_souris, BITMAP *cursor, BITMAP *map, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP *desc_sorts, int respiration[])
{
    BITMAP *buffer_pixels;
    buffer_pixels = create_bitmap(SCREEN_W,SCREEN_H);
    int red_temp, green_temp,blue_temp;
    int red_temp1, green_temp1,blue_temp1;
    int attaque = 0;
    int degats;
    int id_ennemi;
    int attaque_reussie;
    time_t start;
    /// tant qu'on ne clique pas sur l'icone de l'attaque de base, ou qu'on a lanc� l'attaque
    while (!attaque)
    {
        if (joueur[i].pa >= 2 && joueur[i].classe.spell[0].dispo)
        {
            clear_bitmap(buffer);
            blit(map, buffer, 0,0,0,0, SCREEN_W,SCREEN_H);
            affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
            dessin_ligne(joueur, i, nb_joueurs, buffer, buffer_pixels, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts, 1);
            dessin_diagonales(joueur, i, nb_joueurs, buffer, buffer_pixels, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts, 1);
            affichage_joueurs_respiration_ralenti(buffer, joueur, i, nb_joueurs, matrice, respiration, 5);
            display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
            lecture_pixels_buffer_map(buffer_map, &red_temp, &green_temp,&blue_temp);
            reperage_bloc_souris(&x_souris, &y_souris, red_temp, green_temp, blue_temp, matrice, joueur, i);
            lecture_pixels_buffer_map(buffer_pixels, &red_temp1, &green_temp1,&blue_temp1);
            // on attaque le joueur ennemi1 sur on clique et que la souris est sur lui
            if (matrice[x_souris][y_souris].occuper != matrice[joueur[i].x][joueur[i].y].occuper && matrice[x_souris][y_souris].occuper != 0 && mouse_b&1 && green_temp1 == 140)
            {
                id_ennemi = matrice[x_souris][y_souris].id_case - 1;
                if (joueur[id_ennemi].mortel)
                    degats = random(joueur[i].classe.spell[0].degats_min + 4, joueur[i].classe.spell[0].degats_max + 4);
                else
                    degats = random(joueur[i].classe.spell[0].degats_min, joueur[i].classe.spell[0].degats_max);
                /// NORD OUEST
                if (x_souris < joueur[matrice[x_souris][y_souris].occuper - 1].x && y_souris == joueur[matrice[x_souris][y_souris].occuper - 1].y)
                {
                    animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 1);
                }
                /// SUD EST
                if (x_souris > joueur[matrice[x_souris][y_souris].occuper - 1].x && y_souris == joueur[matrice[x_souris][y_souris].occuper - 1].y)
                {
                    animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 3);
                }
                /// SUD OUEST
                if (x_souris == joueur[matrice[x_souris][y_souris].occuper - 1].x && y_souris < joueur[matrice[x_souris][y_souris].occuper - 1].y)
                {
                    animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 0);
                }
                /// NORD EST
                if (x_souris == joueur[matrice[x_souris][y_souris].occuper - 1].x && y_souris > joueur[matrice[x_souris][y_souris].occuper - 1].y)
                {
                    animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 2);
                }
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

                if (pourcentage_de_chance() < 8 && joueur[i].pa >= 4)
                {
                    joueur[id_ennemi].pv = joueur[id_ennemi].pv - degats;
                    joueur[i].pv = joueur[i].pv + degats;
                    if (joueur[i].pv > 55)
                        joueur[i].pv = 55;
                    joueur[i].degatstotal = joueur[i].degatstotal + degats;
                    joueur[i].pa = joueur[i].pa - 2;
                    attaque_reussie = 1;
                }
                else
                {
                    joueur[i].pa = joueur[i].pa - 2;
                    attaque_reussie = 0;
                }
                joueur[i].classe.spell[0].dispo = 0;
                start = time(NULL);
                while ((int)time(NULL) - start < 3)
                {
                    clear_bitmap(buffer);
                    affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
                    affichage_joueurs_respiration_ralenti(buffer, joueur, i, nb_joueurs, matrice, respiration, 5);
                    if (attaque_reussie)
                        textprintf_ex(buffer, font, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].x_bloc - 10, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].y_bloc  - 72, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "- %d", degats);
                    else
                        textprintf_ex(buffer, font, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].x_bloc - 10, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].y_bloc  - 70, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "Attaque manque");
                    display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
                    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                }
                attaque = 1; // on a attaqu�, on peut sortir de la boucle en infligeant les d�g�ts, avec le % de chance
            }
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            if (mouse_x >= 335 && mouse_x <= 365 && mouse_y >= 670 && mouse_y <= 700 && mouse_b&1)
            {
                attaque = 1; // le joueur a annul� son attaque, l'attaque est consid�r� comme faite mais sans d�g�ts
            }
        }
        else
        {
            start = time(NULL);
            while ((int)time(NULL) - start < 2)
            {
                clear_bitmap(buffer);
                affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
                affichage_joueurs_respiration_ralenti(buffer, joueur, i, nb_joueurs, matrice, respiration, 5);
                textprintf_ex(buffer, font, matrice[joueur[i].x][joueur[i].y].x_bloc - strlen("Attaque indisponible") - 30, matrice[joueur[i].x][joueur[i].y].y_bloc  - 70, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "Attaque indisponible");
                display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            }
            attaque = 1;
        }
    }
}

void sort2_vampire(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, BITMAP* buffer_map, t_bloc matrice[23][23], int x_souris, int y_souris, BITMAP *cursor, BITMAP *map, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP *desc_sorts, int respiration[])
{
    BITMAP *buffer_pixels;
    buffer_pixels = create_bitmap(1280,720);
    int red_temp, green_temp,blue_temp;
    int red_temp1, green_temp1,blue_temp1;
    int attaque = 0;
    int id_ennemi;
    int degats;
    int attaque_reussie;
    time_t start = time(NULL);
    /// tant qu'on ne clique pas sur l'icone de l'attaque de base, ou qu'on a lanc� l'attaque
    while (!attaque)
    {
        if (joueur[i].pa >= 4 && joueur[i].classe.spell[1].dispo)
        {
            clear_bitmap(buffer);
            blit(map, buffer, 0,0,0,0, SCREEN_W,SCREEN_H);
            affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
            dessin_ligne(joueur, i, nb_joueurs, buffer, buffer_pixels, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts, 2);
            dessin_diagonales(joueur, i, nb_joueurs, buffer, buffer_pixels, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts, 1);
            affichage_joueurs_respiration_ralenti(buffer, joueur, i, nb_joueurs, matrice, respiration, 5);
            display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
            lecture_pixels_buffer_map(buffer_map, &red_temp, &green_temp,&blue_temp);
            reperage_bloc_souris(&x_souris, &y_souris, red_temp, green_temp, blue_temp, matrice, joueur, i);
            lecture_pixels_buffer_map(buffer_pixels, &red_temp1, &green_temp1,&blue_temp1);
            // on attaque le joueur ennemi1 sur on clique et que la souris est sur lui
            if (matrice[x_souris][y_souris].occuper != matrice[joueur[i].x][joueur[i].y].occuper && matrice[x_souris][y_souris].occuper != 0 && mouse_b&1 && green_temp1 == 140)
            {
                id_ennemi = matrice[x_souris][y_souris].id_case - 1;
                if (joueur[id_ennemi].mortel)
                    degats = random(joueur[i].classe.spell[0].degats_min + 4, joueur[i].classe.spell[0].degats_max + 4);
                else
                    degats = random(joueur[i].classe.spell[0].degats_min, joueur[i].classe.spell[0].degats_max);
                /// NORD OUEST
                if (x_souris < joueur[matrice[x_souris][y_souris].occuper - 1].x && y_souris == joueur[matrice[x_souris][y_souris].occuper - 1].y)
                {
                    animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 1);
                }
                /// SUD EST
                if (x_souris > joueur[matrice[x_souris][y_souris].occuper - 1].x && y_souris == joueur[matrice[x_souris][y_souris].occuper - 1].y)
                {
                    animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 3);
                }
                /// SUD OUEST
                if (x_souris == joueur[matrice[x_souris][y_souris].occuper - 1].x && y_souris < joueur[matrice[x_souris][y_souris].occuper - 1].y)
                {
                    animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 0);
                }
                /// NORD EST
                if (x_souris == joueur[matrice[x_souris][y_souris].occuper - 1].x && y_souris > joueur[matrice[x_souris][y_souris].occuper - 1].y)
                {
                    animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 2);
                }
                if (pourcentage_de_chance() < 7 && joueur[i].pa >= 4)
                {
                    joueur[id_ennemi].pv = joueur[id_ennemi].pv - degats;
                    joueur[i].degatstotal = joueur[i].degatstotal + degats;
                    joueur[i].pa = joueur[i].pa - 4;
                    attaque_reussie = 1;
                }
                else
                {
                    joueur[i].pa = joueur[i].pa - 4;
                    attaque_reussie = 0;
                }
                joueur[i].classe.spell[1].dispo = 0;
                start = time(NULL);
                while ((int)time(NULL) - start < 3)
                {
                    clear_bitmap(buffer);
                    affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
                    affichage_joueurs_respiration_ralenti(buffer, joueur, i, nb_joueurs, matrice, respiration, 5);
                    if (attaque_reussie)
                        textprintf_ex(buffer, font, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].x_bloc - 10, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].y_bloc  - 72, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "- %d", degats);
                    else
                        textprintf_ex(buffer, font, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].x_bloc - 10, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].y_bloc  - 70, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "Attaque manque");
                    display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
                    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                }
                attaque = 1; // on a attaqu�, on peut sortir de la boucle en infligeant les d�g�ts, avec le % de chance
            }
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            if (mouse_x >= 370 && mouse_x <= 400 && mouse_y >= 670 && mouse_y <= 700 && mouse_b&1)
            {
                attaque = 1; // le joueur a annul� son attaque, l'attaque est consid�r� comme faite mais sans d�g�ts
            }
        }
        else
        {
            start = time(NULL);
            while ((int)time(NULL) - start < 2)
            {
                clear_bitmap(buffer);
                affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
                affichage_joueurs_respiration_ralenti(buffer, joueur, i, nb_joueurs, matrice, respiration, 5);
                textprintf_ex(buffer, font, matrice[joueur[i].x][joueur[i].y].x_bloc - strlen("Attaque indisponible") - 30, matrice[joueur[i].x][joueur[i].y].y_bloc  - 70, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "Attaque indisponible");
                display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            }
            attaque = 1;
        }
    }
}

void sort3_vampire(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, BITMAP* buffer_map, t_bloc matrice[23][23], int x_souris, int y_souris, BITMAP *cursor, BITMAP *map, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP *desc_sorts, int respiration[])
{
    BITMAP *buffer_pixels;
    buffer_pixels = create_bitmap(SCREEN_W,SCREEN_H);
    int red_temp, green_temp,blue_temp;
    int red_temp1, green_temp1,blue_temp1;
    int attaque = 0;
    int id_ennemi;
    int attaque_effectue = 0;
    int attaque_reussie;
    time_t start = time(NULL);

    /// tant qu'on ne clique pas sur l'icone de l'attaque de base, ou qu'on a lanc� l'attaque
    while (!attaque)
    {
        if (joueur[i].pa >= 4 && joueur[i].classe.spell[2].dispo)
        {
            clear_bitmap(buffer);
            affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
            for (int j = -3; j <= 3; j++)
            {
                for (int h = -3; h <= 3; h++)
                {
                    dessin_bloc_unique(buffer, joueur[i].x + h, joueur[i].y + j, matrice, 255, 140, 0);
                    dessin_bloc_unique(buffer_pixels, joueur[i].x + h, joueur[i].y + j, matrice, 255, 140, 0);
                }
            }
            affichage_joueurs_respiration_ralenti(buffer, joueur, i, nb_joueurs, matrice, respiration, 5);
            display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            lecture_pixels_buffer_map(buffer_map, &red_temp, &green_temp,&blue_temp);
            reperage_bloc_souris(&x_souris, &y_souris, red_temp, green_temp, blue_temp, matrice, joueur, i);
            lecture_pixels_buffer_map(buffer_pixels, &red_temp1, &green_temp1,&blue_temp1);
            // on attaque le joueur ennemi1 sur on clique et que la souris est sur lui
            if (matrice[x_souris][y_souris].occuper != matrice[joueur[i].x][joueur[i].y].occuper && matrice[x_souris][y_souris].occuper != 0 && mouse_b&1 && green_temp1 == 140)
            {
                id_ennemi = matrice[x_souris][y_souris].id_case - 1;
                /// NORD OUEST
                if (x_souris < joueur[i].x && !attaque_effectue)
                {
                    attaque_effectue = 1;
                    animation_sort3_vampire(buffer, map, joueur, i, matrice, nb_joueurs, 1, respiration);
                }
                /// SUD EST
                if (x_souris > joueur[i].x && !attaque_effectue)
                {
                    attaque_effectue = 1;
                    animation_sort3_vampire(buffer, map, joueur, i, matrice, nb_joueurs, 3, respiration);
                }
                /// SUD OUEST
                if (y_souris < joueur[i].y && !attaque_effectue)
                {
                    attaque_effectue = 1;
                    animation_sort3_vampire(buffer, map, joueur, i, matrice, nb_joueurs, 0, respiration);
                }
                /// NORD EST
                if (y_souris > joueur[i].y && !attaque_effectue)
                {
                    attaque_effectue = 1;
                    animation_sort3_vampire(buffer, map, joueur, i, matrice, nb_joueurs, 2, respiration);
                }
                if (pourcentage_de_chance() < 6 && joueur[i].pa >= 4)
                {
                    joueur[id_ennemi].mortel = 1;
                    joueur[id_ennemi].compteur_mortel = 1;
                    joueur[i].pa = joueur[i].pa - 4;
                    attaque_reussie = 1;
                }
                else
                {
                    joueur[i].pa = joueur[i].pa - 4;
                    attaque_reussie = 0;
                }
                joueur[i].classe.spell[2].dispo = 0;
                start = time(NULL);
                while ((int)time(NULL) - start < 3)
                {
                    clear_bitmap(buffer);
                    affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
                    affichage_joueurs_respiration_ralenti(buffer, joueur, i, nb_joueurs, matrice, respiration, 5);
                    if (attaque_reussie)
                        textprintf_ex(buffer, font, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].x_bloc - strlen("Inflige marque mortel") - 10, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].y_bloc  - 72, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "Inflige marque mortel");
                    else
                        textprintf_ex(buffer, font, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].x_bloc - 10, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].y_bloc  - 70, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "Attaque manque");
                    display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
                    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                }
                attaque = 1; // on a attaqu�, on peut sortir de la boucle en infligeant les d�g�ts, avec le % de chance
            }

            if (mouse_x >= 405 && mouse_x <= 435 && mouse_y >= 670 && mouse_y <= 700 && mouse_b&1)
            {
                attaque = 1; // le joueur a annul� son attaque, l'attaque est consid�r� comme faite mais sans d�g�ts
            }
        }
        else
        {
            start = time(NULL);
            while ((int)time(NULL) - start < 2)
            {
                clear_bitmap(buffer);
                affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
                affichage_joueurs_respiration_ralenti(buffer, joueur, i, nb_joueurs, matrice, respiration, 5);
                textprintf_ex(buffer, font, matrice[joueur[i].x][joueur[i].y].x_bloc - strlen("Attaque indisponible") - 30, matrice[joueur[i].x][joueur[i].y].y_bloc  - 70, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "Attaque indisponible");
                display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            }
            attaque = 1;
        }
    }
}


void sort4_vampire(BITMAP *buffer_map, BITMAP * map,BITMAP * cursor, BITMAP *buffer, t_joueur* joueur, int i, t_bloc matrice[23][23], int *red_mouse, int * green_mouse, int *blue_mouse, int *ligne_souris,
                   int *colonne_souris, int nb_joueurs, BITMAP * hud_icone, BITMAP * desc_sorts, BITMAP **hud_joueur, BITMAP **icone_classes, int respiration[])
{
    int sort_lance = 0;
    int annulation = 0;
    int red_temp, green_temp, blue_temp;
    int tab[3] = {0,0,0};
    time_t start = time(NULL);
    if( !joueur[i].classe.spell[3].dispo)
    {
        while ((int)time(NULL) - start < 2)
        {
            clear_bitmap(buffer);
            affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
            affichage_joueurs_respiration_ralenti(buffer, joueur, i, nb_joueurs, matrice, respiration, 5);
            textprintf_ex(buffer, font, matrice[joueur[i].x][joueur[i].y].x_bloc - strlen("Attaque indisponible") - 30, matrice[joueur[i].x][joueur[i].y].y_bloc  - 70, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "Attaque indisponible");
            display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }
    }
    else
    {
        while(sort_lance == 0 && annulation == 0)
        {
            if(mouse_b &&1 && (abs(joueur[i].x - *ligne_souris) + abs(joueur[i].y - *colonne_souris)) <= 3 && matrice[*ligne_souris][*colonne_souris].accessible)
            {
                joueur[i].classe.spell[3].chance = random(joueur[i].classe.spell[3].degats_min,joueur[i].classe.spell[3].degats_max);
                if (pourcentage_de_chance() < 6 && joueur[i].pa >= 5)
                {
                    sort_lance = 1;
                    /// NORD OUEST
                    if (*ligne_souris < joueur[i].x )
                    {
                        joueur[i].direction = 1;
                    }
                    /// SUD OUEST
                    else if (*colonne_souris < joueur[i].y )
                    {
                        joueur[i].direction = 0;
                    }
                    /// SUD EST
                    if (*ligne_souris >= joueur[i].x )
                    {
                        joueur[i].direction = 3;
                    }
                    /// NORD EST
                    if (*colonne_souris >= joueur[i].y)
                    {
                        joueur[i].direction = 2;
                    }
                }
                else
                {
                    start = time(NULL);
                    while ((int)time(NULL) - start < 2)
                    {
                        clear_bitmap(buffer);
                        blit(map, buffer, 0,0,0,0, SCREEN_W,SCREEN_H);
                        affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
                        affichage_joueurs_respiration_ralenti(buffer, joueur, i, nb_joueurs, matrice, respiration, 5);
                        textprintf_ex(buffer, font, matrice[joueur[i].x][joueur[i].y].x_bloc - 10, matrice[joueur[i].x][joueur[i].y].y_bloc - 70, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "Attaque manque !");
                        display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
                        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                    }
                    joueur[i].pa = joueur[i].pa - 5;
                    joueur[i].classe.spell[3].dispo = 0;
                    annulation = 1;
                }
            }
            else if((mouse_b &&1 && mouse_x >= 280 && mouse_x<= 490 && mouse_y >= 650 && mouse_y <= 720) )
            {
                annulation = 1;
            }
            else
            {
                blit(map, buffer, 0,0,0,0, SCREEN_W, SCREEN_H);
                textprintf_ex(buffer, font, 0, 0, makecol(0, 0, 0), -1, "Mouse X : %d", mouse_x);
                textprintf_ex(buffer, font, 0, 10, makecol(0, 0, 0), -1, "Mouse Y : %d", mouse_y);
                lecture_pixels_buffer_map(buffer_map, red_mouse, green_mouse, blue_mouse);
                reperage_bloc_souris(ligne_souris, colonne_souris, *red_mouse, *green_mouse, *blue_mouse, matrice);
                int n = 0;
                if((abs(joueur[i].x - *ligne_souris) + abs(joueur[i].y - *colonne_souris)) <= 3 && matrice[*ligne_souris][*colonne_souris].accessible)
                {
                    for(int k = *ligne_souris-2; k < *ligne_souris+3; k++)
                    {
                        for (int l = *colonne_souris-2; l< *colonne_souris+3; l++)
                        {
                            if(matrice[k][l].accessible == 1 && (k >=0 && k <= 22) && (l >= 0 && l <= 22))
                            {
                                dessin_bloc_unique(buffer, k, l, matrice, 128,72,117);
                                if(matrice[k][l].id_case)
                                {
                                    tab[n] = matrice[k][l].id_case;
                                    n++;
                                }
                            }
                        }
                    }
                }
                affichage_hud_sorts(joueur, i, nb_joueurs, buffer, hud_icone, desc_sorts); // Blit de 5 logos (les m�mes pour la barre d'action, � changer apr�s...)
                affichage_hud_joueur(buffer, hud_joueur, joueur, i,icone_classes);
                affichage_joueurs_respiration_ralenti(buffer, joueur, i, nb_joueurs, matrice, respiration, 5);
                rest(5);
                display_cursor(cursor, buffer, mouse_x-5, mouse_y-5);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            }
        }
    }
    if (sort_lance == 1)
    {
        for (int l = 0; l<3; l++)
        {
            if (tab[l] != 0 && tab[l]-1 != i)
            {
                joueur[tab[l]-1].pv = joueur[tab[l]-1].pv - joueur[i].classe.spell[3].chance;
                joueur[i].degatstotal = joueur[i].degatstotal + joueur[i].classe.spell[3].chance;
            }
        }
        printf("degat %d \n", joueur[i].classe.spell[3].chance);
        joueur[i].pa = joueur[i].pa - 5;
        joueur[i].classe.spell[3].dispo = 0;
        int num_sprites = 0;
        int compteur = 0;
        time_t start = time(NULL);
        int rand1;
        int rand2;
        while((int)(time(NULL) - start < 4))
        {
            blit(map, buffer, 0,0,0,0, SCREEN_W, SCREEN_H);
            affichage_hud_sorts(joueur, i, nb_joueurs, buffer, hud_icone, desc_sorts); // Blit de 5 logos (les m�mes pour la barre d'action, � changer apr�s...)
            affichage_hud_joueur(buffer, hud_joueur, joueur, i,icone_classes);
            affichage_joueurs_respiration_ralenti(buffer, joueur, i, nb_joueurs, matrice, respiration, 5);
            draw_sprite(buffer, joueur[i].classe.spell[3].animation_sort[num_sprites], matrice[*ligne_souris][*colonne_souris].x_bloc - 161, matrice[*ligne_souris][*colonne_souris].y_bloc - 91);
            if (compteur == 30)
            {
                num_sprites = (num_sprites +1) % 2;
                compteur = 0;
                rand1 = rand()%(10);
                rand2 = rand()%(10);
            }
            if (joueur[i].classe.spell[3].chance == 8)
            {
                textout_ex(buffer, font,"COUP CRITIQUE !!", 100, 630, makecol(255,255,255), -1);
                textout_ex(buffer, font,"-8 ", 30 + rand2, 630 - rand1, makecol(255,255,255), -1);
            }
            compteur++;
            display_cursor(cursor, buffer, mouse_x-5, mouse_y-5);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }
    }
}
