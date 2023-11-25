void trouverRacine(struct Operation listeOp[100],int nmbOp) // permet de marquer les operations qui n'ont pas de arc entrant ( pas de precedents)
{
    for(int i = 0 ; i< nmbOp ; i++)
    {
        for(int k = 0 ; k< nmbOp ; k++)
        {
            for(int l = 0 ; l < listeOp[k].nmbS ; l++) // Parcours de tous les successeurs de l'opération actuelle
            {
                if(getOpById(listeOp[k].suivant[l],listeOp,nmbOp).id == listeOp[i].id) // Vérifie si l'opération actuelle est un successeur de l'opération en cours
                {
                    listeOp[i].racine = 1; // Si l'opération actuelle a un successeur alors on met racine à 1
                }
            }

        }
    }
}


int DFS(struct Operation listeOp[100],int nmbOp,struct Operation depart, struct Operation arrive)
{
    struct Operation pile[15];
    int taillePile = 0;
    pile[0] = depart;


    do
    {
        int act = taillePile;
        //printf("\non analyse les suivant de %d , %d suivants\n",pile[act].id,pile[act].nmbS);
        //system("pause");

        for(int i = 0 ; i < pile[act].nmbS ; i++) // Parcourir les successeurs du nœud actuel
        {
            //printf("\non ajoute %d\n",pile[act].suivant[i]);
            //system("pause");
            if(pile[act].suivant[i] == arrive.id)
            {
                return 1;
            }
            struct Operation suivant = getOpById(pile[act].suivant[i],listeOp,nmbOp); // Récupération du nœud suivant à partir de son identifiant
            
            if(suivant.placed == 1) //nœud suivant n'a pas déjà été visité, l'ajouter à la pile
            {
                pile[taillePile] = suivant;
                taillePile++;
            }
        }
        taillePile--;


    }
    while(taillePile > -1);

    return 0;
}

