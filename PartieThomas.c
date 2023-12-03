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


    float readTempsCycle()  // lecture du fichier temps_cycle.txt
{
    FILE* fichier = fopen("..\\+temps_cycle.txt", "r");

    if (!fichier)
    {
        fprintf(stderr, "Impossible d'ouvrir temps_cycle.txt\n");
        exit(EXIT_FAILURE);
    }

    float nombre1;
    while (fscanf(fichier, "%f", &nombre1) != EOF)
    {


    }

    fclose(fichier);

    return nombre1;
}

void AfficherTempsOp(struct Operation listeOp[100],int nmbOp)
{
    /// AFFICHAGE DE OPERATIONS ET DE LEUR TEMPS
    printf("\n\nListe des opérations et de leur temps d'execution\n\n");
    for(int i = 0 ; i < nmbOp ; i++)
    {
        printf("\n%d temps: %.2f",listeOp[i].id,listeOp[i].temps);
    }

}

    void opti2(struct Operation listeOp[100],int nmbOp,float tempscycle) /// Optimiser en fonction du temps de cycle et des precedences
{
    TriTopologique(listeOp, nmbOp);
    qsort(listeOp, nmbOp, sizeof(struct Operation), comparerByClassement);

    struct Station listeStation[15];

    int nmbStation = 0;
    int cmpOp = 0;


    while(cmpOp != nmbOp)
    {
        listeStation[nmbStation] = newStation();

        //printf("\nCréation station %d\n",nmbStation+1);
        //system("pause");

        for(int i = cmpOp ; i< nmbOp ; i++)
        {

            if(listeStation[nmbStation].tempsTotal + listeOp[i].temps < tempscycle)
            {
                listeStation[nmbStation].listeOp[listeStation[nmbStation].nmbOp] = listeOp[i];
                listeStation[nmbStation].nmbOp++;
                listeStation[nmbStation].tempsTotal = listeStation[nmbStation].tempsTotal + listeOp[i].temps;
                cmpOp++;

                //printf("\nAjout de l'operation %d\n",listeOp[i].id);
                //printf("\nTemps total de la station: %.2f\n",listeStation[nmbStation].tempsTotal);
                //system("pause");
            }
            else
            {
                //printf("\nStation pleine\n");
                //system("pause");
                nmbStation++;
                break;
            }
        }
    }

    /// AFFICHAGE DES STATION

    printf("\n\nNombre minimal de station : %d",nmbStation+1);

    printf("\nComposition des stations");

    for(int i = 0 ; i < (nmbStation+1) ; i++)
    {
        printf("\n\nStation %d : ",i+1);

        for(int k = 0 ; k< listeStation[i].nmbOp ; k++)
        {
            printf("%d ",listeStation[i].listeOp[k].id);
        }
        printf("\ntemps total d'execution : %.2fs ",listeStation[i].tempsTotal);
    }


}

void opti3(struct Operation listeOp[100],int nmbOp,float tempsCycle)  /// Optimiser en fonction des exclusion et du temps de cycle
{
    qsort(listeOp, nmbOp, sizeof(struct Operation), comparerById); /// TRIER LE TABLEAU EN ORDRE CROISSANT
    welshPowell(listeOp,nmbOp);

    qsort(listeOp, nmbOp, sizeof(struct Operation), comparerByColor); /// TRIER LE TABLEAU EN ORDRE CROISSANT



    struct Station listeStation[15];
    int nmbStation = 0;
    int cmpOp = 0;


     while(cmpOp != nmbOp)
    {
        listeStation[nmbStation] = newStation();

        //printf("\nCréation station %d\n",nmbStation+1);
        //system("pause");

        for(int i = cmpOp ; i< nmbOp ; i++)
        {
            int verif = 0;
            if(listeOp[i].couleur > 0)
            {
                if(listeOp[i].couleur != listeOp[i-1].couleur && listeStation[nmbStation].nmbOp !=0)
                {
                    verif = 1;
                    //printf("\nNouvelle couleur detecte");
                    //system("pause");
                }
            }
            if(listeStation[nmbStation].tempsTotal + listeOp[i].temps < tempsCycle && verif !=1)
            {
                listeStation[nmbStation].listeOp[listeStation[nmbStation].nmbOp] = listeOp[i];
                listeStation[nmbStation].nmbOp++;
                listeStation[nmbStation].tempsTotal = listeStation[nmbStation].tempsTotal + listeOp[i].temps;
                cmpOp++;

                //printf("\nAjout de l'operation %d\n",listeOp[i].id);
                //printf("\nTemps total de la station: %.2f\n",listeStation[nmbStation].tempsTotal);
                //system("pause");
            }
            else
            {
                //printf("\nCréation station d'une nouvelle sation\n");
                //system("pause");
                nmbStation++;
                break;
            }
        }


    }



    /// AFFICHAGE DES STATION

    printf("\n\nNombre minimal de station : %d",nmbStation+1);

    printf("\nComposition des stations");

    for(int i = 0 ; i < (nmbStation+1) ; i++)
    {
        printf("\n\nStation %d : ",i+1);

        for(int k = 0 ; k< listeStation[i].nmbOp ; k++)
        {
            printf("%d ",listeStation[i].listeOp[k].id);
        }
        printf("\ntemps total d'execution : %.2fs ",listeStation[i].tempsTotal);
    }

}


void optimiserStation(struct Operation listeOp[100],int nmbOp,float tmpCycle) /// MENU optimiser stations
{
    int choix=0;

    while(choix != 6)
    {
        printf("\n\n1-Optimiser en fonction des exclusions"); // opt1
        printf("\n2-Optimiser en fonction du temps de cycle et des precedences"); // opt2
        printf("\n3-Optimiser en fonction des exclusion et du temps de cycle"); // opt3
        printf("\n4-Optimiser en fonction des exclusion et des precedences");  //opt4
        printf("\n5-Optimiser en fonction de tout les parametres"); // opt5
        printf("\n6-Retour");

        printf("\n\nchoix: ");

        scanf("%d",&choix);


        switch (choix)
        {
            case 1:
                opti1(listeOp,nmbOp);
                break;
            case 2:
                opti2(listeOp,nmbOp,tmpCycle);
                break;
            case 3:
                opti3(listeOp,nmbOp,tmpCycle);
                break;
            case 4:
                opti4(listeOp,nmbOp);
                break;
            case 5:
                opti5(listeOp,nmbOp,tmpCycle);
                break;
            case 6:
                break;
            default:
                printf("\nChoix non valide.\n");
        }

    }
}

