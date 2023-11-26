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
