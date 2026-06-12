#include <stdio.h>

struct Process
{
    int pid, at, bt, ct, tat, wt, completed;
};

int main()
{
    int n, i;
    struct Process p[20];

    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        printf("\nProcess %d\n", i + 1);

        printf("Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        p[i].completed = 0;
    }

    int completed = 0;
    int current_time = 0;

    while(completed < n)
    {
        int idx = -1;
        int min_bt = 9999;

        for(i = 0; i < n; i++)
        {
            if(p[i].at <= current_time &&
               p[i].completed == 0)
            {
                if(p[i].bt < min_bt)
                {
                    min_bt = p[i].bt;
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

            avg_wt += p[idx].wt;
            avg_tat += p[idx].tat;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }

    printf("\nAverage WT = %.2f", avg_wt / n);
    printf("\nAverage TAT = %.2f\n", avg_tat / n);

    return 0;
}