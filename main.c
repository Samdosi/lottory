

// link list structure
typedef struct node{
    int data;
   struct node* next;
}node;


// function prototype
node* insert_back(node* front, int num);
node* RemoveNodes(struct node* front, int numPeople, int numSkip, int numWinner);
void free_list(node* front);


#include <stdio.h>
#include <stdlib.h>
# define maxwinner 1000000


int main(){
    int testCases, numberOfGroup, i, j;
    int NumPeople=0, NumSkip=0, NumThre=0;
    int arr_winner[maxwinner] ;
    node* ptr_front=(node*)malloc(sizeof(node));
    ptr_front=NULL;
    scanf("%d", &testCases);
    while(testCases != 0)
    {
        // intial every value to 0 for each group
        NumPeople=0;
        NumSkip=0;
        NumThre=0;
        scanf("%d", &numberOfGroup);
        for(i=0; i<numberOfGroup; i++)
        {
            scanf("%d %d %d", &NumPeople, &NumSkip, &NumThre);
            for(j=0; j<NumPeople; j++)
            {
                // creating the link list for each group
                ptr_front=insert_back(ptr_front, j+1);
           }
            printf("Group #%d:\n", i+1);
            // eliminate the loosers and remove the node from the linked list
         ptr_front=RemoveNodes(ptr_front, NumPeople, NumSkip, NumThre);
            // storing the winners from each group into the array
        arr_winner[i+1]=ptr_front->data;
            // setting the front ptr to Null and get ready for the next group
            ptr_front=NULL;
            
        }
        testCases --;
        // assuming the winner is the first person from the first group
        int winner=arr_winner[1];
        int gp=1;
            for(i=2; i<numberOfGroup+1; i++)
            {   // comparing the winner from each group and find the smallest number
                if(arr_winner[i]<winner){
                    // update the winner
                    winner=arr_winner[i];
                    // checking for the smallest group and update if necessary
                    if(i>gp && gp != 1) continue;
                        gp=i;
                    
                }
            }
        ptr_front=NULL;
        printf("Lottery winner is person %d from group %d.\n", winner, gp);
        // free the whole list
        free_list(ptr_front);
    
    }
    
    return 0;
}
// making the linked list and return the pointer to the front of the list
node* insert_back(node* front, int num)
{
    node *temp, *iter;
    temp=(node*)malloc(sizeof(node));
    temp->data=num;
    // list is empty
    if(front==NULL)
    {
        temp->next=temp;
        return temp;
    }
    // add to an exsiting list
    else
    {
        // setting the temp pointer to the beginning of the list
        temp->next= front;
        iter=front ;
        // looking for the last element in the list
        while(iter->next != front)
        {
            iter=iter->next;
        }
        // update the pointer
        iter->next=temp ;
        return front;
    }
    
}
// remove the nodes and return the pointer to the beginning of the list
node* RemoveNodes( node* front, int numPeople, int numSkip, int numWinner) {
    
  // check to see if list is empty
  if (front == NULL)
        return front;
    node* temp;
    temp=front;
    node* del=(node*)malloc(sizeof(node));
    // finding the winners
  while (numPeople != numWinner ) {
      // skip to the player that gets eliminated
      for(int i=0; i<numSkip-1; i++){
          temp = temp->next;}
        del = temp->next;
      if(del==front)
          front=del->next;
      printf("%d\n", del->data);
          temp->next=del->next;
        temp=del->next;
        free(del);
      numPeople--;
  }
    return front;
}
void free_list(node* front)
{
    if(front != NULL)
    {
        free_list(front->next);
        free(front);
    }
}
