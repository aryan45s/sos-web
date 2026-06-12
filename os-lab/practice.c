// #include<stdio.h>
// struct process{
//     int at,bt,ct,tat,wt,completed;
// };
// int main(){
// struct process p[20];
// int n;
// printf("enter the number of processes");
// scanf("%d",&n);
// for(int i=0;i<n;i++){
//     printf("enter the arrival time for process %d\n",);
//     scanf("%d",p[i].at);
//     printf("enter the burst time \n");
//     scanf("%d",p[i].bt);
//     p[i].completed=0;

// }
// int completed=0;
// int current_time=0;
// while(completed<n){
//     int idx=-1;
//     int min=9999;
//     for(int i=0;i<n;i++){
//         if(p[i].at<=current_time && p[i].completed==0){
//              if(p[i].bt<min){
//                 min=p[i].bt;
//                 idx=i;
//              }
//         }}
//         if(idx==-1){
//             current_time++;
//         }
//         else{
//             p[idx].ct=current_time+p[idx].bt;
//             p[idx].tat=p[idx].ct-p[idx].at;
//             p[idx].wt=p[idx].tat-p[idx].bt;
//             p[idx].completed=1;
//             completed++;
//         }
    
// }

// }
// #include<stdio.h>
// struct process{
//     int at,bt,rt,ct,tat,wt,completed;
// };

// int main(){
//  struct process p[20];
//  int n;
//  printf("enter the number of process\n");
//  scanf("%d",&n);
//  for(int i=0;i<n;i++){
//        printf("\nProcess %d\n",i+1);

//         printf("Arrival Time: ");
//         scanf("%d",&p[i].at);

//         printf("Burst Time: ");
//         scanf("%d",&p[i].bt);
//         p[i].rt=p[i].bt;
//         p[i].completed=0;
//  }
// int completed=0;
// int current_time=0;
// while(completed<n){
//     int idx=-1;
//     int min=999;
//     for(int i=0;i<n;i++){
//         if(current_time>=p[i].at && p[i].completed==0){
//             if(p[i].rt<min){
//                 min=p[i].rt;
//                 idx=i;
                
//             }}}
//             if(idx==-1){
//                 current_time++;
//             }
//             else{
//            p[idx].rt--;
//            current_time++;
//            if(p[idx].rt==0){
//             p[idx].ct=current_time;
//             p[idx].tat=p[i].ct-p[i].at;
//             p[idx].wt=p[i].tat-p[i].bt;

//            }

//             }
        
    
// }
// }


// #include<stdio.h>
// struct process{
//     int at,bt,rt,ct,tat,wt;
// };

// int main(){
//     int qt=2;
//  struct process p[20];
//  int n;
//  printf("enter the number of process\n");
//  scanf("%d",&n);
//  for(int i=0;i<n;i++){
//        printf("\nProcess %d\n",i+1);

//         printf("Arrival Time: ");
//         scanf("%d",&p[i].at);

//         printf("Burst Time: ");
//         scanf("%d",&p[i].bt);
//         p[i].rt=p[i].bt;
        
//  }
//  int current_time=0;
//  int completed=0;
//  while(completed<n){
//     int found=0;
//     for(int i=0;i<n;i++){
//         if(p[i].at<=current_time && p[i].rt>0){
//             found=1;
//             if(p[i].rt>qt){
//                 p[i].rt--;
//                 current_time+=qt;
//             }
//             else {
//                  current_time+=p[i].rt;
//                  p[i].rt=0;
                
//                  p[i].ct=current_time;
//                  p[i].tat=p[i].ct-p[i].at;
//                  p[i].wt=p[i].tat-p[i].bt;
//                  completed++;

//              }
//         }
//     }
//  }
// #include<stdio.h>

// struct task
// {
//     int id;
//     int et;        // execution time
//     int period;
//     int remaining;
//     int next_release;
// };

// int main()
// {
//     struct task p[20];
//     struct task t[10];
//     int n, total_time;

//     printf("Enter number of tasks: ");
//     scanf("%d",&n);

//     for(int i=0;i<n;i++)
//     {
//         t[i].id = i+1;

//         printf("\nTask %d\n",i+1);

//         printf("Execution Time: ");
//         scanf("%d",&t[i].et);

//         printf("Period: ");
//         scanf("%d",&t[i].period);

//         t[i].remaining = t[i].et;
//         t[i].next_release = t[i].period;
//     }

//     printf("Enter simulation time: ");
//     scanf("%d",&total_time);
//     for(int time=0;time<total_time;time++){
//        for(int i=0;i<n;i++){
//         if(time==p[i].next_release){
//             p[i].remaining=p[i].et;
//             p[i].next_release+=p[i].period;
//         }
        
//         int idx=-1;
//        int min=999;

//        for(int i=0;i<n;i++){
//         if(p[i].remaining>0){
//             if(p[i].period<min){
//                 idx=i;
//                 min=p[i].period;
//             }
//         }
//        }
//        if(idx==-1){
//         printf("%d---%d idle",time,time+1);
//        }
//        else{
//         printf("%d---%d ->>%d",time,time+1,p[idx].id);
//        }
//        }
       
//        }
       
//     }
// #include<stdio.h>
// struct task{
//     int id;
// int et;
// int current;
// int next_release;
// int period;
// int deadline;
// int remaining;

// };
// struct task t[20];
// int main(){
//     int n;
//     printf("enter the number of process");
//     scanf("%d",&n);
//     int stime;
//      for(int i=0;i<n;i++)
//     {
//     t[i].id = i + 1;

//         printf("\nTask %d\n",i+1);

//         printf("Execution Time: ");
//         scanf("%d",&t[i].et);

//         printf("Period: ");
//         scanf("%d",&t[i].period);

//         printf("Relative Deadline: ");
//         scanf("%d",&t[i].deadline);

//         /* First job released at time 0 */
//         t[i].remaining = t[i].et;
//         t[i].next_release = t[i].period;
//         t[i].current = t[i].deadline;
//     }
//     for(int time=0;time<n;time++){
//        for(int i=0;i<n;i++){
//         if(time==t[i].next_release){
//             t[i].remaining=t[i].et;
//             t[i].next_release+=t[i].period;
//             t[i].current=time+t[i].deadline;
//         }
//        }
//        int idx=-1;
//        int min=9999;
//        for(int i=0;i<n;i++){
//         if(t[i].remaining>0){
//             if(t[i].deadline<min){
//                 min=t[i].deadline;
//                 idx=i;

//             }

//         }
//        }
//        if(idx==-1){
//         printf("%d----%d",time,time+1);

//        }
//        else{
//         printf("%d-----%d",time,time++);
//         t[idx].remaining--;
//        }
//     }
    

// }
// #include<stdio.h>
// #include<semaphore.h>
// #include<pthread.h>
// #include<unistd.h>
// #define size 5
// int buffer[size];
// int in=0;
// int out=0;
// sem_t empty;
// sem_t full;
// pthread_mutex_t mutex;
// void *producer(void *arg){
//     int item;
//     for(int i=0;i<10;i++){
//         item=i;
//         sem_wait(&empty);
//         pthread_mutex_lock(&mutex);
//         buffer[in]=item;
//         in=(in+1)%size;
//         printf("%d is added in %d ",item,i);
//         pthread_mutex_unlock(&mutex);
//         sem_post(&full);
//         sleep(1);
//     }

// }
// void *consumer(void *arg){
//     int item;
//     for(int i=0;i<10;i++){
        
//         sem_wait(&full);
//         pthread_mutex_lock(&mutex);
//         item=buffer[out];
//         printf("%d----%d",item,out);
//         out=(out+1)%size;
//         pthread_mutex_unlock(&mutex);
//         sem_post(&empty);
// sleep(1);

//     }
// }

// sem_t chopsticks[size];
// void *philosoper(int num){
//     int i=*(int*)num;
//  printf("philosopher is thinking ");
//  sleep(1);
//  sem_wait(&chopsticks[i]);
//  sem_wait(&chopsticks[(i+1)%size]);
//  printf("philosoper is eating");
//  sleep(2);
//  sem_post(&chopsticks[i]);
//  sem_post(&chopsticks[(i+1)%size]);
// }
// int main(){
//     for(int i=0;i<5;i++){
// sem_init(&chopsticks[i],0,1);
//     }


    

// }

#include<stdio.h>
int main(){
    int alloc[10][10];
    int max[10][10];
    int need[10][10];
    int avail[10];
    int n,m;
    printf("enter the number of processes");
    scanf("%d",&n);
    printf("enter the number of resoureces");
    scanf("%d",&m);
    printf("enter the alocation matrix");
    for(int i=0;i<n;i++){
        for(int j=0;i<m;j++){
            scanf("%d",alloc[i][j]);
        }
    }
    printf("enter the max matrix");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&max[i][j]);
        }}

        for(int i=0;i<n;i++){
            scanf("%d",&avail[i]);
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                need[i][j]=max[i][j]-alloc[i][j];
            }
        }
int count =0;
int safe[10];
  int finish[20]={0};
  while(count<n){
     int found=0;;
for(int i=0;i<n;i++){
   
    if(finish[i]==0){
     int possible=1;
    for(int j=0;j<n;j++){
        if(need[i][j]>avail[j]){
            possible =0;
            break;
        }
    }
    if(possible=1){
        for(int j=0;j<m;j++){
            avail[j]+=alloc[i][j];
        }
        safe[count++]=i;
        finish[i]=1;
        found=1;

    }
}}
if(found==-1){
break;
}

  }

    
    
}
