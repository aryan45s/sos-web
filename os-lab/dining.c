#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define N 5

sem_t chopstick[N];

void* philosopher(void* num)
{
    int i = *(int*)num;

    while(1)
    {
        printf("Philosopher %d is thinking\n", i);
        sleep(1);

        // pick left chopstick
        sem_wait(&chopstick[i]);

        // pick right chopstick
        sem_wait(&chopstick[(i+1)%N]);

        // eating section
        printf("Philosopher %d is eating\n", i);
        sleep(2);

        // put down right chopstick
        sem_post(&chopstick[(i+1)%N]);

        // put down left chopstick
        sem_post(&chopstick[i]);
    }
}

int main()
{
    pthread_t ph[5];
    int a[5];

    // initialize chopsticks
    for(int i=0;i<N;i++)
        sem_init(&chopstick[i], 0, 1);

    // create philosopher threads
    for(int i=0;i<N;i++)
    {
        a[i] = i;
        pthread_create(&ph[i], NULL, philosopher, &a[i]);
    }

    // join threads
    for(int i=0;i<N;i++)
        pthread_join(ph[i], NULL);

    return 0;
}