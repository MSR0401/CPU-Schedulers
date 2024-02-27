#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "schedulers.h"
#include "list.h"
#include "cpu.h"
int time = 0;
int totalProcess=0;
float averageTurnAround = 0.0;
float averageResponse = 0.0;
float averageWait = 0.0;
struct node *head = NULL;
struct node *tail = NULL;

void add(char *name, int priority, int burst){
    if(head==NULL)
    {
        head= malloc(sizeof(struct node));
        head->task = malloc(sizeof(struct task));
        head->task->name = name;
        head->task->priority = priority;
        head->task->burst = burst;
        head->next = NULL;
        tail=head;
    }
    else{
        struct node *newNode = malloc(sizeof(struct node));
        newNode->task= malloc(sizeof(struct task));
        newNode->task->name=name;
        newNode->task->priority=priority;
        newNode->task->burst=burst;
        newNode->next=NULL;
        tail->next=newNode;
        tail=newNode;
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

void schedule()
{
    struct node *temp = head;
    struct node *temp2 = head;
    float responseTime = 0;
    int i = 0;
    while(temp2!=NULL)
    {   temp2->task->tid = i;
        if(temp2->next!=NULL)
        {   if(temp2->task->burst<=QUANTUM)
        {
                responseTime+=temp2->task->burst;
        }
            else
            {
                responseTime+=QUANTUM;
            }
            averageResponse+=responseTime;
        }
        else{

        }
        i++;
        totalProcess++;
        temp2=temp2->next;

    }
    int j = 0;
    int burst[totalProcess];
    temp2 = head;
    while(temp2!=NULL){
        burst[j]=temp2->task->burst;
        j++;
        temp2=temp2->next;
    }
    
    while(temp!=NULL)
    {
        if(temp->task->burst<=QUANTUM)
        {
            run(temp->task,temp->task->burst);
            time+=temp->task->burst;
            averageWait+= time - burst[getTid(&head,temp->task)];
            averageTurnAround+=time;
            temp=temp->next;
        }
        else
        {
            run(temp->task,QUANTUM);
            time+=QUANTUM;
            temp->task->burst = temp->task->burst-QUANTUM;
            add(temp->task->name,temp->task->priority,temp->task->burst);
            temp=temp->next;
        }
    }
    printf("\nAverage waiting time = %.2f\n", averageWait/totalProcess);
    printf("Average turnaround time = %.2f\n", averageTurnAround/totalProcess);
    printf("Average response time = %.2f\n", averageResponse/totalProcess);

    

    
}