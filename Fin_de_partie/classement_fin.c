#include "../prototypes.h"
#include "../structures.h"

#include "../prototypes.h"
#include "../structures.h"

void classement_fin2(BITMAP * buffer, t_joueur * joueur, int nb_joueurs, int classement[])
{
    BITMAP *ecran_fin;
    printf("%d\n", nb_joueurs);
    ecran_fin=load_bitmap("BITMAP/GAMEOVER.bmp",NULL);
    if (!ecran_fin)
    {
        allegro_message("pas pu trouver tour joueur/charger mon_image de fin.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    if (nb_joueurs == 2)
    {
        textprintf_ex(buffer, font, 80, 100, makecol(255,255,255), -1, "1er : Joueur %d", classement[0]);
        textprintf_ex(buffer, font, 80, 110, makecol(255,255,255), -1, "Degats inflig�s : %d", joueur[classement[0]].degatstotal);
        textprintf_ex(buffer, font, 80, 120, makecol(255,255,255), -1, "Cases parcourues : %d", joueur[classement[0]].casesparcourues);
        textprintf_ex(buffer, font, 130, 100, makecol(255,255,255), -1, "2eme : Joueur %d", classement[1]);
        textprintf_ex(buffer, font, 130, 110, makecol(255,255,255), -1, "Degats inflig�s : %d", joueur[classement[1]].degatstotal);
        textprintf_ex(buffer, font, 130, 120, makecol(255,255,255), -1, "Cases parcourues : %d", joueur[classement[1]].casesparcourues);
    }
    printf("zefrgthr\n");
    if (nb_joueurs == 3)
    {
        textprintf_ex(buffer, font, 80, 100, makecol(255,255,255), -1, "1er : Joueur %d, %s", classement[0], joueur[classement[0]].pseudo);
        textprintf_ex(buffer, font, 80, 110, makecol(255,255,255), -1, "Degats inflig�s : %d", joueur[classement[0]].degatstotal);
        textprintf_ex(buffer, font, 80, 120, makecol(255,255,255), -1, "Cases parcourues : %d", joueur[classement[0]].casesparcourues);
        textprintf_ex(buffer, font, 130, 100, makecol(255,255,255), -1, "2eme : Joueur %d, %s", classement[1], joueur[classement[1]].pseudo);
        textprintf_ex(buffer, font, 130, 110, makecol(255,255,255), -1, "Degats inflig�s : %d", joueur[classement[1]].degatstotal);
        textprintf_ex(buffer, font, 130, 120, makecol(255,255,255), -1, "Cases parcourues : %d", joueur[classement[1]].casesparcourues);
        textprintf_ex(buffer, font, 200, 100, makecol(255,255,255), -1, "3eme : Joueur %d, %s", classement[2], joueur[classement[2]].pseudo);
        textprintf_ex(buffer, font, 200, 110, makecol(255,255,255), -1, "Degats inflig�s : %d", joueur[classement[2]].degatstotal);
        textprintf_ex(buffer, font, 200, 120, makecol(255,255,255), -1, "Cases parcourues : %d", joueur[classement[2]].casesparcourues);


    }
    if (nb_joueurs == 4)
    {
        textprintf_ex(buffer, font, 80, 100, makecol(255,255,255), -1, "1er : Joueur %d, %s", classement[0], joueur[classement[0]].pseudo);
        textprintf_ex(buffer, font, 80, 110, makecol(255,255,255), -1, "Degats inflig�s : %d", joueur[classement[0]].degatstotal);
        textprintf_ex(buffer, font, 80, 120, makecol(255,255,255), -1, "Cases parcourues : %d", joueur[classement[0]].casesparcourues);
        textprintf_ex(buffer, font, 130, 100, makecol(255,255,255), -1, "2eme : Joueur %d, %s", classement[1], joueur[classement[1]].pseudo);
        textprintf_ex(buffer, font, 130, 110, makecol(255,255,255), -1, "Degats inflig�s : %d", joueur[classement[1]].degatstotal);
        textprintf_ex(buffer, font, 130, 120, makecol(255,255,255), -1, "Cases parcourues : %d", joueur[classement[1]].casesparcourues);
        textprintf_ex(buffer, font, 200, 100, makecol(255,255,255), -1, "3eme : Joueur %d, %s", classement[2], joueur[classement[2]].pseudo);
        textprintf_ex(buffer, font, 200, 110, makecol(255,255,255), -1, "Degats inflig�s : %d", joueur[classement[2]].degatstotal);
        textprintf_ex(buffer, font, 200, 120, makecol(255,255,255), -1, "Cases parcourues : %d", joueur[classement[2]].casesparcourues);
        textprintf_ex(buffer, font, 260, 100, makecol(255,255,255), -1, "4eme : Joueur %d, %s", classement[3], joueur[classement[3]].pseudo);
        textprintf_ex(buffer, font, 260, 110, makecol(255,255,255), -1, "Degats inflig�s : %d", joueur[classement[3]].degatstotal);
        textprintf_ex(buffer, font, 260, 120, makecol(255,255,255), -1, "Cases parcourues : %d", joueur[classement[3]].casesparcourues);
    }
    printf("zefrgthr\n");
    blit(ecran_fin, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);
    printf("zefrgthr\n");
    blit(buffer, screen,0,0,0,0, SCREEN_W, SCREEN_H);
}

void classement_fin(BITMAP * buffer, t_joueur * joueur, int nb_joueurs, int classement[])
{
    BITMAP *ecran_fin = NULL;
    int y_affiche = 40;
    int elimine = 1;
    int compteur_fin = nb_joueurs - 1;
    ecran_fin=load_bitmap("BITMAP/GAMEOVER.bmp",NULL);
    if (!ecran_fin)
    {
        allegro_message("pas pu trouver tour joueur/charger mon_image de fin.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    blit(ecran_fin, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);
    blit(buffer, screen,0,0,0,0, SCREEN_W, SCREEN_H);

    while (elimine != nb_joueurs - 1)
    {
        for (int i = 0; i < nb_joueurs; i++)
        {
            if (joueur[i].elimine == elimine)
            {
                classement[compteur_fin] = i;
                compteur_fin--; // Ce compteur est �gal � nb_joueur - 1 au d�but
                /// 1 - 4eme
                /// 2 - 3eme
                /// 3 - 2eme
                /// 4 - 1er
                /// (dans le cas des 4 joueurs)
            }
        }
        elimine++;
    }
    /// Test pour le joueur pas �limin�, qui sera premier
    for (int i = 0; i < nb_joueurs; i++)
    {
        if (joueur[i].elimine == 0) // le joueur i n'est pas �limin� car pas mort
        {
            classement[compteur_fin] = i;
        }
    }

    if (compteur_fin == 0)
    {
        for (int i = 0; i < nb_joueurs; i++)
        {
            if (joueur[i].vivant == 1)
            {
                ecran_fin=load_bitmap("BITMAP/GAMEOVER.bmp",NULL);
                classement[compteur_fin] = i;
            }
        }
        clear_bitmap(buffer);
        blit(ecran_fin, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);

        for (int i = nb_joueurs; i < 0; i--)
        {
            textprintf_ex(buffer,font,96,y_affiche,makecol(0,255,0), makecol(0,0,0),"%deme : Joueur %d", i, classement[i]);
            y_affiche += 10;
        }
        blit(buffer, screen,0,0,0,0, SCREEN_W, SCREEN_H);
    }
    // Apr�s ces �tapes, nous sommes cens� obtenir un tableau classement de la taille de nb_joueurs
    // qui contient la num�ro du joueur en fonction de sa place (ordre du tableau : case 0, premier)
}