
/***********Solution encoding**************/

int individu(int syn[c], int av[c][p], int WLD[p], int service_time[c])
{int i,j,a,a1,s,k,v,som,som1,som2,l,h;
    for(i=0;i<c;i++)
        {
            for(j=0;j<p;j++)
        {
            w[i][j]=0;
            }
            }
    for (i=0;i<c;i++)
        {
            if (syn[i]==1)/***begin(sychronization=1)***/
        {
            A0: a=rand()%20;
            if (av[i][a]==0)
           {
               goto A0;
           }
           w[i][a]=(rand()%(end_time[i]-start_time[i])+start_time[i]);

                if (w[i][a]!=0)
                    {
                        som=0;
                        for (l=0;l<i;l++) {
                            if (w[l][a]!=0)
                        {
                            som=som+service_time[l]+Travel_time(XC[i],YC[l],XC[i],YC[l]);
                        }
                        }
                        }
                        if (som<=WLD[a]) /*** if the workload of the package isn't exceeded yet***/
                            {
                          int v=0;
                        for(j=0;j<i;j++)
                            {
                                if (w[j][a]!=0)
                                    {
                                        if (w[j][a]>=w[i][a])
                                        {
                                            if (w[j][a]<w[i][a]+Travel_time(XC[i],YC[j],XC[i],YC[j])+service_time[i])
                                                {
                                                    v=1; break;
                                            }
                                }
                                else
                                    {
                                        if (w[i][a]<w[j][a]+Travel_time(XC[j],YC[i],XC[j],YC[i])+service_time[j])
                                        {
                                            v=1; break;
                              }
                              }
                              }
                              }
                     for(j=0;j<i;j++) /************** Testing the start of cares assigned to the same patient**********************/
                        {
                                     for (l=0;l<p;l++)
                                {
                                    for (h=0;h<p;h++)
                                {
                                if (w[j][h]!=0 && w[i][l]!=0)
                                {
                                if (patient[i][j]==1)
                                    {
                                if (w[j][h]>=w[i][l])
                                        {
                                if (w[j][h]<w[i][l]+service_time[i])
                                {
                                    v=1; break;
                                }
                                }
                                else
                                    {
                                        if (w[i][l]<w[j][h]+service_time[j])
                                        {
                                            v=1; break;
                              }
                              }
                              }
                              }
                              }
                              }
                              }
                     if (v==1)
                        {
                            w[i][a]=0;i--;
                            }
                     }
                     else /*** if the workload of the packages is exceeded, we choose other packages ****/
                        {
                            w[i][a]=0;
                            goto A0;
                            }
                     }/***end(syn=1)****/
                     else if (syn[i]==2)/***begin(sychronization)=2***/
                                                    {
                                                        B:a=rand()%20;
                     a1=rand()%20;
                     if (a==a1)
                    { goto B;
                    }
                    if (av[i][a]==0 || av[i][a1]==0)
                    { goto B;
                    }
                    w[i][a]=(rand()%(end_time[i]-start_time[i])+start_time[i]);
                    w[i][a1]=w[i][a];
                    if (w[i][a]!=0)
                        {
                        som1=0;
                        for (l=0;l<i;l++)
                        {
                            if (w[l][a]!=0)
                        {som1=som1+service_time[l]+Travel_time(XC[i],YC[l],XC[i],YC[l]);
                        }
                        }
                        }
                        if (w[i][a1]!=0)
                            {
                        som2=0;
                        for (l=0;l<i;l++)
                        {if (w[l][a1]!=0)
                        {som2=som2+service_time[l]+Travel_time(XC[l],YC[i],XC[l],YC[i]);
                        }
                        }
                        }
                        if (som1<=WLD[a] && som2<=WLD[a1]) /*** if the workload of both packages isn't exceeded yet***/
                            {
                        s=0;
                        for(j=0;j<i;j++)
                        {
                            if (w[j][a]!=0)
                            {
                                if (w[j][a]>=w[i][a])
                                {
                                    if (w[j][a]<w[i][a]+Travel_time(XC[i],YC[j],XC[i],YC[j])+service_time[i])
                                    {
                                        s=1; break;
                                        }
                                        }
                                        else
                                            {
                            if (w[i][a]<w[j][a]+Travel_time(XC[j],YC[i],XC[j],YC[i])+service_time[j])
                            {
                                s=1; break;
                                }
                        }
                        }
                        }
                         for(j=0;j<i;j++)
                        {
                            if (w[j][a1]!=0)
                            {
                                if (w[j][a1]>=w[i][a1])
                                {
                                    if (w[j][a1]<w[i][a1]+Travel_time(XC[i],YC[j],XC[i],YC[j])+service_time[i])
                                    {
                                        s=1; break;
                                        }
                                        }
                    else
                        {
                            if (w[i][a1]<w[j][a1]+Travel_time(XC[j],YC[i],XC[j],YC[i])+service_time[j])
                            {
                                s=1; break;
                                }
                        }
                        }
                        }
                     for(j=0;j<i;j++)  /************** Testing the start of cares assigned to the same patient**********************/
                        {
                                     for (l=0;l<p;l++)
                                {
                                    for (h=0;h<p;h++)
                                {
                                if (w[j][h]!=0 && w[i][l]!=0)
                                {
                                if (patient[i][j]==1)
                                    {
                                if (w[j][h]>=w[i][l])
                                        {
                                if (w[j][h]<w[i][l]+service_time[i])
                                {
                                    s=1; break;
                                }
                                }
                                else
                                    {
                                        if (w[i][l]<w[j][h]+service_time[j])
                                        {
                                            s=1; break;
                              }
                              }
                              }
                              }
                              }
                              }
                              }
                        if (s==1)
                            {
                                w[i][a]=0;
                                w[i][a1]=0;
                                i--;
                        }
        }
        else /*** if the workload of the packages is exceeded, we choose other packages ****/
        {
            w[i][a1]=0;
            w[i][a]=0;
            goto B;
        }
        } /***end(syn=2)***/
        }
