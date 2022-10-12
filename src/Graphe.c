#include "Graphe.h"

// Ajouter l'arete entre les maillons s1 et s2 du graphe
pSommet *Graph_CreateArc(pSommet *sommet, int s1, int s2, int ponderation) {

    pArc Newarc = (pArc) malloc(sizeof(struct Arc));
    Newarc->arc_suivant = NULL;
    Newarc->ponderation = ponderation;
    Newarc->valeur = UNEXPLORED;
    Newarc->sommet0 = s1;
    Newarc->sommet1 = s2;

    if (sommet[s1]->arc == NULL) {
        sommet[s1]->arc = Newarc;
        return sommet;
    } else {
        pArc temp = sommet[s1]->arc;
        while (temp->arc_suivant)
            temp = temp->arc_suivant;

        temp->arc_suivant = Newarc;
        return sommet;
    }
}

void Graph_PrintSucesseurs(pSommet *sommet, int num) {
    printf(" sommet1 %d :\n", num);

    pArc arc = sommet[num]->arc;

    while (arc != NULL) {
        printf("%d ", arc->sommet1);
        arc = arc->arc_suivant;
    }
}

void Graph_Print(Graphe *graphe) {
    printf("Graphe\n");

    if (graphe->orientation)
        printf("Oriente\n");
    else
        printf("Non oriente\n");

    printf("Ordre = %d\n", graphe->ordre);

    printf("Listes D'adjacence :\n");

    for (int i = 0; i < graphe->ordre; i++) {
        Graph_PrintSucesseurs(graphe->pSommet, i);
        printf("\n");
    }
}


// creer le graphe
Graphe *Graphe_AllocGraphe(int ordre) {
    Graphe *Newgraphe = (Graphe *) malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet *) malloc(ordre * sizeof(pSommet));

    for (int i = 0; i < ordre; i++) {
        Newgraphe->pSommet[i] = (pSommet) malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->id = i;
        Newgraphe->pSommet[i]->couleur = UNEXPLORED;
        Newgraphe->pSommet[i]->arc = NULL;
    }
    return Newgraphe;
}


/* La construction du reseau peut se faire a partir d'un fichier dont le nom est passe en parametre
Le fichier contient : ordre, taille,orientation (0 ou 1)et liste des arcs + la ponderation de l'arc*/
Graphe *Graph_LoadFromFile(char *nomFichier, int arete) {
    Graphe *graphe;
    FILE *ifs = fopen(nomFichier, "r");
    int taille, orientation, ordre, s1, s2;

    if (!ifs) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    fscanf(ifs, "%d", &ordre);

    graphe = Graphe_AllocGraphe(ordre); // creer le graphe d'ordre maillons

    fscanf(ifs, "%d", &taille);
    fscanf(ifs, "%d", &orientation);

    graphe->orientation = orientation;
    graphe->ordre = ordre;
    graphe->taille = taille;

    // creer les aretes du graphe
    if(arete){
        for (int i = 0; i < taille; ++i) {
            int ponderation = 0;
            fscanf(ifs, "%d%d%d", &s1, &s2, &ponderation);
            graphe->pSommet = Graph_CreateArc(graphe->pSommet, s1, s2, ponderation);

            if (!orientation)
                graphe->pSommet = Graph_CreateArc(graphe->pSommet, s2, s1, ponderation);
        }
    }
    for (int i = 0; i < graphe->ordre; ++i) {
        graphe->pSommet[i]->predecesseur = NULL;
    }
    return graphe;
}

void Graphe_PrintPathsRecursive(Graphe *graphe, pSommet sommetActuel) {
    if (sommetActuel->predecesseur == NULL) {
        printf("%d", sommetActuel->id);
        return;
    } else {
        printf("%d <-- ", sommetActuel->id);
        Graphe_PrintPathsRecursive(graphe, sommetActuel->predecesseur);
    }
}

void Graphe_PrintPaths(Graphe *graphe, int sommetActuel) {
    for (int i = 0; i < graphe->ordre; ++i) {
        if (i == sommetActuel)
            continue;

        if (!graphe->pSommet[i]->predecesseur)
            continue;

        Graphe_PrintPathsRecursive(graphe, graphe->pSommet[i]);
        printf("\n\r");
    }
}


void cheminDjikstra(Graphe *graphe, int sommet) {
    Graphe_PrintPathsRecursive(graphe, graphe->pSommet[sommet]);
    printf("\n\r");
}

void Graphe_DisplayArcs(Graphe* graphe) {
    for (int i = 0; i < graphe->ordre; ++i) {
        pArc arc = graphe->pSommet[i]->arc;
        while (arc) {
            printf("Arc %d --> %d (%d) \n", graphe->pSommet[i]->id, arc->sommet1, arc->ponderation);
            arc = arc->arc_suivant;
        }
    }
}