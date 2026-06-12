#include<stdio.h>
int frames[10];
int pages[10];
int f;
int page_faults=0;
int index=0;
int main(){
    int n;
printf("enter the number of pages");
scanf("%d",&n);
printf("enter the reference string ");

for(int i=0;i<n;i++){
scanf("%d",&pages[i]);
}
printf("enter the no frames");
scanf("%d",&f);
for(int i=0;i<f;i++){
    frames[i]=-1;
}
for(int i=0;i<n;i++){
    int found=0;
for(int j=0;j<f;j++){
    if(frames[j]==pages[i]){
found=1;
break;

    }}
    if(found==0){
 frames[index]=pages[i];
 index=(index+1)%f;
page_faults+=1;

    }

}
}