#include <stdio.h>
#include <stdlib.h>

typedef struct Dnode {
    int data;
    struct Dnode* prev;
    struct Dnode* next;
} Dnode;

typedef struct  Dlist {
    Dnode* head;
    Dnode* tail;
} Dlist;



Dlist* createList() {
    Dlist* newList = (Dlist*)malloc(sizeof(Dlist));
    if (!newList) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newList->head = NULL;
    newList->tail = NULL;
    return newList;
}

Dnode* createNode(int data) {
    Dnode* newNode = (Dnode*)malloc(sizeof(Dnode));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void append(Dlist* list, int data) {
    Dnode* newNode = createNode(data);
    if (list->tail == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
    free(newNode);
}

void displayList(Dlist* list) {
    Dnode* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}


int main() {
    Dlist* Dlist = createList();
    
    append(Dlist, 10);
    append(Dlist, 20);
    append(Dlist, 30);
    
    printf("Doubly Linked List: ");
    displayList(Dlist);
    free(Dlist);
    return 0;
}

