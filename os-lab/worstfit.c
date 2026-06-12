#include<stdio.h>

int main()
{
    int block[20], process[20];
    int m,n;

    scanf("%d",&m);

    for(int i=0;i<m;i++)
        scanf("%d",&block[i]);

    scanf("%d",&n);

    for(int i=0;i<n;i++)
        scanf("%d",&process[i]);

    int allocation[20];

    for(int i=0;i<n;i++)
    {
        allocation[i]=-1;

        int worst=-1;

        for(int j=0;j<m;j++)
        {
            if(block[j] >= process[i])
            {
                if(worst==-1 ||
                   block[j] > block[worst])
                {
                    worst=j;
                }
            }
        }

        if(worst!=-1)
        {
            allocation[i]=worst;
            block[worst]-=process[i];
        }
    }

    printf("\nProcess\tBlock\n");

    for(int i=0;i<n;i++)
    {
        if(allocation[i]!=-1)
            printf("P%d\t%d\n",
                   i+1,allocation[i]+1);
        else
            printf("P%d\tNot Allocated\n",
                   i+1);
    }
}
