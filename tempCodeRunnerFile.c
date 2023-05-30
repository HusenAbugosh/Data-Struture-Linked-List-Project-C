// Husain Abugosh/ حسين ابوغوش / 1210338 / sec:5
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

//////// Structures and the implemntation of the double linked List //////

/*
doubly linked list: its a list of node each node have 3 spaces in it :

  data: space to store the data in it;
  next: pointer thats point to the next node;
  prev: pointer thats point to the previous node;

          list👇🏽       |            Nodes👇🏽                      |  tail 👇🏽
  |null/data/next| ->  <_|prev/data/next| -> <_|prev/data/next| ->   <_ |prev/data/null| -> Null

  disadvantages?  >yes its take more space than the single linked list cuse of the prev pointer.
*/

typedef struct Node{

  // each node will contain these 4 attributes:
  int data;
  char sign;
  struct Node *next;
  struct Node *prev;

} Node;

// will lock about sapce place for a node in the memo
Node *create_Node(int data){

  // TO find a space in memo to create a node:
  Node *newNode = (Node *)(malloc(sizeof(Node)));

  // if there is no space in the memo:
  if (newNode == NULL){
    printf("Out of memory!\n");
  }
  // to insert the data and set up the pointers
  newNode->data = data;
  newNode->next = NULL;
  newNode->prev = NULL;
  return newNode;
}

// to insert a new node into the linked list
void insert(Node **list, int data){

  Node *new_node = create_Node(data);    //<--create a node:
  //if this list does not have nay node befor the new node will the first node 
  if (*list == NULL){
    *list = new_node;
  }else{
  //if the list have a nodes the new node will be after the pervios tail(node->next = null)
    Node *current_node = *list;
    while (current_node->next != NULL){
      current_node = current_node->next;
    }
    //move the postion to the next node:
    current_node->next = new_node;
    new_node->prev = current_node;
  }
}

// to print the data of each node in givven list:
void display(Node *list){

  Node *current_node = list;
  printf("%c", current_node->sign); //<-- to print the sign of the int
  while (current_node != NULL){
    printf("%d > ", current_node->data);
    current_node = current_node->next;
  }
  printf("\n");
}

// to delete alist :
void deleteList(Node **list){

  Node *current_node = *list;
  Node *next_node;
  while (current_node != NULL){

    next_node = current_node->next; //<-- to save the next node before deleting the current node
    if (current_node->prev != NULL){
      current_node->prev->next = NULL; //<-- to set the next pointer of the previous node to null
    }

    free(current_node);       // Free the memory allocated for the current node
    current_node = next_node; // Move to the next node in the list
  }
  *list = NULL; // Set the list pointer to NULL, indicating the list is empty
}

// to reverse the list(the head will be the tail and the opposite is true)
Node *reverse(Node *head){

  Node *current_node = head;
  Node *temp = NULL;

  while (current_node != NULL){

    temp = current_node->prev; 
    current_node->prev = current_node->next;
    current_node->next = temp;
    current_node = current_node->prev;
  }

  // Update the head of the reversed list
  if (temp != NULL){
    head = temp->prev;
  }

  return head;
}

// to caluclate the size of linked list:
int sizeOf(Node *head){
  Node *current_node = head;
  int size = 0; //<-- couter to count how many node the list have till the tail
  while (current_node != NULL){
    size++;
    current_node = current_node->next;
  }
  return size;
}

// to comapre between 2 lists:
int isGreaterOrEqual(Node* list1, Node* list2) {
    int size1 = sizeOf(list1);
    int size2 = sizeOf(list2);
    
    //if list1 have bigger size it is greater
    if(size1 > size2) 
        return 1;
    //if list2 is bigger size it is greater
    else if(size1 < size2)
        return 0;

    //if both lists have the same size we will compare node by node from left to right
    Node* current_node1 = list1;
    Node* current_node2 = list2;
    
    while(current_node1 != NULL) {
        if(current_node1->data > current_node2->data)
            return 1;
        else if(current_node1->data < current_node2->data)
            return 0;
        //move to the next nodes
        current_node1 = current_node1->next;
        current_node2 = current_node2->next;
    }

    // if the 2 list have the same size&same numbers in it they will be equal:
    return 2;
}

////////  END of Structures and the implemntation of the double linked List //////

void print_file_numbers(){

  FILE *file = fopen("numbers.txt", "r"); //<-- will open the wanted file & put it on the reading mode.
   // this if-statment used to check if there any error with openning the file.
  if (file == NULL){
    printf("*ERROR: File couldn't be opened*\n");
  }

  char character;     //<-- will save the digit of the numbers in the file as character.
  // while the character its not the End of the file keep checking the character if its a digit or not  :
  while ((character = fgetc(file)) != EOF){

    if (isdigit(character) || character == '-'){
      // the character is a digit.
      printf("%c", character); //<--  will print the digit.
    }else{
      printf("\n");
    }
  }
  fclose(file);
}

/*insert_line: will take the target line that contain the wnated int and will take the list want
complexity = O(n+m) where is n the number of lines and m is the number of characters in the target line*/ 
Node *insert_line(int targetLine, Node *list){

  FILE *file = fopen("numbers.txt", "r"); //<-- will open the wanted file and put on the reading mode.
  // this if-statment used to check if there any error with openning the file:
  if (file == NULL){
    printf("*ERROR: file couldn't be opened*");
    return NULL;
  }

  int currentLine = 1; //<-- this var will tracking the nubers of line in the file.
  char character;      //<-- will save the  character in it.

  // while we did not reach the target line(the line that contain int that user chosed) incrse the currentLine
  while (currentLine < targetLine){

    character = fgetc(file); //<-- will keep taking a new char.
    // to check if we a newline that conatan a number in it
    if (character == '\n'){
      currentLine++; //<-- will increse the currentLine counter by one.
    }

    // if the target line did not found show the eroor message and close the file
    if (character == EOF){
      printf("Desired line does not exist in the file.\n");
      fclose(file);
      return NULL;
    }
  }

  int digit;
  int isNegative = 0;

  // this will print the digit that in the wanted int:
  while ((character = fgetc(file)) != EOF && character != '\n'){

    // if there any negative sign character thats mean the int is negative int:
    if (character == '-'){
       isNegative = 1;
    }else {
      // handle each character from the target int :
      digit = (character - '0'); //<--convert the type data from character to int
      insert(&list, digit);       //<--insert the digit into the given list
    }
  }
  // if the number contain a negative sign will add this to the head of the list:
  if(isNegative){
    list->sign = '-';
  }
  
  fclose(file); //<-- close the file
  return list;  //<-- return the list thats contain the digit of the wanted number;

}



/*sum operation function: will take 3 linked lists:
 list1: that conatin the 1st int, list2: that conatin the 2nd int, and return the resutlt)
 complexity of sum function: O(n), where is n-> the maximum number of nodes (digits) in either list1 or list2
 */
Node *Sum(Node *list1, Node *list2, Node *resultList){

    // if one of the lists does not have any elements(we will suppose its zeros) we will return the other list.
    if (list1 == NULL){
      return list2;
    }
    if (list2 == NULL){
      return list1;
    }

    // to reverse the list to let the ones be on the left(head) to do the sum operation:
    list1 = reverse(list1);
    list2 = reverse(list2);

    // to track the postion of the node:
    Node *currentNode1 = list1;
    Node *currentNode2 = list2;
    
    int carry = 0;   //<-- will handle the carry .
    int nodeSum = 0; //<-- will handle the sum result of the each data node.

    // while the currentNode1 or currentNode2 is not null (there is values in it keep moving)
    while (currentNode1 != NULL || currentNode2 != NULL){
      /*these if-statments cheack if the two int numbers have the same number of digit
      if one is have more the other one  the rsult will be the same digit:
      */
      if (currentNode1 == NULL){
        nodeSum = (currentNode2->data + carry) % 10; //<-- to held the sumof the node.
        carry = (currentNode2->data + carry) / 10;   //<-- to held the carry.
        insert(&resultList, nodeSum);                //<-- to insert the nodeSum into the result list.
        currentNode2 = currentNode2->next;           //<-- move to the next node of the list 2.
      }else if (currentNode2 == NULL){
        nodeSum = (currentNode1->data + carry) % 10; //<-- same of above but for the list1
        carry = (currentNode1->data + carry) / 10;   //<-- same of above but for the list1
        insert(&resultList, nodeSum);                //<-- same of above but for the list1
        currentNode1 = currentNode1->next;           //<-- same of above but for the list1
      }else{
        // to cheack if there any carry for the next node(if there any value > 9 the carry will be 1 if less carry=0)
        nodeSum = (currentNode1->data + currentNode2->data + carry) % 10; // eg: 9+9 = 18%10 = 8
        carry = (currentNode1->data + currentNode2->data + carry) / 10;   // eg: 9+9 = 18/10 = 1(there is a carry)
        // insert the nodeSum into the rsult list:
        insert(&resultList, nodeSum);
        // move to the next node:
        currentNode1 = currentNode1->next;
        currentNode2 = currentNode2->next;
      }
    }

    // to check if there remaining carry:
    if (carry > 0){
      insert(&resultList, carry);
    }
    // to let the ones be on the right as the normal present int way:
    return reverse(resultList); //<-- return the result list that contain the final values of sum.

}

/*sub operation function: will take 3 linked lists:
 list1: that conatin the 1st int, list2: that conatin the 2nd int, and return the resutlt)
 complexity of sum function: O(n), where is n-> the maximum number of nodes (digits) in either list1 or list2
 */
Node *Sub(Node *list1, Node *list2, Node *resultList){

    // if the first list is embty the result will be neagtion of list2
    if(list1 == NULL){
      //just will make the most right digit is negative:
      list1->data = -(list1->data); 
        return list1;
    }
    
     // if the 2nd list is embty the result will be 1st list:
    if(list2 == NULL){
        return list1;
    }
   
    // if the list1<list2 the result will be the same of list2-list1 with adding the negative signm to result
    if(isGreaterOrEqual(list2,list1)){
      resultList = Sub(list2,list1,resultList);
      resultList->sign = '-';
      return resultList;
    }

    // to reverse the list to let the ones be on the left to do the sum operation:
    list1 = reverse(list1);
    list2 = reverse(list2);
    // to track the postion of the node:
    Node *currentNode1 = list1;
    Node *currentNode2 = list2;

    int borrow = 0; //<-- will handle the borrow.
    while (currentNode1 != NULL){
        // if the 2nd list have a size less than the 1st we will fill the 2nd list with zero till we reach equal size with out insert it 
        int list2_data = (currentNode2 != NULL ? currentNode2->data : 0);
        int nodeSub;
        // to check the the  node of list1 want to borrow or not:
        if((currentNode1->data - borrow) < list2_data){
            nodeSub = currentNode1->data + 10 - borrow - list2_data;
            borrow = 1;
        } else {
            nodeSub = currentNode1->data - borrow - list2_data;
            borrow = 0;
        }

        insert(&resultList, nodeSub);
        currentNode1 = currentNode1->next;
        if(currentNode2 != NULL){
            currentNode2 = currentNode2->next;
        }
    }
    // we reverse to rrturn the number to normal form (most digit - - - -  least digit)
    resultList = reverse(resultList);
    return resultList;
}


// to handle each form of the add operations: 
Node* Add_operations(Node *list1, Node *list2, Node *resultList){

  // to check if there any list do nt have any values in it:
  if(list1 == NULL || list2 == NULL){
    printf("Error: One or both lists are null.\n");
    return NULL;
  }

  // \0 :represent the null in char data == the node does not have a sign.
  if(list1->sign == '\0' && list2->sign == '\0' ){
    resultList = Sum(list1,list2,resultList);
  }else if(list1->sign == '\0' && list2->sign == '-'){
    resultList = Sub(list1,list2,resultList);
  }else if(list1->sign == '-' && list2->sign == '\0'){
    resultList = Sub(list2,list1,resultList);
  }else if(list1->sign == '-' && list2->sign == '-'){
    resultList = Sum(list1,list2,resultList);
    resultList->sign = '-';
  }

  return resultList;
}

// to handle each form of the sub operations: 
Node* Sub_operations(Node *list1, Node *list2, Node *resultList){

  // to check if there any list do nt have any values in it:
  if(list1 == NULL || list2 == NULL){
    printf("Error: One or both lists are null.\n");
    return NULL;
  }

  // \0 :represent the null in char data == the node does not have a sign.
  if(list1->sign == '\0' && list2->sign == '\0' ){
    resultList = Sub(list1,list2,resultList);
  }else if(list1->sign == '-' && list2->sign == '\0'){
    resultList = Sum(list1,list2,resultList);
    resultList->sign = '-';
  }else if(list1->sign == '-' && list2->sign == '-'){
    resultList = Sub(list2,list1,resultList);
  }else if(list1->sign == '\0' && list2->sign == '-'){
    resultList = Sum(list1,list2,resultList);
  }

  return resultList;
}


// Function to perform multiplication of two linked lists
Node* Multiplication(Node* list1, Node* list2) {

  printf("1111");
  if (list1 == NULL || list2 == NULL) {
    printf("Error: One or both lists are null.\n");
    return NULL;
  }

  printf("222");

  Node* resultList = NULL;
  Node* currentNode1 = list1;

  printf("3333");

  while (currentNode1 != NULL) {
    printf("4444");
    Node* currentNode2 = list2;
    printf("555");
    Node* multResult = NULL;
    printf("6666");
    Node* tempResult = NULL;
    printf("777");
    int carry = 0;

    // Multiply each digit of list2 with the current digit of list1
    while (currentNode2 != NULL) {
      int mult = (currentNode1->data * currentNode2->data + carry);
      carry = mult / 10;
      mult %= 10;
      insert(&multResult, mult);
      currentNode2 = currentNode2->next;
    }

    if (carry > 0) {
      insert(&multResult, carry);
    }

    // Pad the result with zeros based on the position of currentNode1
    for (int i = 0; i < sizeOf(list1) - sizeOf(currentNode1); i++) {
      insert(&multResult, 0);
    }

    // Reverse the multiplied result list before adding it to the overall result
    multResult = reverse(multResult);

    // Add the multiplied result to the overall result list
    resultList = Sum(resultList, multResult, tempResult);
    deleteList(&resultList);
    resultList = tempResult;

    // Move to the next digit of the first number
    currentNode1 = currentNode1->next;
  }

  // Determine the sign of the result based on the signs of the input lists
  if ((list1->sign == '-' && list2->sign == '\0') || (list1->sign == '\0' && list2->sign == '-')) {
    resultList->sign = '-';
  } else {
    resultList->sign = '\0';
  }

  return resultList;
}




///// Main /////// 
int main(){

  int choice;              //<-- will store the choice of the user.
  int exitFlag = 0;        //<-- if the user rise the flag(exitFlag = 1) th loop will stop and close the programe.
  int didRead = 0;         //<-- the user shoud first choice th first choice to can select the operation.
  int number1, number2;    //<-- will save the number of lines that conatin the wanted int.
  Node *list1 = NULL;      //<-- declear a linked list that will conatian the 1st int int.
  Node *list2 = NULL;      //<-- declear a linked list that will conatian the 2nd int int.
  Node *resultList = NULL; //<-- to deaclar alist each node of it  will held the result of the 2 node

  //  this loop use for showing the menu:
  while (!exitFlag){

    printf("\nMenu:\n");
    printf("1. Read Input File\n");
    printf("2. Perform Addition\n");
    printf("3. Perform Subtraction\n");
    printf("4. Perform Multiplication\n");
    printf("5. Perform Division\n");
    printf("6. Print Results\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      // read the int numbers and print it;
      print_file_numbers();
      didRead = 1;
      break;
    case 2:

      if (didRead == 0){
        printf("please choice the first option1 first :) \n");
      }else{

        // to get the wanted opeartaion  numbers:
        printf("Please enter the first number\n");
        scanf("%d", &number1);               //<-- to get the line thta contain the 1st wanted int.
        //list1 = insert_line(number1, list1); //<-- to insert the 1st selected int to the list & reverse it.
        // display(list1);

        printf("\nNow, please enter the second number:\n");
        scanf("%d", &number2);               //<-- to get the line that contain the 2nd wanted int.
        list2 = insert_line(number2, list2); //<-- to insert the 2nd selected int to the list & reverse it.
        display(list2);

        // do the sum operation:
        resultList = Sum(list1, list2, resultList);
        printf("the result is :\n");
        display(resultList);

        // clear and delete the lists after saved result in the reuslt list:
        deleteList(&list1);
        deleteList(&list2);
        deleteList(&resultList);
      }
      break;
    case 3:
      if (didRead == 0) {
        printf("please choice 1 first :) \n");
      }else{
         // to get the wanted opeartaion  numbers:
        printf("Please enter the first number\n");
        scanf("%d", &number1);               //<-- to get the line thta contain the 1st wanted int.
        list1 = insert_line(number1, list1); //<-- to insert the 1st selected int to the list & reverse it.
        display(list1);

        printf("\nNow, please enter the second number:\n");
        scanf("%d", &number2);               //<-- to get the line that contain the 2nd wanted int.
        list2 = insert_line(number2, list2); //<-- to insert the 2nd selected int to the list & reverse it.
        display(list2);
        // do the sum operation:
        printf("the result is :\n");
        resultList = Sub_operations(list1, list2, resultList);
        display(resultList);

        // clear and delete the lists after saved result in the reuslt list:
        deleteList(&list1);
        deleteList(&list2);
        deleteList(&resultList);
      }
      break;
    case 4:

      if (didRead == 0) {
        printf("please choice 1 first :) \n");
      }else {

         // to get the wanted opeartaion  numbers:
        printf("Please enter the first number\n");
        scanf("%d", &number1);               //<-- to get the line thta contain the 1st wanted int.
        list1 = insert_line(number1, list1); //<-- to insert the 1st selected int to the list & reverse it.
        display(list1);

        printf("\nNow, please enter the second number:\n");
        scanf("%d", &number2);               //<-- to get the line that contain the 2nd wanted int.
        list2 = insert_line(number2, list2); //<-- to insert the 2nd selected int to the list & reverse it.
        display(list2);


      if (list1 == NULL || list2 == NULL) {
        printf("Error: One or both lists are null.\n");
      } else {
        printf("Calling the Multiplication function...\n");
        resultList = Multiplication(list1, list2);
        printf("Multiplication function was called. Here is the result:\n");
        printf("The result is:\n");
        display(resultList);
      }

        // clear and delete the lists after saved result in the reuslt list:
        deleteList(&list1);
        deleteList(&list2);
        deleteList(&resultList);

      }
      break;
    case 5:

      if (didRead == 0)
      {
        printf("please choice 1 first :) \n");
      }
      else
      {
        // will select the 2 numbers  and then do the Division operation.
      }
      break;

    case 6:
      // print the result in the file and terminal

      break;

    case 7:
      // exit
      exitFlag = 1;
      printf("Exiting the program...\n");
      break;
    default:
      printf("Invalid choice. Please try again.\n");
      break;
    }
    printf("\n");
  }

  return 0;
}
