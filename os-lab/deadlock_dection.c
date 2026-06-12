#include<stdio.h>

int main()
{
    int n,m;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    printf("Enter number of resource types: ");
    scanf("%d",&m);

    int alloc[20][20];
    int request[20][20];
    int avail[20];

    printf("\nEnter Allocation Matrix:\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%d",&alloc[i][j]);
        }
    }

    printf("\nEnter Request Matrix:\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%d",&request[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");
    for(int i=0;i<m;i++)
    {
        scanf("%d",&avail[i]);
    }

    int finish[20]={0};

    while(1)
    {
        int found=0;

        for(int i=0;i<n;i++)
        {
            if(finish[i]==0)
            {
                int possible=1;

                for(int j=0;j<m;j++)
                {
                    if(request[i][j] > avail[j])
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

                    finish[i]=1;
                    found=1;
                }
            }
        }

        if(found==0)
            break;
    }

    int deadlock=0;

    for(int i=0;i<n;i++)
    {
        if(finish[i]==0)
        {
            deadlock=1;
            break;
        }
    }

    if(deadlock)
    {
        printf("\nDeadlock Detected\n");

        printf("Processes in Deadlock: ");

        for(int i=0;i<n;i++)
        {
            if(finish[i]==0)
            {
                printf("P%d ",i);
            }
        }
    }
    else
    {
        printf("\nNo Deadlock Detected\n");
    }

    return 0;
}