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


void TriTopologique(struct Operation listeOp[100],int nmbOp)  /// algo tri topologique ( voir vidéo word)
{
    for(int i = 0 ; i< nmbOp ; i++)
    {
        listeOp[i].couleur2 = 0;
        listeOp[i].pred = -1;
    }

    int classement = 0;
    while(verifAllColored2(listeOp,nmbOp) == 1)
    {
        int jeton = rand()%nmbOp;
        int depart = jeton;

        //printf("\non part de %d\n",listeOp[depart].id);
        //system("pause");


        int out = 0;
        while(out == 0 && listeOp[jeton].couleur2 != 2)
        {
            listeOp[jeton].couleur2 = 1;
            int find = 0;
            do
            {
                find = 0;
                for(int i = 0 ; i < listeOp[jeton].nmbS ; i++)
                {
                    int suiv = getOpById2(listeOp[jeton].suivant[i],listeOp,nmbOp);
                    if(listeOp[suiv].couleur2 == 0)
                    {
                        listeOp[suiv].pred = listeOp[jeton].id;
                        jeton = suiv;
                        listeOp[jeton].couleur2 = 1;
                        find = 1;

                        //printf("\non decouvre %d\n",listeOp[jeton].id);
                        //system("pause");


                        break;
                    }
                }
            }
            while(find == 1);

            //printf("\n%d n'as pas de sortie\n",listeOp[jeton].id);
            //system("pause");

            listeOp[jeton].couleur2 = 2;
            listeOp[jeton].classement = classement;
            //printf("\n Classement de %d : %d\n",listeOp[jeton].id,classement);
            //system("pause");

            classement++;

            if(jeton == depart)
            {
                out = 1;

                //printf("\n Nous sommes revenu au point de depart\n",listeOp[jeton].id);
                //system("pause");

            }
            else
            {
                jeton = getOpById2(listeOp[jeton].pred,listeOp,nmbOp);
                /*
                printf("\non revient a %d\n",listeOp[jeton].id);
                system("pause");
                */
            }




        }
    }

}
