#include<stdio.h>

struct task
{
    int id;
    int et;
    int period;
    int deadline;

    int remaining;
    int next_release;
    int current_deadline;
};

int main()
{
    struct task t[10];
    int n, total_time;

    printf("Enter number of tasks:");
    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {
        t[i].id = i + 1;

        printf("\nTask %d\n",i+1);

        printf("Execution Time: ");
        scanf("%d",&t[i].et);

        printf("Period: ");
        scanf("%d",&t[i].period);

        printf("Relative Deadline: ");
        scanf("%d",&t[i].deadline);

        /* First job released at time 0 */
        t[i].remaining = t[i].et;
        t[i].next_release = t[i].period;
        t[i].current_deadline = t[i].deadline;
    }

    printf("\nEnter Simulation Time: ");
    scanf("%d",&total_time);

    for(int time=0; time<total_time; time++)
    {
        /* Release new jobs */
        for(int i=0;i<n;i++)
        {
            if(time == t[i].next_release)
            {
                t[i].remaining = t[i].et;

                t[i].current_deadline =
                time + t[i].deadline;

                t[i].next_release += t[i].period;
            }
        }

        int idx = -1;
        int earliest_deadline = 9999;

        /* EDF Selection */
        for(int i=0;i<n;i++)
        {
            if(t[i].remaining > 0)
            {
                if(t[i].current_deadline <
                   earliest_deadline)
                {
                    earliest_deadline =
                    t[i].current_deadline;

                    idx = i;
                }
            }
        }

        if(idx == -1)
        {
            printf("Time %d - %d : Idle\n",
                   time,time+1);
        }
        else
        {
            printf("Time %d - %d : T%d\n",
                   time,time+1,
                   t[idx].id);

            t[idx].remaining--;
        }
    }

    return 0;
}