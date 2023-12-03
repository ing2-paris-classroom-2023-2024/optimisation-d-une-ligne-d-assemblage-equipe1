
#include "header.h"


int main()
{

    srand((unsigned int)time(NULL));

    struct Operation listeOp[100];  // liste des opération
    int nmbOp = 0; // au debut la liste est vide

    /// CHARGEMENT DES DATA


    printf("chargement de exclusion.txt ...\n");

    nmbOp = readExclusion(listeOp,nmbOp);



    /// RAJOUTER LES OPERATION MANQUANTE

    int maximum = listeOp[nmbOp -1].id;
    int taille = nmbOp;

    for(int i = 1; i < maximum ; i++)
    {
        int verif = 0;
        for(int k = 0 ; k < taille ; k++ )
        {
            if(listeOp[k].id == i)
                verif = 1;
        }

        if(verif == 0)
        {
            listeOp[nmbOp] = newOperation(i);
            nmbOp++;
        }
    }

    printf("\nchargement de precedences.txt ...\n");
    readPrecedences(listeOp, nmbOp);

    printf("\nchargement de operations.txt ...\n");
    readTempsOperation(listeOp, nmbOp);


    printf("\nchargement de temps_cycle.txt ...\n");
    float tempsCycle = readTempsCycle();


    printf("\nNombre d'operation : %d\nTemps de cycle : %.2fs",nmbOp,tempsCycle);


    int choix = 0;

    while(choix != 3)
    {
        printf("\n\n1-Afficher les donnees\n2-Optimisation des stations\n3-Quitter");

        printf("\n\nChoix: ");

        scanf("%d",&choix);

        switch (choix)
        {
            case 1:
                afficherData(listeOp,nmbOp);
                break;
            case 2:
                optimiserStation(listeOp,nmbOp,tempsCycle);
                break;
            case 3:
                return 0;
                break;
            default:
                printf("Choix non valide.\n");
        }

    }

    return 0;
} 
