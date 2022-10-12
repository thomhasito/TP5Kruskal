#include "Kruskal.h"
#include "Graphe.h"

void InitKruskal(Graphe* g,pArc* tab){
    int num=0;
    for (int i = 0; i < g->ordre; ++i) {   //remplir tableau d'arete
        pArc arc = g->pSommet[i]->arc;
        pSommet sommet = g->pSommet[i];
        while (arc){
            pSommet successeur = g->pSommet[arc->sommet1];
            if(successeur->couleur == UNEXPLORED){  //on ajoute la condition si le successeur n est pas marque
                tab[num] = arc;                     // pour eviter de prendre l arete en double(sens inverse)
                num++;
            }
            arc=arc->arc_suivant;
        }
        sommet->couleur = EXPLORED;
    }
    for (int i = 0; i < g->taille-1; ++i) {     //tri du tableau
        for (int j = 0; j < g->taille-1; ++j) {
            if(tab[j]->ponderation > tab[j + 1]->ponderation){
                pArc temp;
                temp=tab[j + 1];
                tab[j + 1]=tab[j];
                tab[j]=temp;
            }
        }
    }
}

void kruskal(Graphe* g,pArc* tab){
    printf("Nous allons derouler l'algorithme de Kruskal a partir du sommet 0\n");
    int nbArete = 0;
    for (int i = 0; i < g->ordre; ++i) { //initialisation des numCC
        g->pSommet[i]->numCC = i;
        g->pSommet[i]->couleur = UNEXPLORED;
    }
    int poidsTotal = 0;
    int numArete=0;
    while(nbArete < g->ordre-1){
        if(g->pSommet[tab[numArete]->sommet0]->numCC != g->pSommet[tab[numArete]->sommet1]->numCC){
            g->pSommet = Graph_CreateArc(g->pSommet, tab[numArete]->sommet0, tab[numArete]->sommet1, tab[numArete]->ponderation); //creer les aretes de l'arbre
            int numCC = g->pSommet[tab[numArete]->sommet1]->numCC;
            for (int i = 0; i < g->ordre; ++i) {
                if(g->pSommet[i]->numCC == numCC){
                    g->pSommet[i]->numCC = g->pSommet[tab[numArete]->sommet0]->numCC; //actualisation des numCC pour eviter les cycles
                }
            }
            poidsTotal += tab[numArete]->ponderation;
            nbArete+=1;
            printf("%d",g->pSommet[tab[numArete]->sommet0]->id);
            for (int i = 0; i < g->ordre; ++i) {
                if(g->pSommet[i]->numCC == g->pSommet[tab[numArete]->sommet0]->numCC && g->pSommet[i] != g->pSommet[tab[numArete]->sommet0]){
                    printf("--> %d",g->pSommet[i]->id);
                }
            }
            printf("\n");
        }
        numArete++;
    }
    printf("Le poids total de l'arbre couvrant est de %d.\n\n",poidsTotal);
}



