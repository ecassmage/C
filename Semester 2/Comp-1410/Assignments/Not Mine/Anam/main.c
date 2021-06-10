#include <stdio.h>
#include <stdlib.h>
typedef struct LinkedListNode{
 int value;
 struct LinkedListNode * next;
}Node;
typedef struct LinkedListHeader{
 int size;
 int version;
}FileHeader;

void CreateList(Node **head){
 *head = NULL;
}

void InsertNodeAtHead(Node **head, int v){
 Node *newNode = (Node*) malloc(sizeof(Node));
 newNode->value = v;
 newNode->next = NULL;
 if(head == NULL){ // remove pointer
    *head = newNode;
 }
 else{
     newNode->next = *head;
     *head = newNode;
 }
}

void InsertNodeAtEnd(Node **head, int v) {
 Node * newNode = (Node*)malloc(sizeof(Node));
 newNode->value = v;
 newNode->next = NULL;
 if(*head == NULL){ // remove pointer
    *head = newNode;
    return;
 }
 Node *current;
 current = *head;
 while(current->next!=NULL){
 current = current->next;
 }
 current->next = newNode;
}

void DeleteNodeAtHead(Node**head){
     if(*head ==NULL){
        return;
     }
     Node *temp;
     temp = *head;
    *head = (*head)->next; // moved this above free(temp);
     free(temp);

}

int ListSize(Node *head){ //Nothing
    int size =0;
    while(head != NULL){
        size+=1;
        head = head->next;
    }
    return size;
}

void DeleteNodeAtEnd(Node**head){
     if(*head ==NULL){
        return;
     }
     Node *current, *temp;
     current = *head;
     while(current-> next -> next != NULL){
        current = current->next;
     }
     temp = current->next;
     current->next = NULL;
     free(temp);
     //current->next = NULL;
}

void PrintList(Node *head){ // Fine
 Node *current;
 current = head;
 while (current != NULL){
 printf("%d --> ", current->value);
 current = current->next;
 }
 printf("NULL\n");
}

Node * SearchList(Node *head, int v){ // Fine
     Node *current;
     current = head;
     while (current != NULL){
         if(current->value == v)
            return current;
         current = current->next;
     }
     return NULL;
}

void ClearList(Node **head){ // Fine
     Node *temp;
     while(NULL != *head){
        temp = *head;
        *head = (*head) -> next;
        free(temp);
     }
}

void PrintListRec(Node *head) {
     if (head == NULL) {
         printf("NULL\n");
         return;
     }
     printf("%d --> ",head->value);
     PrintListRec(head->next);
}

void SortList(Node *head){
    int temp;
    for(Node * curr = head; curr!=NULL; curr=curr->next){ // bug remove -> next
        for(Node * after = curr->next; after!=NULL; after=after->next){
            if(curr->value > after->value){
                temp = curr->value;
                curr->value = after->value;
                after->value = temp;
            }
        }
    }
}

void WriteToFile(FileHeader header, Node *head){
     FILE *myFile = fopen("listdata.bin", "wb");
     header.size = ListSize(head);
     header.version = 1;
     fwrite(&header, sizeof(header), 1, myFile);
     Node * node = head;
     while(node!=NULL){
         //head->next = NULL;
         fwrite(&(node -> value), sizeof(Node), 1, myFile);
         node = node -> next;
     }
     fclose(myFile);
}
void LoadFromFile(FileHeader header, Node **head){
     FILE *myFile = fopen("listdata.bin", "rb");
     fread(&header, sizeof(header), 1, myFile);
     int size = header.size;
     Node temp;
     for(int i=0; i<size; i++){
         fread(&temp, sizeof(Node),1,myFile);
         InsertNodeAtHead(head,temp.value);
     }
     fclose(myFile);
}

int main() {
    printf("Linked List version: 1.0\n");
    Node *head = NULL;
    InsertNodeAtHead(&head, 1);
    InsertNodeAtHead(&head, 3);
    InsertNodeAtHead(&head, 2);
    InsertNodeAtHead(&head, 7);
    InsertNodeAtHead(&head, 4);
    InsertNodeAtHead(&head, 6);
    InsertNodeAtHead(&head, 5);
    InsertNodeAtEnd(&head, 10);
    //DeleteNodeAtHead(&head);
    printf("%d\n", ListSize(head));
    //DeleteNodeAtEnd(&head);
    PrintList(head);
    Node *HEllo = SearchList(head, 6);
    //ClearList(&head);
    SortList(head);
    PrintList(head);
    FileHeader HELLO;
    //WriteToFile(HELLO, head);
 return 0;
}