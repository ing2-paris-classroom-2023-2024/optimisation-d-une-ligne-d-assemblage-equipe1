
struct Operation getOpById(int id,struct Operation listeOp[100],int nmbOp)  /// permet de récupérer une operation dans la liste des operation avec son id
{
    for(int i = 0 ; i< nmbOp ; i++) /// Parcours de la liste des opérations
    {
        if(listeOp[i].id == id) /// Vérifie si l'id de l'opération actuelle correspond à l'id recherché.
            return listeOp[i];
    }
}


int getOpById2(int id,struct Operation listeOp[100],int nmbOp)
{
    for(int i = 0 ; i< nmbOp ; i++)
    {
        if(listeOp[i].id == id)
            return i;
    }
}



void trouverRacine(struct Operation listeOp[100],int nmbOp) /// permet de marquer les operations qui n'ont pas de arc entrant ( pas de precedents)
{
    for(int i = 0 ; i< nmbOp ; i++)
    {
        for(int k = 0 ; k< nmbOp ; k++)
        {
            for(int l = 0 ; l < listeOp[k].nmbS ; l++) /// Parcours de tous les successeurs de l'opération actuelle
            {
                if(getOpById(listeOp[k].suivant[l],listeOp,nmbOp).id == listeOp[i].id) /// Vérifie si l'opération actuelle est un successeur de l'opération en cours
                {
                    listeOp[i].racine = 1; /// Si l'opération actuelle a un successeur alors on met racine à 1
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
        ///printf("\non analyse les suivant de %d , %d suivants\n",pile[act].id,pile[act].nmbS);
        ///system("pause");

        for(int i = 0 ; i < pile[act].nmbS ; i++) /// Parcourir les successeurs du nœud actuel
        {
            ///printf("\non ajoute %d\n",pile[act].suivant[i]);
            ///system("pause");
            if(pile[act].suivant[i] == arrive.id)
            {
                return 1;
            }
            struct Operation suivant = getOpById(pile[act].suivant[i],listeOp,nmbOp); /// Récupération du nœud suivant à partir de son identifiant
            
            if(suivant.placed == 1) ///nœud suivant n'a pas déjà été visité, l'ajouter à la pile
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


void addSuivant(int id1, int id2,struct Operation listeOp[100],int nmbOp)
{
    for(int i = 0 ; i < nmbOp ; i++)
    {
        if(listeOp[i].id == id1)
        {
            for(int k = 0 ; k < nmbOp ; k++)
            {
                if(listeOp[k].id == id2)
                {
                    listeOp[i].suivant[listeOp[i].nmbS] = id2;
                    listeOp[i].nmbS++;
                }
            }
        }
    }
}



void readPrecedences(struct Operation listeOp[100],int nmbOp)  /// lecture du fichier precedences.txt
{
    FILE* fichier = fopen("precedences.txt", "r");

    if (!fichier)
    {
        fprintf(stderr, "Impossible d'ouvrir precedences.txt\n");
        exit(EXIT_FAILURE);
    }

    int nombre1;
    int nombre2;

    while (fscanf(fichier, "%d %d", &nombre1, &nombre2) != EOF)
    {

        addSuivant(nombre1,nombre2,listeOp,nmbOp);

    }

    fclose(fichier);

}


int comparerById(const void *a, const void *b) /// Fonction de comparaison pour trier en fonction de l'identifiant
{ 
    return ((struct Operation *)a)->id - ((struct Operation *)b)->id;
}

int verifAllColored2(struct Operation listeOp[100],int nmbOp)  /// verifier si tous les operations sont coloré
{
    int verif = 0;
    for(int i  = 0 ; i< nmbOp ; i++)
    {
        if(listeOp[i].couleur2 == 0)
            verif = 1;
    }
    return verif;
}



void TriTopologique(struct Operation listeOp[100], int nmbOp)  /// Algorithme de tri topologique
{
    /// Initialisation des opérations
    for(int i = 0; i < nmbOp; i++)
    {
        listeOp[i].couleur2 = 0;  /// Initialise la couleur à 0 (non traité)
        listeOp[i].pred = -1;     /// Initialise le prédécesseur à -1 (pas de prédécesseur)
    }

    int classement = 0;  /// Initialise le classement à 0
    while(verifAllColored2(listeOp, nmbOp) == 1)  /// Continue tant que toutes les opérations ne sont pas colorées
    {
        int jeton = rand() % nmbOp;  /// Choix aléatoire d'une opération comme point de départ
        int depart = jeton;

        /// Débogage : Affichage du point de départ
        ///printf("\nOn part de %d\n", listeOp[depart].id);
        ///system("pause");

        int out = 0;
        while(out == 0 && listeOp[jeton].couleur2 != 2)  /// Boucle tant que l'opération actuelle n'est pas terminée
        {
            listeOp[jeton].couleur2 = 1;  /// Marque l'opération comme en cours de traitement

            int find = 0;
            do
            {
                find = 0;

                /// Parcours des successeurs de l'opération actuelle
                for(int i = 0; i < listeOp[jeton].nmbS; i++)
                {
                    int suiv = getOpById2(listeOp[jeton].suivant[i], listeOp, nmbOp);

                    /// Si le successeur n'est pas encore traité
                    if(listeOp[suiv].couleur2 == 0)
                    {
                        listeOp[suiv].pred = listeOp[jeton].id;
                        jeton = suiv;
                        listeOp[jeton].couleur2 = 1;  /// Marque le successeur comme en cours de traitement
                        find = 1;

                        /// Débogage : Affichage de la découverte d'une nouvelle opération
                        ///printf("\nOn découvre %d\n", listeOp[jeton].id);
                        ///system("pause");

                        break;
                    }
                }
            }
            while(find == 1);

            /// Débogage : Affichage si l'opération n'a pas de sortie
            ///printf("\n%d n'a pas de sortie\n", listeOp[jeton].id);
            ///system("pause");

            listeOp[jeton].couleur2 = 2;  /// Marque l'opération comme terminée
            listeOp[jeton].classement = classement;  /// Affecte le classement à l'opération
            classement++;

            if(jeton == depart)
            {
                out = 1;

                /// Débogage : Affichage si on est revenu au point de départ
                ///printf("\nNous sommes revenus au point de départ\n", listeOp[jeton].id);
                ///system("pause");
            }
            else
            {
                jeton = getOpById2(listeOp[jeton].pred, listeOp, nmbOp);
                /*
                /// Débogage : Affichage du retour à une opération précédente
                printf("\nOn revient à %d\n", listeOp[jeton].id);
                system("pause");
                */
            }
        }
    }
}


void opti4(struct Operation listeOp[100], int nmbOp) { /// optimisation en fonction des exclusions et précédences
    for (int i = 0; i < nmbOp; i++) {
        listeOp[i].placed = 0;
    }
/// pré-traitement
    qsort(listeOp, nmbOp, sizeof(struct Operation), comparerById);
    welshPowell(listeOp, nmbOp);
    TriTopologique(listeOp, nmbOp);
    trouverRacine(listeOp, nmbOp);

    qsort(listeOp, nmbOp, sizeof(struct Operation), comparerByClassement);

/// Initialisation des stations
    struct Station listeStation[15]; 
    int nmbStation = 0; 
    int cmpOp = 0;

/// Placement des opérations dans les stations
    while (cmpOp != nmbOp) {
        
    int couleur = -1;

    /// Parcours de la liste des opérations
    for (int i = 0; i < nmbOp; i++) {
       
        if (listeOp[i].placed == 0) /// Vérifie si l'opération n'a pas encore été placée 
        {
            
            if (couleur == -1 || listeOp[i].couleur == couleur) /// Vérifie si la couleur n'a pas encore été attribuée ou si elle correspond à la couleur de l'opération en cours
            {
                
                if (listeOp[i].racine == 0) /// Si l'opé est racine, elle est placée directement dans la station
                {
                    listeOp[i].placed = 1;
                    listeStation[nmbStation].listeOp[listeStation[nmbStation].nmbOp] = listeOp[i];
                    listeStation[nmbStation].nmbOp++;
                    couleur = listeOp[i].couleur;
                    cmpOp++;
                } else {
                    /// Si l'opé n'est racine, vérifie si elle peut être atteinte par une opération déjà placée
                    int verif = 0;
                    for (int k = 0; k < nmbOp; k++) {
                        if (listeOp[k].placed == 1) {
                            //. Utilise DFS pour vérifier l'accessibilité
                            if (DFS(listeOp, nmbOp, listeOp[k], listeOp[i]) == 1) {
                                listeOp[i].placed = 1;
                                listeStation[nmbStation].listeOp[listeStation[nmbStation].nmbOp] = listeOp[i];
                                listeStation[nmbStation].nmbOp++;
                                couleur = listeOp[i].couleur;
                                cmpOp++;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    // station suivante
    nmbStation++;
}
