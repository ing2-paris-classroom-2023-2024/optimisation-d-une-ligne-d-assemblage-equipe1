
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Operation
{

    float temps; // temps d'execution de l'operation
    int id;   // numéro de l'operation
    int contrainte[10];  // liste de operation exclu
    int nmbC;  // nombre d'operation exclu
    int couleur;  // WELSH POWELL COLORATION
    int suivant[15]; // liste des arc sortant
    int nmbS;  // nombre d'arc sortant
    int couleur2;  // TRI TOPOLOGIQUE
    int classement; // ordre pour le tri topologique
    int pred; // precedent pour le tri topologique
    int racine; // 1 = operation avec des precedent  0 = operation sans precedent
    int placed;  // pour opti4 et opti5

};

struct Station
{
    float tempsTotal;
    struct Operation listeOp[30];
    int nmbOp;
};

struct Operation newOperation(int id){  // creation d'une operation

    struct Operation op;
    op.couleur =-1;
    op.nmbC = 0;
    op.id = id;
    op.temps = 0;
    op.nmbS = 0;
    op.couleur2 = 0;
    op.pred = -1;
    op.racine = 0;

    return op;
};


struct Station newStation() // creation d'une station
{
    struct Station St;
    St.nmbOp = 0;
    St.tempsTotal =0;

};

