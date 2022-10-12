#include "prim.h"
#include "Graphe.h"
#include <time.h>
#include "limits.h"

void Prim(Graphe* arbre,Graphe * graphe,int* sommetInitial){
    srand(time(NULL));

    for (int i = 0; i < arbre->ordre; ++i) {   //initialisation  de l arbre
        arbre->pSommet[i]->couleur = UNEXPLORED;
        arbre->pSommet[i]->predecesseur = NULL;
    }

    *sommetInitial = rand() % (arbre->ordre);
    printf("Nous allons derouler l'algorithme de Prim a partir du sommet %d (choisi aleatoirement)\n",*sommetInitial);
    // choix du sommet initial aleatoirement

    arbre->pSommet[*sommetInitial]->couleur = EXPLORED;
    int sommetMarques = 1;
    int poidsTotal = 0;
    pSommet s1,s2;

    while(sommetMarques < arbre->ordre){
        int distanceMin = INT_MAX;
        for (int i = 0; i < arbre->ordre; ++i) {
            if(arbre->pSommet[i]->couleur == EXPLORED){
                pArc arc = graphe->pSommet[i]->arc;  //on reprend les arcs du graphe complet
                while (arc){
                    if(arbre->pSommet[arc->sommet1]->couleur == UNEXPLORED){
                        if(arc->ponderation < distanceMin){ //recherche de lka distance minimale parmi les arcs de sommets marques
                            distanceMin = arc->ponderation;
                            s1 = arbre->pSommet[i];
                            s2 = arbre->pSommet[arc->sommet1];
                        }
                    }
                    arc = arc->arc_suivant;
                }
            }
        }

        poidsTotal += distanceMin;
        arbre->pSommet = Graph_CreateArc(arbre->pSommet,s1->id,s2->id,distanceMin);
        s2->predecesseur = s1; //on ajoute l arc a l arbre s1 predecesseur de s2
        s2->couleur = EXPLORED;
        sommetMarques ++;
        printf("%d--->%d (poidsArc:%d -> poids total %d)\n",s1->id,s2->id,distanceMin,poidsTotal);
    }
    afficherArbre(arbre,arbre->pSommet[2]);

    printf("Le poids total de l'arbre couvrant est de %d.\n",poidsTotal);

}

void afficherArbreRecur(Graphe* arbre,pSommet sommet){
    if (sommet->predecesseur == NULL) {
        printf("%d", sommet->id);
        printf("\n\r");
        return;
    } else {
        printf("%d <-- ", sommet->id);
        afficherArbreRecur(arbre, sommet->predecesseur);
    }
}

void afficherArbre(Graphe* g, pSommet sommet){
    for (int i = 0; i < g->ordre; ++i) {
        afficherArbreRecur(g,g->pSommet[i]);
    }
}
