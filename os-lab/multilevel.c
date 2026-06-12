#include<stdio.h>

struct process
{
    int pid;
    int at, bt;
    int ct, tat, wt;
    int type;   // 1-System, 2-User
};

int main()
{
    struct process p[20];
    int n;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {
        p[i].pid = i + 1;

        printf("\nProcess %d\n",i+1);

        printf("Arrival Time: ");
        scanf("%d",&p[i].at);

        printf("Burst Time: ");
        scanf("%d",&p[i].bt);

        printf("Type (1-System, 2-User): ");
        scanf("%d",&p[i].type);
    }

    int current_time = 0;

    /* System Queue First */
    for(int i=0;i<n;i++)
    {
        if(p[i].type == 1)
        {
            if(current_time < p[i].at)
                current_time = p[i].at;

            p[i].ct = current_time + p[i].bt;
            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;

            current_time = p[i].ct;
        }
    }

    /* User Queue Next */
    for(int i=0;i<n;i++)
    {
        if(p[i].type == 2)
        {
            if(current_time < p[i].at)
                current_time = p[i].at;

            p[i].ct = current_time + p[i].bt;
            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;

            current_time = p[i].ct;
        }
    }

    printf("\nPID\tAT\tBT\tTYPE\tCT\tTAT\tWT\n");

    for(int i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].type,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }

    return 0;
}