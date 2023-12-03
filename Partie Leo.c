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

int comparerByColor(const void *a, const void *b)   // fonction pour classer la liste d'peration en fonction de la couleur pour welsh powell
{
    return ((struct Operation *)a)->couleur - ((struct Operation *)b)->couleur;
}

void welshPowell(struct Operation listeOp[100],int nmbOp)  // Algo de welsh powell (voir vidéo dans le word)
{

    qsort(listeOp, nmbOp, sizeof(struct Operation), comparerById); /// TRIER LE TABLEAU EN ORDRE DECROISSANT EN FONCTION DE l'ID

    for(int i = 0 ; i < nmbOp ; i++)
    {
        listeOp[i].couleur = -1;
    }
 int C = 0;
    while(verifAllColored(listeOp,nmbOp) == 1)
    {
        for(int i = 0 ; i< nmbOp ; i++)
        {
            if(listeOp[i].couleur == -1)
            {
                int verif = 0;
                for(int k = 0 ; k < listeOp[i].nmbC ; k++)
                {
                    struct Operation adjacent = getOpById(listeOp[i].contrainte[k],listeOp,nmbOp);
                    if(adjacent.couleur == C)
                        verif = 1;
                }
                if(verif == 0)
                    listeOp[i].couleur = C;

            }
        }
        C++;
    }
}

void opti1(struct Operation listeOp[100],int nmbOp)  /// Optimiser en fonction des exclusions
{
    qsort(listeOp, nmbOp, sizeof(struct Operation), comparerById); /// TRIER LE TABLEAU EN ORDRE CROISSANT

    welshPowell(listeOp,nmbOp);

    int max = 0;

    for(int i = 0 ; i< nmbOp ; i++)
    {
        if(listeOp[i].couleur > max)
            max = listeOp[i].couleur;
    }
  printf("\n\nNombre minimal de station : %d",max+1);

    printf("\nComposition des stations");

    for(int i = 0 ; i < (max+1) ; i++)
    {
        printf("\n\nStation %d : ",i+1);
        for(int k = 0 ; k< nmbOp ; k++)
        {
            if(listeOp[k].couleur == i)
            {
                printf("%d ",listeOp[k].id);
            }
        }
    }
}

int verifAllColored(struct Operation listeOp[100],int nmbOp)  // fonction utilisé pour welsh powell pour verifier si toutes les operations sont colloré
{
    int verif = 0;
    for(int i  = 0 ; i< nmbOp ; i++)
    {
        if(listeOp[i].couleur == -1)
            verif = 1;
    }
    return verif;
}

struct Operation getOpById(int id,struct Operation listeOp[100],int nmbOp)  // permet de récupérer une operation dans la liste des operation avec son id
{
    for(int i = 0 ; i< nmbOp ; i++)
    {
        if(listeOp[i].id == id)
            return listeOp[i];
    }
}

void afficherExclusions(struct Operation listeOp[100],int nmbOp)
{

    qsort(listeOp, nmbOp, sizeof(struct Operation), comparerById); /// TRIER LE TABLEAU EN ORDRE CROISSANT
    /// AFFICHAGE DE OPERATIONS ET DE LEURS CONTRAINTES

    printf("\n\nListe des opérations et de leurs exclusions\n\n");
    for(int i = 0 ; i < nmbOp ; i++)
    {
