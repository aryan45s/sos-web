int main()
{
    int block[20], process[20];
    int m,n;

    scanf("%d",&m);

    for(int i=0;i<m;i++)
        scanf("%d",&block[i]);

    scanf("%d",&n);

    for(int i=0;i<n;i++)
        scanf("%d",&process[i]);

    int allocation[20];
    

    for(int i=0;i<n;i++){
        allocation[i]=-1;
        int best=-1;
        for(int j=0;j<m;j++){
            if(block[j]>=process[i]){
          if(best==-1 || block[j]<block[best]){
              best=j;
              
          }}
        }

        if(best!=-1){
            allocation[i]=best;
            block[best]-=process[i];
        }
    }