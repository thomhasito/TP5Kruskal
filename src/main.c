#include <stdio.h>
#include "Graphe.h"
#include "Kruskal.h"
#include "prim.h"

int main() {

    int sommetInitial;

    Graphe* graphe = Graph_LoadFromFile("../graphe1_TP3.txt",1);

    Graphe* arbre = Graph_LoadFromFile("../graphe1_TP3.txt",0);

    pArc* tabArete = (pArc*) malloc(graphe->taille * sizeof(pArc));

    InitKruskal(graphe,tabArete);

    kruskal(arbre, tabArete);

    free(tabArete);

    Prim(arbre,graphe,&sommetInitial);

//    afficherArbre(arbre);

    return 0;
}
