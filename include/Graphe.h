#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

enum SommetCouleur {
    UNEXPLORED,
    EXPLORING,
    EXPLORED
};

/* Structure d'un arc*/
struct Arc
{
    int sommet1;
    int sommet0;
    int valeur; /// stocke si l'arc a dejé été parcouru ou non
    int ponderation; /// poids de l'arc
    struct Arc* arc_suivant;
};

/* Alias de pointeur sur un Arc */
typedef struct Arc* pArc;

/* Structure d'un sommet1*/
struct Sommet
{
    struct Arc* arc;
    // numéro du sommet1.
    int id;
    // pointeur vers le sommet1 précédent.
    struct Sommet *predecesseur;

    // distance du sommet1
    int numCC;

    enum SommetCouleur couleur;
};

/* Alias de pointeur sur un Sommet */
typedef struct Sommet* pSommet;

/* Alias d'un Graphe */
typedef struct Graphe
{
    int taille;
    int orientation;
    int ordre;
    int distance;
    pSommet* pSommet;
} Graphe;

/// Alloue et retourne un pointeur vers une structure graphe initalisée
Graphe* Graphe_AllocGraphe(int ordre);

/// Lit un graphe depuis un fichier texte
Graphe *Graph_LoadFromFile(char *nomFichier, int arete);

/// Crée un arc pointant entre les deux ID de sommets spécifiés avec la pondération specifiée.
pSommet* Graph_CreateArc(pSommet* sommet, int s1, int s2, int ponderation);

/// Affichage des successeurs du sommet1 spécifié.
void Graph_PrintSucesseurs(pSommet * sommet, int num);

/// Affiche le contenu du graphe + les successeurs de chaque sommet1.
void Graph_Print(Graphe* graphe);

/// Affiche tous les chemins qui partent du sommet1 actuel.
void Graphe_PrintPaths(Graphe *graphe, int sommetActuel);

void Graphe_PrintPathsRecursive(Graphe *graphe, pSommet sommetActuel);

void cheminDjikstra(Graphe *graphe, int sommet);

void Graphe_DisplayArcs(Graphe* graphe);

#endif // GRAPHE_H_INCLUDED