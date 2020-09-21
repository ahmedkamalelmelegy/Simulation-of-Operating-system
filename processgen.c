#include "queueofstructs.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include<math.h>
#include"headers.h"



int up_v=12345;

void clearResources(int);
int main(int argc, char *argv[])
//int main()
{
        printf("jjjjjjjjjjjjjjjjjjjjjjjjjjjjj \n");
    signal(SIGINT, clearResources);

    int p_id, p_arrivaltime , p_runtime, p_priority, p_memsize;
        printf("jjjjjjjjjjjjjjjjjjjjjjjjjjjjj \n");
    struct linkedlist_as_queue * storeprocessinqueue,muti;
    storeprocessinqueue=&muti;

    char algorithim ;
    int RRquantum;
            printf("jjjjjjjjjjjjjjjjjjjjjjjjjjjjj \n");
    storeprocessinqueue = createqueue();
            printf("jjjjjjjjjjjjjjjjjjjjjjjjjjjjj \n");
    struct process readprocess;
    int whatistimenow;
            printf("jjjjjjjjjjjjjjjjjjjjjjjjjjjjj \n");
    FILE *readfromfile ;
            printf("jjjjjjjjjjjjjjjjjjjjjjjjjjjjj \n");
   readfromfile = fopen("test.txt", "r");

    if (readfromfile == NULL)
    {
        printf("Error! your file not found \n");

    }


    // while loop tp check it not reach the end of the line
    while (fscanf(readfromfile, "%d\t%d\t%d\t%d\t%d", &p_id, &p_arrivaltime,  &p_runtime, &p_priority, &p_memsize) != EOF)  // will read sepearated by \t (tab)
    {
        readprocess.processid = p_id;
        readprocess.arrivaltime = p_arrivaltime;
        readprocess.runtime = p_runtime;
        readprocess.priority = p_priority;
        readprocess.memsize= p_memsize;
        printf("jjjjjjjjjjjjjjjjjjjjjjjjjjjjj \n");
        // after reading the values in variables >> it will enqueue to the process queue at each line
        enqueue(storeprocessinqueue,readprocess);

    }


    printf("Hi choose your algorithim of scheduling\na- Non premtive HPF\nb-Shortest remaning time next SRTN \nc-Round Robin RR\n  ");



        scanf("%c", &algorithim);

  //  if (algorithim == c)
    //{
    //    printf("now you are on RR,you have to choose the quantum of the Round Robin algorithm\n");
      //  scanf( "%d", &RRquantum);

    //}




 int pid = fork();

    if (pid == -1)
        perror("error in initiating the clock");

// here the first child >> clock forking
    else if (pid == 0)
    {
        char *argv[] = {"./clk.out", 0};
        execve(argv[0], &argv[0], NULL);
    }
    else
    {

      int  pid2 = fork();
        if (pid2 == -1)
            perror("error in initiating the scheduler");
// here the first child >> scheduler forking
        else if (pid2 == 0)
        {
            char *argv[] = {"./finalscheduler.out", &algorithim ,0};
            execve(argv[0], &argv[0], NULL);
        }
        else
        {
        printf("back to process genr\n");

// now the parent is the process generator
// initiate the clock and get the current timee by getClk()
            initClk();
            whatistimenow = getClk();
// Now the process generator will do his role >> which is send the process to scheduler at apporpiate time
// we can do this step as create a struct of the process that will send to the schedluer by a message queue

           int msgid = msgget(up_v,IPC_CREAT|0644); // unique message
            key_t msgqid;
            int send_val;
            struct messagequeuetoscheduler messagecontainprocessdata; //message to be sent from the Genrator contain the process


            messagecontainprocessdata.mtype = 7;               // aribitary value

            int processturn;

            while (!(isempty(storeprocessinqueue)))
            {

                processturn = storeprocessinqueue->head->thedataofprocess.arrivaltime;
                whatistimenow = getClk(); // getting the time now
                //The process genrator should sleep untill the arrival time of the process in turn


                sleep(processturn - whatistimenow); // if process arrivaltime is 3 and now is 1 >> the generator will sleep 2 >> and when it wakeup it will send the process
                // here we will store the data of process in message queue to be send ( so there , i will work on the head of the message queue)
                messagecontainprocessdata.processtobesend.processid = storeprocessinqueue->head->thedataofprocess.processid;
                messagecontainprocessdata.processtobesend.arrivaltime = storeprocessinqueue->head->thedataofprocess.arrivaltime;
                messagecontainprocessdata.processtobesend.runtime = storeprocessinqueue->head->thedataofprocess.runtime;
                messagecontainprocessdata.processtobesend.priority =  storeprocessinqueue->head->thedataofprocess.priority;
                messagecontainprocessdata.processtobesend.memsize =  storeprocessinqueue->head->thedataofprocess.memsize;
                dequeue(storeprocessinqueue);// the process that i read it and send it to the message queue will be dequeued from the storeprocessinqueue;
                int send_val = msgsnd(msgid, &messagecontainprocessdata, sizeof(messagecontainprocessdata.processtobesend),!IPC_NOWAIT);

                if (send_val == -1)
                    printf("error happened in sending the process");

            }
            printf("Process genrator wait to send the process\n");

            int status;
            int pid_wait = wait(&status);
            wait(&status);
            printf("Process genrator resumed\n");
            destroyClk(true);
        }
    }
}
void clearResources(int signum)
{
    //TODO Clears all resources in case of interruption
destroyClk(true);
exit(0);
}
