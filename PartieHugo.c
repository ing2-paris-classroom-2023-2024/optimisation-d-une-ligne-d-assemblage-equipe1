void trouverRacine(struct Operation listeOp[100],int nmbOp) // permet de marquer les operations qui n'ont pas de arc entrant ( pas de precedents)
{
    for(int i = 0 ; i< nmbOp ; i++)
    {
        for(int k = 0 ; k< nmbOp ; k++)
        {
            for(int l = 0 ; l < listeOp[k].nmbS ; l++)
            {
                if(getOpById(listeOp[k].suivant[l],listeOp,nmbOp).id == listeOp[i].id)
                {
                    listeOp[i].racine = 1;
                }
            }

        }
    }
}

