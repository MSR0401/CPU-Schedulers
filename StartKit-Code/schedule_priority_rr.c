#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "schedulers.h"
#include "list.h"
#include "cpu.h"

struct node *head = NULL;
struct node *tail =NULL;
struct node *new = NULL;
int counter = 0;
void add(char *name, int priority, int burst)
{
    new = malloc(sizeof(struct node));
   
    new->task = malloc(sizeof(struct task));
    new->task->name = name;
    new->task->priority = priority;
    new->task->burst = burst;
    new->task->tid = counter;
    counter++;
    new->next=NULL;

    //Insertion of first element into list
    if(head==NULL)
    {  
        head = new;
        tail = head;
    }
    else
    {
        
        //Insertion at head
        if(new->task->priority>head->task->priority)
        {
            new->next=head;
            head = new;
        }

        //Insertion in middle or tail
        else{
        struct node *temp = head;
        struct node *prev = NULL;

        while(temp!=NULL && new->task->priority<=temp->task->priority)
        {
            prev = temp;
            temp=temp->next;
            
        }
        //Insertion at tail
        if(temp==NULL)
        {
            tail = new;
        }
        //Insertion in middle
        else{
            prev->next=new;
            new->next = temp;
        }
        new->next = temp;
        prev->next = new;
        }
    }

}

int getTid(struct node **head,Task *task)
{
    struct node *temp;
    temp=*head;
    while(strcmp(temp->task->name,task->name)!=0)
    {
        temp=temp->next;
    }
    return temp->task->tid;
}

void schedule(){
    int time = 0;
    float totalTurnAround = 0 ;
    float totalWaitTime = 0;
    float totalResponseTime = 0;
    struct node *temp = head;
    struct node *temp2 = head;
    struct node *temp3 = head;
    struct node *temp4 = head;
    int process = 0;
    
    
    while(temp2!=NULL)
    {
        process++;
        temp2=temp2->next;
    }
    int burst[process];
    while (temp4!=NULL)
    {
        /* code */
        burst[temp4->task->tid]=temp4->task->burst;
        temp4=temp4->next;
    }
    
    while(temp!=NULL)
    {
        if(temp->task->burst<=QUANTUM)
        {   
            
            run(temp->task,temp->task->burst);
            if(temp->task->burst==burst[getTid(&head,temp->task)])
            {
                totalResponseTime+=time;
            }
            time+=temp->task->burst;
            totalTurnAround+=time;
            totalWaitTime+=time-burst[getTid(&head,temp->task)];
            temp = temp->next;
        }
        else
        {
            if(temp->next==NULL)
            {   
                run(temp->task,temp->task->burst);
                if(temp->task->burst==burst[getTid(&head,temp->task)])
                {
                    totalResponseTime+=time;
                }   
                time+=temp->task->burst;
                totalTurnAround+=time;
                totalWaitTime+=time-burst[getTid(&head,temp->task)];

            }
            else if(temp->task->priority>temp->next->task->priority)
            {
                run(temp->task,temp->task->burst);
                if(temp->task->burst==burst[getTid(&head,temp->task)])
                {
                    totalResponseTime+=time;
                }
                time+=temp->task->burst;
                totalTurnAround+=time;
                totalWaitTime+=time-burst[getTid(&head,temp->task)];

                
            }
            else{
            run(temp->task,QUANTUM);
            if(temp->task->burst==burst[getTid(&head,temp->task)])
            {
                totalResponseTime+=time;
            }
            time+=QUANTUM;
            temp->task->burst=temp->task->burst-QUANTUM;
            add(temp->task->name,temp->task->priority,temp->task->burst);
            
            }
            temp=temp->next;
            
        }

    }
    printf("\nAverage waiting time = %.2f\n", totalWaitTime/process);
    printf("Average turnaround time = %.2f\n", totalTurnAround/process);
    printf("Average response time = %.2f\n", totalResponseTime/process);



}