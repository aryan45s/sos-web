#include<stdio.h>
int process[20];
int block[20];
int main(){
    printf("enter the number of process");
    int n;int m;
    scanf("%d",&n);
    printf("enter the number of blocks");
    scanf("%d",&m);
    printf("enter the block size");
    for(int i=0;i<m;i++){
     scanf("%d",&block[i]);
    }
    printf("enter the process size ");
    for(int i=0;i<n;i++){
        scanf("%d",&process[i]);
    }int allocation[20];
    for(int i=0;i<n;i++){
      allocation[i]=-1;
      for(int j=0;j<m;j++){
        if(process[i]<block[j]){
            allocation[i]=j;
            block[j]-=process[i];
            break;

        }
           
        
      }
    }
    for(int i=0;i<n;i++){
        if(allocation[i]!=-1){
            printf("p%d  %d",i+1,allocation[i]);
        }
    }


}