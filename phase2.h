
#include <stdio.h>
#include <stdlib.h>

struct treenode
{
    int nodevalue;
    int beginsize;
    int endsize;
    int fullornot;
    struct treenode *leftchild;
    struct treenode *rightchild;
};


struct treenode * drawtree(int value)
{
	struct treenode * ptr ;//= (struct treenode *)malloc(value);
	struct treenode o;
	ptr=&o;
	ptr -> nodevalue = value;
    ptr ->beginsize = 0;
    ptr ->endsize = value - 1;
    ptr ->fullornot = 0;
    return ptr;
}


struct treenode * destroythenodetotwochildren (struct treenode * node)
{
    struct treenode t;
    node=&t;
	if (node -> nodevalue == 8)
		return node ;
	//leftchilddata
	node -> leftchild = drawtree((node-> nodevalue)/2);
	node ->leftchild->beginsize = node->beginsize;
    node->leftchild->endsize = (node->beginsize + node->nodevalue / 2 ) - 1;
    node->leftchild-> fullornot= 0;

    //rightchilddata
	node -> rightchild = drawtree((node-> nodevalue)/2);
	node ->rightchild->beginsize = (node -> leftchild -> endsize ) + 1 ;
    node-> leftchild-> endsize = node -> nodevalue -1 ;
    node -> rightchild-> fullornot= 0;

    return node ;

}


struct treenode *  storeprocessmeomrysize (int processmeomrysize, struct treenode * returnednode  )
{
	int begin;
	int end;
	int begin_and_end_array[2];
	int successed[1];
	struct treenode p;
    returnednode=&p;
    struct treenode fra;
    struct treenode * returnedtreenode;
    returnedtreenode=&fra;

	if ( processmeomrysize > 0 && processmeomrysize <= 256)
	{
		if ( returnednode -> fullornot == 0)
		{
			// if the value = 17 >> it will check if 17 <= 32 and 17 > 16 it will stored in 32
			if ((processmeomrysize <= returnednode -> nodevalue) && (processmeomrysize > (returnednode->nodevalue) / 2))
			{
				begin = returnednode->beginsize;
            	end = returnednode ->endsize;
            	returnednode -> fullornot = 1;  // the node is now has stored process
            	returnedtreenode -> beginsize= begin;
                returnedtreenode -> endsize= end;
                return returnedtreenode;



			}

			else
			{
				struct treenode * destroyed ;
				destroyed = destroythenodetotwochildren(returnednode);
				if ((processmeomrysize <= destroyed -> leftchild -> nodevalue) && (processmeomrysize > (destroyed -> leftchild -> nodevalue) / 2))
				{
					begin = destroyed -> leftchild ->beginsize;
            		end = destroyed -> leftchild ->endsize;
            		destroyed -> leftchild -> fullornot = 1;  // the leftnode is now has stored process
            		returnedtreenode -> beginsize= begin;
                    returnedtreenode -> endsize= end;
                    return returnedtreenode;
            		storeprocessmeomrysize ( processmeomrysize, destroyed -> leftchild  );
				}

				if ((processmeomrysize <= destroyed -> rightchild -> nodevalue) && (processmeomrysize > (destroyed -> rightchild -> nodevalue) / 2))
				{
					begin = destroyed -> rightchild ->beginsize;
            		end = destroyed -> rightchild ->endsize;
            		destroyed -> rightchild -> fullornot = 1;  // the leftnode is now has stored process
            		returnedtreenode -> beginsize= begin;
                    returnedtreenode -> endsize= end;
                    return returnedtreenode;
            		storeprocessmeomrysize ( processmeomrysize, destroyed -> rightchild  );
				}

			}

		}
		if ( returnednode -> fullornot == 1)
		{
			printf("false storeprocessmeomrysize, all nodes ar fulled now ");
			successed[0] = 0;
			return returnedtreenode; // not storing the meomry size
		}


	}
    // the reading from file has problem as the memsize bigger than 256 or smaller than 1
	else
	{
			printf("false storeprocessmeomrysize, the meomry size should be in range 0 between 256 , you e ");
			successed[0]=0;
			return returnedtreenode; // not storing the meomry size
	}

}

int make_the_stored_node_is_empty(struct treenode * nodetobeemppty,int * begin_and_end)
{
        struct treenode z;
    nodetobeemppty=&z;

			if(nodetobeemppty->fullornot==1)
			{
				nodetobeemppty->fullornot=0;
				return 1;

			}


		if (make_the_stored_node_is_empty (nodetobeemppty->leftchild , begin_and_end)  )

		{
			return 1;
		}

		if (make_the_stored_node_is_empty(nodetobeemppty->rightchild , begin_and_end))
		{
			return 1;
		}


}
