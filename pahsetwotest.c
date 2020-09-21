#include "phase2.h"
#include <stdio.h>
#include <stdlib.h>
struct process
{
	int pid;
	int arrivaltime;
	int runtime;
	int priority;
	int memsize;
};

int main ()
{
		//// initialize the begin and end of the treenode that we will need to free it
int beginof_returnedfrom_storing=0;
int endof_returnedfrom_storing=0;
// array to store the end and begin
int  begin_and_end[2];
FILE * phase2;
phase2 = fopen("meomry.log123", "w");

struct process rw;
struct process * pro;
pro=&rw;
int x = pro-> memsize = 145 ;
struct treenode * ourstart_tree ;


ourstart_tree=drawtree(1024);

struct  treenode * returnedfrom_storing;

 returnedfrom_storing = storeprocessmeomrysize (x , ourstart_tree );
 struct  treenode i;
 returnedfrom_storing=&i;

 beginof_returnedfrom_storing =returnedfrom_storing->beginsize;
endof_returnedfrom_storing=  returnedfrom_storing -> endsize;

begin_and_end[0]=beginof_returnedfrom_storing;
begin_and_end[1]=endof_returnedfrom_storing;

int allocatedvalue=begin_and_end[1] - begin_and_end[0];
fprintf (phase2 ,"At timime %d is alloecated  , from : %d  , to: %d ",allocatedvalue , begin_and_end[0],begin_and_end[1] );
}
