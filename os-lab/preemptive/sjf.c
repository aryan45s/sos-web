#include<stdio.h>

struct process{
    int at,bt,rt,ct,tat,wt,completed;
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

        p[i].rt = p[i].bt;      // CHANGED
        p[i].completed = 0;
    }

    int completed = 0;
    int current_time = 0;

    while(completed < n)
    {
        int idx = -1;
        int min = 9999;

        for(int i=0;i<n;i++)
        {
            if(p[i].at <= current_time &&
               p[i].completed == 0)
            {
                if(p[i].rt < min)      // CHANGED
                {
                    min = p[i].rt;
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
            p[idx].rt--;      // CHANGED
            current_time++;   // CHANGED

            if(p[idx].rt == 0)    // CHANGED
            {
                p[idx].ct = current_time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;

                p[idx].completed = 1;
                completed++;
            }
        }
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