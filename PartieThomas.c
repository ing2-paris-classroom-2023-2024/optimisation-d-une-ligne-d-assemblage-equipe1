Partie de code de Thomas

int comparerByClassement(const void *a, const void *b)   // fonction pour classer la liste d'peration en fonction de l'ordre dans le tri topologique
{
    return ((struct Operation *)b)->classement - ((struct Operation *)a)->classement;
}
