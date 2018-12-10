#include<stdio.h>
#include<stdlib.h>
#include<math.h>


typedef struct
{
  int  burst_time;
  int priority;
  int priority_component;
  int shortness_component;
  int context_switch_component;
  int ITS;
  int remaining_time;

}process;

void initialAssignment(process ProcessArray[],int n);



int OTS; //global variable (Original time slice)
int i;



process
input(int i)
{
  process p1;
  printf("Enter the burst_time of the process %d :",i+1);
  scanf("%d",&p1.burst_time);
  printf("Enter the priority of the process %d :",i+1);
  scanf("%d",&p1.priority);
  printf("\n");

  return p1;
}


process display(process p1)
{
  printf("\nThe burst time of the process %d is %d\n",i+1,p1.burst_time);
  printf("The priority of the process %d is %d\n",i+1,p1.priority);
    printf("The priority component of the process %d is %d\n",i+1,p1.priority_component);
      printf("The shortness component of the process %d is %d\n",i+1,p1.shortness_component);
            printf("The context switch component of the process %d is %d\n",i+1,p1.context_switch_component);


        printf("The Intelligent Time Slice of the process %d is %d\n",i+1,p1.ITS);
}

//function to calculate its

void initialAssignment(process ProcessArray[],int n)
{
  //printf("%d",ProcessArray[0].burst_time);
  //pc , get the highest priority and set pc=1 of those and rest 0
 // printf("%d\n",sizeof(processArray));
  //printf("%d",sizeof(processArray[0]));

 //int n=sizeof(ProcessArray)/sizeof(ProcessArray[0]);

 //remaining time equal to burst time

 for(i=0;i<n;i++)
 {
   ProcessArray[i].remaining_time=ProcessArray[i].burst_time;

 }




  int highest_priority;
  int min=0;




  for(i=0;i<n;i++)
  {
    if(ProcessArray[i].priority < ProcessArray[min].priority)
    {
      min=i;
      //printf("%d",min);
    }

    else
    {continue;}
      //continue;}
  }

  //here min is the minimum index priority

  for(i=0;i<n;i++)
  {
    if(ProcessArray[i].priority == ProcessArray[min].priority)
    {
      ProcessArray[i].priority_component=1;
    }

    else
    {
      ProcessArray[i].priority_component=0;
    }
  }
// till here we have set the pc

//now we have to set sc

ProcessArray[0].shortness_component=0;

for(i=1;i<n;i++)
{
  if(ProcessArray[i].burst_time < ProcessArray[i-1].burst_time)
  {
    ProcessArray[i].shortness_component=1;
  }

  else
  {
    ProcessArray[i].shortness_component=0;
  }
}

//now we have to calculate CSC

for(i=0;i<n;i++)
{
    int sum =OTS+ProcessArray[i].shortness_component+ProcessArray[i].priority_component;
    int temp=abs(ProcessArray[i].burst_time-sum);
    if(temp<OTS)
    {
        ProcessArray[i].context_switch_component=1;
    }

    else
    {
        ProcessArray[i].context_switch_component=0;
    }


}




for(i=0;i<n;i++)
{
  ProcessArray[i].ITS=OTS+ProcessArray[i].shortness_component + ProcessArray[i].priority_component+ProcessArray[i].context_switch_component;
}




}

int  checkArray(int Array[], int n)
{

  //if all 0 return 0
 //0-executed
 //1-pending

 int check=0;
 for(i=0;i<n;i++)
 {
   if(Array[i]==1)
   {
     check=1;
     return check;
   }

   else
   {
     continue;
   }
 }

 return check;

}







int main()
{
  int n;
  printf("------Priority Based Intelligent Round Robin--------\n\n");
  printf("\nEnter the total number of processes :");
  scanf("%d",&n);
  int waiting[n];
  int turnaround[n];
  int timeq[n][100];
  int ready[n];
  int remaining_time[n];
int total_time=0;

  for(i=0;i<n;i++){
    ready[i]=1;

  }

  process processArray[n];


  for(i=0;i<n;i++)
  {
    processArray[i]=input(i);
  }
  printf("\nEnter the value of Original time slice :");
  scanf("%d",&OTS);
  initialAssignment(processArray,n);
  for(i=0;i<n;i++)
  {
    display(processArray[i]);
  }
  int round=0;
  //printf("%d",x);
  while(checkArray(ready,n)==1){
    for(i=0;i<n;i++){
      if(i==0)
      {
        if(processArray[i].shortness_component==0)
        {
          timeq[i][round]=(int)ceil((double)(processArray[i].ITS/2));
          //printf("\n timeq=%d",timeq[i][round]);
        }
        else
        {

          timeq[i][round]=processArray[i].ITS;
                    //printf("\n timeq=%d",timeq[i][round]);

        }
      }
      else
      {
         if(processArray[i].shortness_component==0)
        {
          timeq[i][round]=(int)ceil((double)(timeq[i-1][round]+ timeq[i-1][round]/2));
                    //printf("\n timeq=%d",timeq[i][round]);
        }
        else
        {
          //printf("\nefefegh");
          timeq[i][round]=2*timeq[i-1][round];
                    //printf("\n timeq2=%d",timeq[i][round]);
        }
      }
      if((processArray[i].remaining_time-timeq[i][round]<=2 && processArray[i].remaining_time-timeq[i][round]>=0 && processArray[i].remaining_time==0))
      {
        timeq[i][round]=abs(processArray[i].remaining_time-timeq[i][round]);
        //printf("\n working");
        //printf("\n timeq after execution %d",timeq[i][round]);
      }
      else if(processArray[i].remaining_time-timeq[i][round]<1){
        timeq[i][round]=processArray[i].remaining_time;
      }
      //printf("\n timeq = %d",timeq[i][round]);

      if(processArray[i].remaining_time>0){
        if(processArray[i].remaining_time>timeq[i][round]){
            total_time+=timeq[i][round];
        }
        else{
            total_time+=processArray[i].remaining_time;
            waiting[i]=total_time-processArray[i].burst_time;
        }


      }

      if(processArray[i].remaining_time>=0){

        //printf("\np%d %d\n",processArray[i].remaining_time,timeq[i][round]);

      processArray[i].remaining_time=processArray[i].remaining_time- timeq[i][round];
      //printf("\nrem time=%d",processArray[i].remaining_time);
      }
      if(processArray[i].remaining_time<0){
        processArray[i].remaining_time=0;
      }
      if(processArray[i].remaining_time<0){
        processArray[i].remaining_time=0;
      }

      if(processArray[i].remaining_time==0)
      {
        ready[i]=0;
      }

    }

    round++;
  }

    for(i=0;i<n;i++){
        //printf("%d ",waiting[i]);
        turnaround[i]=waiting[i]+processArray[i].burst_time;

    }
    printf("\n");
    int total_wait=0;
    int total_tt=0;
    for(i=0;i<n;i++){
        printf("\nWaiting time of process %d = %d",i+1,waiting[i]);
        printf("\nTurn Around time of process %d = %d",i+1,waiting[i]);
        total_wait+=waiting[i];
        total_tt+=turnaround[i];
        printf("\n");
    }
    float avg_wait=total_wait/n;
    float avg_tt=total_tt/n;
    printf("\nAverage waiting time=%f",avg_wait);
    printf("\nAverage turnaround time=%f",avg_tt);
  //1.Calculate the ITS for all the processes
    int timequantum[n][round];
    int j;
    printf("\n\n Time Quantum Matrix:\n");
    for(i=0;i<n;i++){
        for(j=0;j<round;j++){
            timequantum[i][j]=timeq[i][j];
            printf("%d\t",timequantum[i][j]);
        }
        printf("\n");
    }


}
