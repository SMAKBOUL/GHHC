/***comments for the reader***/


/***The provided encoding solution is a method for generating an individual in the context of NSGA-II to solve the scheduling problem.
 The objective is to assign patients' care to caregivers while satisfying various constraints, including synchronization, continuity of care, workload, and capacity limitations.
The encoding solution uses a two-dimensional array "w[i][j]" to represent the assignments of cares to caregivers. It initializes all elements of this array to zero. 
The algorithm then iterates over the patients (denoted by "i") and their respective synchronization parameters ("syn[i]"), which indicate if a care requires one caregiver (syn=1) or two caregivers (syn=2).
For the case when syn=1, the algorithm randomly selects a caregiver ("a") from the available pool ("av[i][a]=1") and assigns the care's start time based on a random value between the specified start and end time. 
It then checks if this assignment satisfies the workload and capacity constraints for the selected caregiver and whether it maintains the continuity of care for each patient. 
If any of these conditions are not met, the algorithm retries the assignment process until a valid one is found.
Similarly, for the case when syn=2 (two caregivers required for synchronization), the algorithm randomly selects two caregivers ("a" and "a1") from the available pool and assigns the care's
 start time for both caregivers based on random values within the specified start and end time. 
It then verifies if the workload and capacity constraints are satisfied for both caregivers and if the continuity of care is maintained for each patient. 
If any of these conditions are not met, the algorithm retries the assignment process until a valid one is found. 
In situations where the workload or package capacity is exceeded, the algorithm reassigns the care to an alternative package while still adhering to the continuity of care constraints.***/

/***********Solution encoding**************/
int individu(int syn[c], int av[c][p], int WLD[p], int service_time[c], int demand[c], int capa[p])
{int i,j,a,a1,s,k,v,som,som_d,som1,som1_d,som2,som2_d,l,h;
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
            A0: a=rand()%12;
            if (av[i][a]==0)
           {
               goto A0;
           }
           w[i][a]=(rand()%(end_time[i]-start_time[i])+start_time[i]);
                if (w[i][a]!=0)
                    {
                        som=0;
                        som_d=0
                        for (l=0;l<i;l++) {
                            if (w[l][a]!=0)
                        {
                            som=som+service_time[l]+Travel_time(XC[i],YC[l],XC[i],YC[l]);
                            som_d=som_d+demand[l];
                        }
                        }
                        }
                        if (som<=WLD[a] && som_d<=capa[a]) /*** if the workload & capacity of the package aren't exceeded yet***/
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
                     else /*** In case the workload or package capacity is exceeded, we opt for alternative packages that still adhere to the continuity of care ****/
                        {
                            w[i][a]=0;
                            goto A0;
                            }
                     }/***end(syn=1)****/
                     else if (syn[i]==2)/***begin(sychronization)=2***/
                                                    {
                                                        B:a=rand()%12;
                     a1=rand()%12;
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
                        som1_d=0;
                        for (l=0;l<i;l++)
                        {
                            if (w[l][a]!=0)
                        {som1=som1+service_time[l]+Travel_time(XC[i],YC[l],XC[i],YC[l]);
                         som1_d=som1_d+demand[l];
                        }
                        }
                        }
                        if (w[i][a1]!=0)
                            {
                        som2=0;
                        som2_d=0;
                        for (l=0;l<i;l++)
                        {if (w[l][a1]!=0)
                        {som2=som2+service_time[l]+Travel_time(XC[l],YC[i],XC[l],YC[i]);
                         som2_d=som2_d+demand[l];
                        }
                        }
                        }
                        if (som1<=WLD[a] && som2<=WLD[a1] && som1_d<=capa[a] && som2_d<=capa[a1] ) /*** if the workload & capacity of both packages aren't exceeded yet***/
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
        else /***In case the workload or package capacity is exceeded, we opt for alternative packages that still adhere to the continuity of care  ****/
        {
            w[i][a1]=0;
            w[i][a]=0;
            goto B;
        }
       } /***end(syn=2)***/
     }
     }
