//#ifndef QUEUEOFSTRUCTS_H
//#define QUEUEOFSTRUCTS_H
//#endif
#include <stdio.h>
#include <stdlib.h>

 struct process
    {
        int processid;
        int arrivaltime;
        int runtime;
        int priority;
        int memsize;
    };




struct messagequeuetoscheduler
{
        long mtype;
        struct process processtobesend;  /// message data itself

};

struct node
{
    struct process thedataofprocess;
    struct node *next;
     //pointer points to struct
};


struct linkedlist_as_queue
{
    struct node *head;
    struct node *tail;

    int count;

};


struct linkedlist_as_queue *createqueue()
{
    struct linkedlist_as_queue * zz,s;
    zz=&s;
    zz->head = zz->tail = NULL;
    return zz;
}



struct node *newnode(struct process newprocess)
{

    struct node * temp ,w;
    temp=&w;
    temp->thedataofprocess.processid = newprocess.processid;
    temp->thedataofprocess.arrivaltime = newprocess.arrivaltime;
    temp->thedataofprocess.runtime = newprocess.runtime;
    temp->thedataofprocess.priority = newprocess.priority;
    temp->thedataofprocess.memsize = newprocess.memsize;
    temp->next = NULL;

    return temp;
}



void enqueue(struct linkedlist_as_queue *nameofthequeue, struct process nextprocess)
{


        struct node *temp  = newnode (nextprocess);


    struct linkedlist_as_queue y;
    nameofthequeue=&y;

    if (nameofthequeue -> tail == NULL)
    {
        nameofthequeue->head = nameofthequeue->tail = temp;
        return;
    }

   else
   {
        nameofthequeue->tail->next = temp;
        nameofthequeue->tail = temp;
   }
   nameofthequeue->count ++ ;
}

int isempty (struct linkedlist_as_queue *nameofthequeue)
{
    struct linkedlist_as_queue f;
    nameofthequeue=&f;
    if (nameofthequeue->head == NULL && nameofthequeue-> tail ==NULL)
    {
        return 1;
    }
    else
    {
        return 0 ;
    }
}

void dequeue(struct linkedlist_as_queue *nameofthequeue)
{
    struct linkedlist_as_queue u;
    nameofthequeue=&u;

     if (nameofthequeue->head == NULL)
            {
                printf("thequeueisempty");
            }



    struct node *temp = nameofthequeue->head;

    nameofthequeue->head = nameofthequeue->head->next;

        nameofthequeue->count --;
}



//// in case of non premptive HPF >> the process will enter the ready queue based on their prority
// the smaller value of prority , the higher prority to be at front of the ready queue


void sortingthequeue_basedon_priority_HPF (struct linkedlist_as_queue *nameofthequeue , struct node * process)
{
    struct linkedlist_as_queue q;
    nameofthequeue=&q;

    struct node yout;
    process=&yout;



    if (nameofthequeue->count ==0) // in case if the queue is empty
    {
        enqueue(nameofthequeue, process->thedataofprocess); // here we will enqueue the first process in the queue

    }



    // if the queue has one value only >> if the added process has priority bigger than the prority of front
   // it will be added normally by enqueue function as no sorting required right ??


    if (nameofthequeue->head->next == NULL)
    {
            // if the queue has one value only >> if the added process has priority bigger than the prority of front
          // it will be added normally by enqueue function as no sorting required right ??
        if (nameofthequeue -> head->thedataofprocess.priority < process->thedataofprocess.priority)
        {
            enqueue(nameofthequeue, process->thedataofprocess);

        }

        // if the added process has priority smaller than the prority of front
        if (nameofthequeue -> head->thedataofprocess.priority > process->thedataofprocess.priority)
        {
            process ->next = nameofthequeue->head;
            nameofthequeue->head = process;
            nameofthequeue->tail = nameofthequeue -> head ->next ;

        }
    }



   ///// here we will check if the forexample the queue has two process ( two nodes )
   // so the new node ( new process ) >> has priority less than the priortiy of the head process
   //so the next of the added node will point to head
  // then the head  become on the added node
    if (nameofthequeue->head ->thedataofprocess.priority >= process->thedataofprocess.priority)

    {
        process ->next = nameofthequeue->head;
        nameofthequeue->head = process;

    }


// reference of this case  >>>>>>from internet
   //if the queue has more than two process ( three or four )
   struct node  *first,tor;
   first=&tor;
   struct node  * afterhead,tor2;
   afterhead=&tor2;


    first = nameofthequeue->head;
 afterhead= first->next;

    while (process->thedataofprocess.priority > afterhead->thedataofprocess.priority )
    {
        if (afterhead->next == NULL)
        {
            enqueue(nameofthequeue, process->thedataofprocess);
        }
        first = afterhead;
        afterhead = afterhead->next;
    }

    process->next = afterhead;
    first->next = process;

}

