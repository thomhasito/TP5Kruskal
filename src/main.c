#include <stdio.h>
#include "Graphe.h"
#include "Kruskal.h"
#include "prim.h"

int main() {

    int sommetInitial;

    Graphe* graphe = Graph_LoadFromFile("../graphe1_TP3.txt",1); // charger graphe complet

    Graphe* arbre = Graph_LoadFromFile("../graphe1_TP3.txt",0); //charger arbre sans arete

    pArc* tabArete = (pArc*) malloc(graphe->taille * sizeof(pArc)); //creation tableau d'arete

    InitKruskal(graphe,tabArete);

    kruskal(arbre, tabArete);

    free(tabArete);//liberation du tableau

    Prim(arbre,graphe,&sommetInitial);

//    afficherArbre(arbre);

    return 0;
}
