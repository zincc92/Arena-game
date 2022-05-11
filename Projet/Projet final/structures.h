#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#include <allegro.h>
#define TEMPS_TOUR 15
#define NB_SORTS 4
#define DIRECTIONS 4
#define NB_BITMAPS_D 4
#define NB_BITMAPS_R 4

typedef struct Acteur
{
    int x; // depart du tracage de l'image (Ex du guerrier : En 0 pour le premier mvt, en 49 pour le second...)
    int y; // depart du tracage de l'image (Ex du guerrier : reste � 0 car meme taille d'image pour 1 direction)
    int tx; // dimension de la taille de l'acteur en x (49)
    int ty; // dimension de la taille de l'acteur en y (64)
}t_acteurs;

typedef struct bloc
{
    int red;
    int green;
    int blue;
    int x_bloc;
    int y_bloc;
    int accessible;
    int occuper;
} t_bloc;

typedef struct sorts
{
    int portee_min;
    int portee_max;
    int cout_pa;
    int degats_min;
    int degats_max;
    int chance;
    BITMAP* logo;
    BITMAP* animation_sort[4];
    BITMAP* description;
}t_sort;

typedef struct classes
{
    int attaque;
    BITMAP *logo_attaque;
    BITMAP *respiration[NB_BITMAPS_R];
    BITMAP *deplacement[DIRECTIONS][NB_BITMAPS_D];
    t_sort spell[NB_SORTS];
}t_classe;


typedef struct Players
{
    char pseudo[20];
    int id_classe;
    BITMAP* skin;
    int x;
    int y;
    int nb_pm;
    int pv;
    int pm;
    int pa;
    int statut;
    int vivant;
    int red;
    int green;
    int blue;
    t_classe classe;
}t_joueur;


#endif // STRUCTURES_H_INCLUDED
