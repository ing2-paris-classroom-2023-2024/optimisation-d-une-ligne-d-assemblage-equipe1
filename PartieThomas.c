Partie de code de Thomas

int comparerByClassement(const void *a, const void *b)   // fonction pour classer la liste d'peration en fonction de l'ordre dans le tri topologique
{
    return ((struct Operation *)b)->classement - ((struct Operation *)a)->classement;
}


int getOpById2(int id,struct Operation listeOp[100],int nmbOp)
{
    for(int i = 0 ; i< nmbOp ; i++)
    {
        if(listeOp[i].id == id)
            return i;
    }
}

void addTemps(int id, struct Operation listeOp[100],int nmbOp, float tmp)
{
    for(int i = 0 ; i < nmbOp ; i++)
    {
        if(id == listeOp[i].id)
            listeOp[i].temps = tmp;
    }
}

void readTempsOperation(struct Operation listeOp[100],int nmbOp)  // lecture du fichier operation.txt
{
    FILE* fichier = fopen("..\\operations.txt", "r");

    if (!fichier)
    {
        fprintf(stderr, "Impossible d'ouvrir operations.txt\n");
        exit(EXIT_FAILURE);
    }

    int nombre1;
    float tmp;
    while (fscanf(fichier, "%d %f", &nombre1, &tmp) != EOF)
    {
        addTemps(nombre1,listeOp,nmbOp,tmp);

    }

    fclose(fichier);

}
