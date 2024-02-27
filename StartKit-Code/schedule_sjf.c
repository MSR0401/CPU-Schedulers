#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "schedulers.h"
#include "list.h"
#include "cpu.h"

struct node *head = NULL;
struct node *tail =NULL;
struct node *new = NULL;

void add(char *name, int priority, int burst)
{
    new = malloc(sizeof(struct node));
    new->task = malloc(sizeof(struct task));
    new->task->name = name;
    new->task->priority = priority;
    new->task->burst = burst;
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
        if(new->task->burst<head->task->burst)
        {
            new->next=head;
            head = new;
        }

        //Insertion in middle or tail
        else{
        struct node *temp = head;
        struct node *prev = NULL;

        while(temp!=NULL && new->task->burst>=temp->task->burst)
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