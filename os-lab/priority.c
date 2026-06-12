#include<stdio.h>

struct process
{
    int at, bt, pr;
    int ct, tat, wt;
    int completed;
};

int main()
{
    struct process p[20];
    int n;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {
        printf("\nProcess %d\n",i+1);

        printf("Arrival Time: ");
        scanf("%d",&p[i].at);

        printf("Burst Time: ");
        scanf("%d",&p[i].bt);

        printf("Priority: ");
        scanf("%d",&p[i].pr);

        p[i].completed = 0;
    }

    int completed = 0;
    int current_time = 0;

    while(completed < n)
    {
        int idx = -1;
        int highest_priority = 9999;

        for(int i=0;i<n;i++)
        {
            if(p[i].at <= current_time &&
               p[i].completed == 0)
            {
                if(p[i].pr < highest_priority)
                {
                    highest_priority = p[i].pr;
                    idx = i;
                }
            }
        }

        if(idx == -1)
        {
            current_time++;
        }
        else
        {
            p[idx].ct = current_time + p[idx].bt;

            p[idx].tat = p[idx].ct - p[idx].at;

            p[idx].wt = p[idx].tat - p[idx].bt;

            current_time = p[idx].ct;

            p[idx].completed = 1;

            completed++;
        }
    }

    printf("\nAT\tBT\tPR\tCT\tTAT\tWT\n");

    for(int i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].at,
               p[i].bt,
               p[i].pr,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }

    return 0;
}