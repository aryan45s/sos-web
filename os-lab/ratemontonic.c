#include<stdio.h>

struct task
{
    int id;
    int et;        // execution time
    int period;
    int remaining;
    int next_release;
};

int main()
{
    struct task t[10];
    int n, total_time;

    printf("Enter number of tasks: ");
    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {
        t[i].id = i+1;

        printf("\nTask %d\n",i+1);

        printf("Execution Time: ");
        scanf("%d",&t[i].et);

        printf("Period: ");
        scanf("%d",&t[i].period);

        t[i].remaining = t[i].et;
        t[i].next_release = t[i].period;
    }

    printf("Enter simulation time: ");
    scanf("%d",&total_time);

    for(int time=0; time<total_time; time++)
    {
        /* release new jobs */
        for(int i=0;i<n;i++)
        {
            if(time == t[i].next_release)
            {
                t[i].remaining = t[i].et;
                t[i].next_release += t[i].period;
            }
        }

        int idx = -1;
        int min_period = 9999;

        /* RMS selection */
        for(int i=0;i<n;i++)
        {
            if(t[i].remaining > 0)
            {
                if(t[i].period < min_period)
                {
                    min_period = t[i].period;
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
                   time,time+1,t[idx].id);

            t[idx].remaining--;
        }
    }

    return 0;
}