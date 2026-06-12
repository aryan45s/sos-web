#include<stdio.h>

struct process
{
    int at, bt, rt;
    int ct, tat, wt;
};

int main()
{
    struct process p[20];

    int n, tq;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    printf("Enter Time Quantum: ");
    scanf("%d",&tq);

    for(int i=0;i<n;i++)
    {
        printf("\nProcess %d\n",i+1);

        printf("Arrival Time: ");
        scanf("%d",&p[i].at);

        printf("Burst Time: ");
        scanf("%d",&p[i].bt);

        p[i].rt = p[i].bt;
    }

    int current_time = 0;
    int completed = 0;

    while(completed < n)
    {
        int found = 0;

        for(int i=0;i<n;i++)
        {
            if(p[i].at <= current_time &&
               p[i].rt > 0)
            {
                found = 1;

                if(p[i].rt > tq)
                {
                    current_time += tq;
                    p[i].rt -= tq;
                }
                else
                {
                    current_time += p[i].rt;

                    p[i].rt = 0;

                    p[i].ct = current_time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;

                    completed++;
                }
            }
        }

        if(found == 0)
            current_time++;
    }

    printf("\nAT\tBT\tCT\tTAT\tWT\n");

    for(int i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n",
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }

    return 0;
}