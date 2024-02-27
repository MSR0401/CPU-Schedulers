#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "schedulers.h"
#include "list.h"
#include "cpu.h"

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

void schedule()
{   
    int task = 0;
    int burst = 0;
    int time = 0;
    float totalBurst=0;
    float waitingTime = 0;
    float turnAroundTime=0;
    struct node *temp = head;
    while(temp!=NULL)
    {   
        run(temp->task,temp->task->burst);
        time+=temp->task->burst;
        task ++;
        burst = burst + temp->task->burst;
        totalBurst = totalBurst + temp->task->burst;
        if(temp->next!= NULL)
        {
            waitingTime = waitingTime + burst;
        }
        turnAroundTime+=time;
        temp=temp->next;
    }
    printf("\nAverage waiting time = %.2f\n" , waitingTime/task);
    printf("Average turnaround time = %.2f\n", turnAroundTime/task);
    printf("Average response time = %.2f\n ", waitingTime/task);
}   
