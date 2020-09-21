#include "queueofstructs.h"
#include "phase2.h"
#include <stdlib.h>
#include <stdio.h>
#include "headers.h"

int up_v=12345;
int main(int argc, char * argv[])
{


     FILE * outputfile;
     FILE * phase2;


     // creating the ready and finished queue

     struct linkedlist_as_queue * readyqueue ,b;
     readyqueue=&b;
     readyqueue = createqueue();
     struct linkedlist_as_queue * finishedqueue,d;
     finishedqueue=&d;


     finishedqueue = createqueue();

     int msgid;
     int receieve_or_not;
     struct node * pointer_to_messagequeue,a;
     pointer_to_messagequeue=&a;

     int finishedtime, waitingtime;
     double averagewaitingtime;
     double averageturnaroundtime;





     printf("Now the scheduler is initiated by initClk()\n");
    initClk();
    struct treenode * ourstart_tree ,pp;
    ourstart_tree=&pp;


    ourstart_tree = drawtree(1024);

    struct  treenode *returnedfrom_storing,i;
    returnedfrom_storing=&i;

    printf("pahse two begin\n");

    //// initialize the begin and end of the treenode that we will need to free it
    int beginof_returnedfrom_storing=0;
    int endof_returnedfrom_storing=0;

    // array to store the end and begin
    int * begin_and_end;
    outputfile = fopen("output.txt", "w");
    phase2 = fopen("meomry.log", "w");

    // Non preemptive HPF priority
    if (*argv[1] == 'a')
    {

        printf("Non preemptive HPF Algorithm choosed by the user\n");
          printf("al3eeb fi mess\n");

        // fi erroe hana

        struct messagequeuetoscheduler sentmessage;
         printf("iams in the7 \n");

        msgid = msgget(up_v,IPC_CREAT|0644);
         printf("iam in the x \n");
        struct process * temp,rw;
        temp=&rw;
         printf("iam in the \n");


        while (1)
        {
            // now i will receive the data from the msgsnd
             receieve_or_not = msgrcv(msgid, &sentmessage, sizeof(sentmessage), 0, IPC_NOWAIT);
            // checking of the message recived or not
            if (receieve_or_not == -1)
            {
                printf("no message sent by the process generator\n");
            }
             printf("iam in the \n");


            pointer_to_messagequeue-> thedataofprocess = sentmessage.processtobesend ;
            sortingthequeue_basedon_priority_HPF (readyqueue , pointer_to_messagequeue);
            printf("iam in the gead of scheduler\n");
    //now to scheduler will work on the head of the ready queue

        int pid = fork();

    if (pid == -1)
        perror("error in working on the process\n");
    // now working on the process
    else if (pid == 0)
    {
        printf("process intaizlize din shceduler\n");
        int memsize_of_frontprocess = readyqueue->head->thedataofprocess.memsize;
    // the begin_and_end_memsize is array contain begin and end

        returnedfrom_storing = storeprocessmeomrysize (memsize_of_frontprocess , ourstart_tree );

       beginof_returnedfrom_storing =returnedfrom_storing->beginsize;

       endof_returnedfrom_storing=  returnedfrom_storing -> endsize;

       begin_and_end[0]=beginof_returnedfrom_storing;
        begin_and_end[1]=endof_returnedfrom_storing;

        int allocatedvalue=begin_and_end[1] - begin_and_end[0];

        char runtimeof_front_process [2];
        sprintf( runtimeof_front_process , "%d" , readyqueue->head->thedataofprocess.runtime );
        int arrivaltimeof_front_process = readyqueue->head->thedataofprocess.arrivaltime ;
        int process_id_of_frontprocess = readyqueue->head->thedataofprocess.processid;

        int timenow = getClk();
        // will work if the currenttime == the arrival time of the process on the front
        if (timenow >= arrivaltimeof_front_process)
        {
           int currenttime=getClk();
             int arrivaltimeof_front_process = currenttime - arrivaltimeof_front_process;
            fprintf (outputfile,"At time : %d , process id : %d , started , arrivaltime: %d , waited %d", timenow , process_id_of_frontprocess, arrivaltimeof_front_process,arrivaltimeof_front_process );
            fprintf (phase2 ,"At time : %d , allocated : %d ,for process : %d , from : %d  , to: %d ", timenow ,allocatedvalue ,process_id_of_frontprocess, begin_and_end[0],begin_and_end[1] );

            char *argv[] = {"./process.out",runtimeof_front_process, 0};
            execve(argv[0], &argv[0], NULL); //// forking the processes
            // finishedtime= currenttime + runtimeof_front_process;
            fprintf (outputfile , " process id : %d , finishedtime: %d", process_id_of_frontprocess ,finishedtime );
            make_the_stored_node_is_empty(returnedfrom_storing,begin_and_end);

             fprintf (phase2 ,"At time : %d , freed  : %d ,for process : %d , from : %d  , to: %d ", timenow ,getClk() ,process_id_of_frontprocess, begin_and_end[0],begin_and_end[1] );
        dequeue(readyqueue );
        enqueue(finishedqueue , readyqueue->head->thedataofprocess ) ;

            exit(0);

        }

    }
    /// here we come back again to schduler

    else
    {
        int status;
        pid = wait(&status);
        if(WIFEXITED(status))
          	printf("\nA child with pid %d terminated with exit code %d\n", pid, WEXITSTATUS(status));

    }


        }

        free(ourstart_tree);

    destroyClk(true);
    }
}
