#include <stdio.h>
#include <stdlib.h>

typedef struct Dnode {
    int data;
    struct Dnode* next;
    struct Dnode* prev;
} Dnode;

typedef struct Dlist {
    Dnode* head;
    Dnode* tail;
} Dlist;

Dnode* createDnode(int data) {
    Dnode* newNode = (Dnode*)malloc(sizeof(Dnode));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

Dlist* createDlist() {
    Dlist* newList = (Dlist*)malloc(sizeof(Dlist));
    newList->head = NULL;
    newList->tail = NULL;
    return newList;
}

void printDlist(Dlist* list) {
    printf("Danh sách hiện tại: ");
    if (list->head == NULL) {
        printf("(rỗng)\n");
        return;
    }
    Dnode* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void printReverse(Dlist* list) {
    printf("Danh sách ngược: ");
    if (list->tail == NULL) {
        printf("(rỗng)\n");
        return;
    }
    Dnode* current = list->tail;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->prev;
    }
    printf("\n");
}

void AddToTail(Dlist* list, int data) {
    printf("Thêm phần tử %d vào cuối danh sách.\n", data);
    Dnode* newNode = createDnode(data);
    if (list->tail == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } 
    else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    printDlist(list);
}

void DeleteFromHead(Dlist* list) {
    if (list->head == NULL) {
        printf("Danh sách rỗng. Không thể xóa đầu.\n");
        return;
    }
    printf("Xóa phần tử đầu: %d\n", list->head->data);
    Dnode* temp = list->head;
    list->head = list->head->next; //
    if (list->head != NULL) { 
        list->head->prev = NULL;
    } else {
        list->tail = NULL; // Danh sách trở nên rỗng
    }
    free(temp);
    printDlist(list);
}

void DeleteFromTail(Dlist* list) {
    if (list->tail == NULL) {
        printf("Danh sách rỗng. Không thể xóa cuối.\n");
        return;
    }
    printf("Xóa phần tử cuối: %d\n", list->tail->data);
    Dnode* temp = list->tail;
    list->tail = list->tail->prev;
    if (list->tail != NULL) {
        list->tail->next = NULL;
    } else {
        list->head = NULL; // Danh sách trở nên rỗng
    }
    free(temp);
    printDlist(list);
}

int main() {
    Dlist* list = createDlist();
    int n, value;

    printf("Nhập số lượng phần tử cần thêm: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Nhập giá trị phần tử thứ %d: ", i + 1);
        scanf("%d", &value);
        AddToTail(list, value);
    }



    printDlist(list);
    printReverse(list);

    DeleteFromHead(list);
    DeleteFromTail(list);

    printDlist(list);
    printReverse(list);
    

    return 0;
}