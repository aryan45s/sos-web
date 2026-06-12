#include<stdio.h>

int main()
{
    int n,m;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    printf("Enter number of resource types: ");
    scanf("%d",&m);

    int alloc[20][20];
    int max[20][20];
    int need[20][20];
    int avail[20];

    printf("\nEnter Allocation Matrix:\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%d",&alloc[i][j]);
        }
    }

    printf("\nEnter Max Matrix:\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%d",&max[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");
    for(int i=0;i<m;i++)
    {
        scanf("%d",&avail[i]);
    }

    // Need = Max - Allocation
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            need[i][j] =
            max[i][j] - alloc[i][j];
        }
    }

    int finish[20]={0};
    int safe[20];
    int count=0;

    while(count<n)
    {
        int found=0;

        for(int i=0;i<n;i++)
        {
            if(finish[i]==0)
            {
                int possible=1;

                for(int j=0;j<m;j++)
                {
                    if(need[i][j] > avail[j])
                    {
                        possible=0;
                        break;
                    }
                }

                if(possible)
                {
                    for(int j=0;j<m;j++)
                    {
                        avail[j] += alloc[i][j];
                    }

                    safe[count++] = i;
                    finish[i]=1;
                    found=1;
                }
            }
        }

        if(found==0)
        {
            break;
        }
    }

    if(count==n)
    {
        printf("\nSystem is SAFE\n");
        printf("Safe Sequence: ");

        for(int i=0;i<n;i++)
        {
            printf("P%d ",safe[i]);
        }
    }
    else
    {
        printf("\nSystem is NOT SAFE\n");
    }

    return 0;
}