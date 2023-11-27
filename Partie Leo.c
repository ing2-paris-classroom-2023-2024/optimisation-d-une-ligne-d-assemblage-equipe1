int addOperation(struct Operation listeOp[100],int nmbOp, int n1, int n2) // ajout d'une operation a la liste des operation 
{
    int verif1 = 0;
    int verif2 = 0;


    for(int i = 0 ; i < nmbOp ; i++)
    {

        if(listeOp[i].id == n1)  // on verifie si l'operation est deja ajoute a la liste
        {
            verif1 = 1;
            listeOp[i].contrainte[listeOp[i].nmbC] = n2;
            listeOp[i].nmbC++;

        }
        if(listeOp[i].id == n2)
        {
            verif2 = 1;
            listeOp[i].contrainte[listeOp[i].nmbC] = n1;
            listeOp[i].nmbC++;

        }
    }
if(verif1 == 0)  // si elle n'est pas ajouté on la rajoute
    {
        listeOp[nmbOp] = newOperation(n1);
        listeOp[nmbOp].contrainte[listeOp[nmbOp].nmbC] = n2;
        listeOp[nmbOp].nmbC++;
        nmbOp++;

    }

    if(verif2 == 0)
    {
        listeOp[nmbOp] = newOperation(n2);
        listeOp[nmbOp].contrainte[listeOp[nmbOp].nmbC] = n1;
        listeOp[nmbOp].nmbC++;
        nmbOp++;
    }


    return nmbOp;

}

int readExclusion(struct Operation listeOp[100],int nmbOp)  // chargement du fichier exclusions.txt
{
    FILE* fichier = fopen("..\\exclusions.txt", "r");

    if (!fichier)
    {
        fprintf(stderr, "Impossible d'ouvrir exclusions.txt\n");
        exit(EXIT_FAILURE);
    }
 int nombre1, nombre2;
    while (fscanf(fichier, "%d %d", &nombre1, &nombre2) != EOF)
    {

        nmbOp = addOperation(listeOp,nmbOp,nombre1,nombre2);
    }

    fclose(fichier);

    return nmbOp;

}
