
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



struct Operation newOperation(int id);
struct Station newStation();
void addContrainte(struct Operation *op, int i);
int addOperation(struct Operation listeOp[100], int nmbOp, int n1, int n2);
int readExclusion(struct Operation listeOp[100], int nmbOp);
int comparerById(const void *a, const void *b);
int comparerByColor(const void *a, const void *b);
int comparerByDegres(const void *a, const void *b);
int comparerByClassement(const void *a, const void *b);
int verifAllColored(struct Operation listeOp[100], int nmbOp);
struct Operation getOpById(int id, struct Operation listeOp[100], int nmbOp);
void trouverRacine(struct Operation listeOp[100], int nmbOp);
int getOpById2(int id, struct Operation listeOp[100], int nmbOp);
void welshPowell(struct Operation listeOp[100], int nmbOp);
void addTemps(int id, struct Operation listeOp[100], int nmbOp, float tmp);
void addSuivant(int id1, int id2, struct Operation listeOp[100], int nmbOp);
void readTempsOperation(struct Operation listeOp[100], int nmbOp);
void readPrecedences(struct Operation listeOp[100], int nmbOp);
int verifAllColored2(struct Operation listeOp[100], int nmbOp);
void TriTopologique(struct Operation listeOp[100], int nmbOp);
float readTempsCycle();
void afficherExclusions(struct Operation listeOp[100], int nmbOp);
void afficherPrecedences(struct Operation listeOp[100], int nmbOp);
void AfficherTempsOp(struct Operation listeOp[100], int nmbOp);
void afficherData(struct Operation listeOp[100], int nmbOp);
void opti1(struct Operation listeOp[100], int nmbOp);
void opti2(struct Operation listeOp[100], int nmbOp, float tempscycle);
void opti3(struct Operation listeOp[100], int nmbOp, float tempsCycle);
int verifAllplaced(struct Operation listeOp[100], int nmbOp);
int DFS(struct Operation listeOp[100], int nmbOp, struct Operation depart, struct Operation arrive);
void opti4(struct Operation listeOp[100], int nmbOp);
void opti5(struct Operation listeOp[100], int nmbOp, float tempsCycle);
void optimiserStation(struct Operation listeOp[100], int nmbOp, float tmpCycle);


