#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *ICSI333. System Fundamentals,
 *Spring 2022,
 *TA Sourav,
 *Kiran Aziz,
 *ID: 001440162
 */


/* 
 *Declaring the Node structure for nodes in the linked list.
 *Each node holds three fields:
 *  -an integer value, which is its index, 
 *  -a string value, which is the text, and
 *  -a pointer to the next node. 
 */
struct Node{
	int index;
	char *text;
	struct Node *next;
};


/*
 *The getSize function returns the size of the linked list by 
 * counting the number of nodes in the list.
 * @param head: struct Node that is the head of the linked list.
 * @return Integer value to indicate the size, or the number of nodes, of the linked list.
 */
int getSize(struct Node* head){
    int size = 0;  //Integer used to hold the value of linked list size, initialized to zero.

    //Iterates through each node and increments counter to reflect the size
    //until it reaches the end of the linked list.
    while(head != NULL){
        head = head->next;
        size++;
    }
    return size; //Returns current size of the linked list.
}


/*
 *The insertAfter function corresponds to the command "ina". The function does the following:
 *  (a) A new node with the text specified in the command must be inserted in the list 
 *      after a node whose index is equal to the number specified in the command, indexes 
 *      of the list should be changed to keep increasing order, and the following message 
 *      must be printed “Ok”.
 *  (b) If the list contains a node whose text is identical to the text specified in the 
 *      command, then no new node must be created, and the following message must be printed 
 *      “Such text exists already”.
 *  (c) If the list does not contain a node whose index is equal to the number specified 
 *      in the command, then a new node must be inserted at the end of the list, and the 
 *      following message must be printed “Text inserted at the end”.
 * @param index: Integer holding the index to where the newNode must be inserted after.
 * @param text: String, or character array, holding the text that will be inserted into the new node.
 * @param head: struct Node that is the head of the linked list.
 */
void insertAfterNthNode(int index, char *text, struct Node** head){
    int size = getSize(*head);  //Gets size of the linked list currently.
    struct Node* temp = *head;  //Temporary node that holds the head of the list 
                                //for the eventual traversal of the linked list.
    
    //Iterates through the linked list to check if the list contains a node whose text
    //is identical to the text specified in the command. 
    //If yes, then no new node is created and a message is returned.
    while(temp != NULL){
        if(strcmp(temp->text, text) == 0){
            printf("Such text exists already\n"); fflush(stdout);
            return;
        }
        temp = temp->next;
    }
    
    //Creates newNode to be inserted after index specified in the command.
    struct Node* newNode; 
    if ((newNode = (struct Node *)malloc(sizeof(struct Node))) == NULL){
        printf("Node allocation failed. \n"); fflush(stdout);
        exit(1);    //Stops program.
    }

    //Space for newNode obtained. 
    //Copies the values of 'index' and 'text' into the node.
    newNode->index = index;
    newNode->text = malloc(strlen(text) + 1);
    strcpy(newNode->text, text);
    newNode->next = NULL;
    
    //The index must be a positive integer, where 'index' must be >= 1.
    //If it is less than 1, a message will be returned.
    if(index < 1){
        printf("Invalid position to insert\n"); fflush(stdout);
    }
    
    //If the list is empty, which means the size is 0, then the first node will
    //be the head of the list with a message.
    else if(size == 0){
        newNode->next = *head; 
        *head = newNode;
        printf("Text inserted at the end\n"); fflush(stdout);
    }
    
    //If the index is greater than or equal to 1, but no nodes whose index
    //is equal to the index specified in the command, then a new node is
    //inserted at the end of the list with a message.
    else if(index>size){
        temp = *head;   //Resetting temporary node back to the head of the linked list for traversal.
        
        while(temp->next != NULL){
            temp = temp->next;
        }

        temp->next = newNode;
        newNode->index=getSize(*head);  //Sets index of newNode to be the size of the 
                                        //list since it is added to the end of the list.
        
        
        printf("Text inserted at the end\n"); fflush(stdout);
    }       
    
    //If there is a node where the index specified in the command exists, then
    //the newNode is inserted after that specific index.
    else{
        int count = 1;  //Setting 'count' as the index of the temporary node, and will aid in 
                        //adjusting the indices in the list.
        temp = *head;   //Resetting temporary node back to the head of the linked list for traversal.

        //Iterates through list until the desired index and corresponding node
        //is found while incrementing count.
        while (temp->next != NULL) {
            if (count == index){
                break;
            }
            count++;
            temp = temp->next;
        }

        temp->index=count;          //Sets index of temporary node to 'count'.
        newNode->index=(count+1);   //Sets index of newNode to be 'count' plus 1.
        newNode->next= temp->next;  //Sets newNode's next to be the temp node's next.
        temp->next = newNode;       //Sets temp node's next to be the newNode. Therefore, the newNode is inserted after
                                    //the nth node in the list.
        
        //Iterates through list once more, but instead of starting at the
        //head of the list, it starts at the newNode.
        //Then, fixes the indices of the nodes that follow the newNode in the list.
        while (temp->next != NULL) {
            //If the index of the previous node is equal to the index of the next node,
            //update the index of the next node by one.
            if (temp->index == temp->next->index){
                temp->next->index = (temp->index + 1);
            }

            temp = temp->next;
        }
        printf("Ok\n"); fflush(stdout);
    }
}


/*
 *The insertBefore function corresponds to the command "inb". The function does the following:
 *  (a) A new node with the text specified in the command must be inserted in the list before 
 *      a node whose index is equal to the number specified in the command, indexes of the 
 *      list should be changed to keep increasing order, and the following message must be 
 *      printed “Ok”.
 *  (b) If the list contains a node whose text is identical to the text specified in the 
 *      command, then no new node must be created, and the following message must be printed 
 *      “Such text exists already”.
 *  (c) If the list does not contain a node whose index is equal to the numberspecified in 
 *      the command, then a new node must be inserted at the beginning of the list, indices 
 *      of the list should be changed to keep increasing order, and the following message must 
 *      be printed “Text inserted at the beginning”.
 * @param index: Integer holding the index to where the newNode must be inserted before.
 * @param text: String, or character array, holding the text that will be inserted into the newNode.
 * @param head: struct Node that is the head of the linked list.
 */
void insertBeforeNthNode(int index, char *text, struct Node** head){
    int size = getSize(*head);  //Gets size of the linked list currently.
    struct Node* temp = *head;  //Temporary node that holds the head of the list 
                                //for the eventual traversal of the linked list.
    
    //Iterates through the linked list to check if the list contains a node whose text
    //is identical to the text specified in the command. 
    //If yes, then no new node is created and a message is returned.
    while(temp != NULL){
        if(strcmp(temp->text, text) == 0){
            printf("Such text exists already\n"); fflush(stdout);
            return;
        }
        temp = temp->next;
    }
    
    //Creates newNode to be inserted before index specified in the command.
    struct Node* newNode; 
    if ((newNode = (struct Node *)malloc(sizeof(struct Node))) == NULL){
        printf("Node allocation failed. \n"); fflush(stdout);
        exit(1);    //Stops program.
    } 

    //Space for newNode obtained. 
    //Copies the values of 'index' and 'text' into the node.
    newNode->index = index;
    newNode->text = malloc(strlen(text) + 1);
    strcpy(newNode->text, text);
    newNode->next = NULL;
    
    //The index must be a positive integer, where 'index' must be >= 1.
    //If it is less than 1, a message will be returned.
    if(index < 1) {
        printf("Invalid position to insert\n"); fflush(stdout);
    }
    
    //If the index is greater than or equal to 1, but no nodes whose index
    //is equal to the index specified in the command, then a new node is
    //inserted at the beginning of the list, at the head, with a message.
    else if(index>size){
        newNode->next = *head;
        *head = newNode;
        
        int count = 1;  //Setting 'count' to be the index of each node in list, starting with 1 for the head.
        temp = *head;   //Resetting temporary node back to the head of the linked list for traversal.
        
        //Iterates through list once more while fixing the indices of the nodes,  
        //that follow the newNode in the list.
        //Indices start at 1 and each following node's index is increasing by 1.
        while (temp != NULL) {
                temp->index = count;
                count++;
            temp = temp->next;
        }
        printf("Text inserted at the beginning\n"); fflush(stdout);
    }    

    //If the index specified in the command is 1, then the newNode will be inserted
    //before the head of the list with a message. This means it will make it the new head
    //of the list while also returning a message.
    else if(index == 1){
        newNode->next = *head; 
        *head = newNode;
        
        int count = 1;  //Setting 'count' to be the index of each node in list, starting with 1 for the head.
        temp = *head;   //Resetting temporary node back to the head of the linked list for traversal.
        
        //Iterates through list once more while fixing the indices of the nodes,  
        //that follow the newNode in the list.
        //Indices start at 1 and each following node's index is increasing by 1.
        while (temp != NULL) {
            temp->index = count;
            count++;
            temp = temp->next;
        }
        printf("Ok\n"); fflush(stdout);
    }
    
    //If there is a node where the index specified in the command exists, then
    //the newNode is inserted before that specific index.
    else{
        int count = 1;  //Setting 'count' as the index of the temporary node, and will aid in 
                        //adjusting the indices in the list.
        temp = *head;   //Resetting temporary node back to the head of the linked list for traversal.
        
        //Iterates through list until the desired index and corresponding node
        //is found while incrementing count.
        while (temp->next != NULL) {
            if (count == (index - 1)){
                break;
            }
            count++;
            temp = temp->next;
        }

        temp->index=count;          //Sets index of temporary node to 'count'.
        newNode->index=(count+1);   //Sets index of newNode to be 'count' plus 1.
        newNode->next= temp->next;  //Sets newNode's next to be the temp node's next.
        temp->next = newNode;       //Sets temp node's next to be the newNode. Therefore, the newNode is inserted after
                                    //the nth node in the list.
        
        //Iterates through list once more, but instead of starting at the
        //head of the list, it starts at the newNode.
        //Then, fixes the indices of the nodes that follow the newNode in the list.
        while (temp->next != NULL) {
            //If the index of the previous node is equal to the index of the next node,
            //update the index of the next node by one.
            if (temp->index == temp->next->index){
                temp->next->index = (temp->index + 1);
            }

            temp = temp->next;
        }
        printf("Ok\n"); fflush(stdout);
    }
}

/*
 *The delete function corresponds to the command "del". The function does the following:
 *  (a) If the list contains a node whose index is equal to the number specified in 
 *      the command, then the node must be removed from the list, indexes of the list 
 *      should be changed to keep increasing order, and the following message must be 
 *      printed “Deleted”.
 *  (b) If the list does not contain a node whose index is equal to the number specified 
 *      in the command, then the program must leave the list unchanged, and the following 
 *      message must be printed “No such index”.
 * @param index: Integer holding the index for the node to be deleted.
 * @param head: struct Node that is the head of the linked list.
 */
void delete(int index, struct Node** head){
    int size = getSize(*head);  //Gets size of the linked list currently.
    struct Node* temp = *head;  //Temporary node that holds the head of the list 
                                //for the eventual traversal of the linked list.
    struct Node* previous;      //Node to hold previous node during traversal.

    
    //The index of the node to be deleted must be within the list.
    //Therefore, the index specified in the command must be a positive 
    //integer, where 'index' must be >= 1 and an integer smaller than the 
    //size of the list itself.
    //If it is less than 1 or greater than the size, a message will 
    //be returned.
    if(index < 1 || index > size){
        printf("No such index\n"); fflush(stdout);
    }
    
    //If the index specified in the command is 1, then the node to be deleted
    //is the head of the list with a message. 
    //This means the second node will become the new head of the list while 
    //also returning a message.
    else if(index == 1){
        //Moves head to the next node in the list.
        *head = (*head)->next;
        
        int count = 1;  //Setting 'count' to be the index of each node in list, starting with 1 for the head.
        temp = *head;   //Resetting temporary node back to the head of the linked list for traversal.
        
        //Iterates through list to fix the indices of the nodes that follow the 
        //new head of the list.
        //Indices start at 1 and each following node's index is increasing by 1.
        while (temp != NULL) {
            temp->index = count;
            count++;
            temp = temp->next;
        }
        
        printf("Deleted\n"); fflush(stdout);
        free(temp); //Completely removes the previous head of the list by deallocating the
                    //memory assigned to it.
    }
    
    else{
        //Iterates through the list until it reaches a node whose index is equal 
        //to the number specified in the command
        while (--index) {
            //Stores the previous node since previous node's next will be changed.
            previous = temp; 
            temp = temp->next; 
        }
        //Changes previous node's next node to temp node's next node.
        //Creates a link where the deleted node is no longer included in the list.
        previous->next = temp->next;
        
        int count = 1;  //Setting 'count' to be the index of each node in list, starting with 1 for the head.
        temp = *head;   //Resetting temporary node back to the head of the linked list for traversal.
        
        //Iterates through list to fix the indices of the nodes that 
        //follow the deleted node of the list.
        //Indices start at 1 and each following node's index is increasing by 1.
        while (temp != NULL) {
            temp->index = count;
            count++;
            temp = temp->next;
        }
        
        printf("Deleted\n"); fflush(stdout);
        free(temp); //Completely removes the node of the list by deallocating the
                    //memory assigned to it.
    }
}

/*
 *The replace function corresponds to the command "rep". The function does the following:
 *  (a) If the list contains a node whose index is equal to the number specified in 
 *      the command, then the node text must be replaced with the text specified in the 
 *      command, and the following message must be printed “Replaced”.
 *  (b) If the list contains a node whose text is identical to the text specified in 
 *      the command, then the program must leave the list unchanged, and the following 
 *      message must be printed “Such text exists already”.
 *  (c) If the list does not contain a node whose index is equal to the number specified 
 *      in the command, then the program must leave the list unchanged, and the following 
 *      message must be printed “No such index”.
 * @param index: Integer holding the index for the node to be replaced.
 * @param text: String, or character array, holding the text that will be replaced.
 * @param head: struct Node that is the head of the linked list.
 */
void replace(int index, char *text, struct Node **head){
    int size = getSize(*head);  //Gets size of the linked list currently.
    struct Node* temp = *head;  //Temporary node that holds the head of the list 
                                //for the eventual traversal of the linked list.
    

    //Iterates through the linked list to check if the list contains a node whose text
    //is identical to the text specified in the command. 
    //If yes, then no new node is created and a message is returned.
    while(temp != NULL){
        if(strcmp(temp->text, text) == 0){
            printf("Such text exists already\n"); fflush(stdout);
            return;
        }
        temp = temp->next;
    }
    
    //The index of the node to be deleted must be within the list.
    //Therefore, the index specified in the command must be a positive 
    //integer, where 'index' must be >= 1 and an integer smaller than the 
    //size of the list itself.
    //If it is less than 1 or greater than the size, a message will 
    //be returned.
    if(index < 1 || index > size){
        printf("No such index\n"); fflush(stdout);
        return;
    }
    
    temp = *head;   //Resetting temporary node back to the head of the linked list for traversal.
    
    //Iterates through the list until it reaches a node whose index is equal 
    //to the number specified in the command.
    while (--index) {
        temp = temp->next; 
    }
    
    //Copies the text specified in the command to the text in the temp node.
    strcpy(temp->text, text);
    
    printf("Replaced\n"); fflush(stdout);
}


/*
 *The printList function corresponds to the command "prn". 
 *If the list is empty, it prints the message “The list is empty”. 
 *Otherwise, it traverses the list in the increasing order of 
 *indices and prints each index and the corresponding text on a line by itself. 
 * @param head: struct Node that is the head of the linked list.
 */
void printList(struct Node* head){
    if(head == NULL){
        printf("The list is empty\n"); fflush(stdout);
    }else{
        while(head!=NULL){
            printf("%d %s\n",head->index, head->text); fflush(stdout);
            head = head->next;
        }
    }
}


/*
 *The freeList function deallocates/frees the memory used by every node in the 
 linked list. Only called after the command "end".
 * @param head: struct Node that is the head of the linked list.
 */
void freeList(struct Node *head) {
    struct Node *temp;

    //Traverses the list and frees each node in the list, including its text, until it 
    //reaches the end of the list.
    while(head != NULL){
      temp = head;
      head = head->next;
      free(temp->text);
      free(temp);
    }
}


/*
 *The main function performs an interactive program that prompts the user for commands,
 *accepts commands from the keyboard (stdin) and executes those commands. When a command 
 *requires output, it is written to stdout. It will continue to accept and process 
 *commands until the user types the command "end". The list of commands and syntax are:
 *      Command Insert After:   ina num str, Inserts newNode after specified index, if index is valid.
 *      Command Insert Before:  inb num str, Inserts newNode before specified index, if index is valid.
 *      Command Delete:         del num, Deletes node at specified index, if index is valid.
 *      Command Replace:        rep num str, Replaces text of node at specified index, if index is valid.
 *      Command Print List:     prn, Prints out linked list.
 *      Command End:            end, Ends program

 *It uses a linked list, where each node contains a string(text), a positive integer(index), and
 *a pointer to the next node in the list. The linked list at all times:
 *      1) The index is a number of the node in the list, i.e., the first 
 *         node has index 1, and when the list is scanned from the beginning
 *         to the end, the value of indexes is increasing by 1.
 *      2) The texts appearing in the list are all distinct; that is, no two nodes
 *         have the same text.
 */
int main(){
    struct Node *head = NULL;  //Creates head, which is an empty linked list.
    
    char command[4];    //Character array of size 4 to hold the user command as a string.
                        //Size 4 to hold 3 chars for the command, and the terminating symbol.
    
    int index;          //Integer to hold integer number specified in the user's command.
                        //Always a postive integer value.
    
    char text[256];     //Character array of size 256 to hold string specified in the user's command.
                        //Size 256 to hold 255 chars for the text, and the terminating symbol.

    
    printf("Command? ");  fflush(stdout);   //Prompts the user for a command.
    scanf("%3s", command);                  //Reads the command.
    

    //While the user's command is not "end":
    while(strcmp(command, "end") != 0){

        //Inserts newNode after specified index, if index is valid.
        if(strcmp(command, "ina") == 0){
            //Reads the values for the command.
            scanf("%d%s", &index, text);
            insertAfterNthNode(index, text, &head);
        }
        
        //Inserts newNode before specified index, if index is valid.
        else if(strcmp(command, "inb") == 0){
            //Reads the values for the command.
            scanf("%d%s", &index, text);
            insertBeforeNthNode(index, text, &head);
        }
        
        //Deletes node at specified index, if index is valid.
        else if(strcmp(command, "del") == 0){
            //Reads the value for the command.
            scanf("%d", &index);
            delete(index, &head);
        }
        
        //Replaces text of node at specified index, if index is valid.
        else if(strcmp(command, "rep")== 0){
            //Reads the values for the command.
            scanf("%d%s", &index, text);
            replace(index, text, &head);
        }
        
        //Prints out linked list.
        else if(strcmp(command, "prn") == 0){
            printList(head);
        }
        

        printf("Command? ");  fflush(stdout);   //Prompts the user for the next command.
        scanf("%s", command);                   //Reads the next command.
    }

    //Frees linked list.
    freeList(head);
    return 0;
}
