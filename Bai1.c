#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void printList(Node* head) {
    printf("Danh sách hiện tại: ");
    if (head == NULL) {
        printf("(rỗng)\n");
        return;
    }
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}
void append(Node** head, int data) {
    printf("Thêm phần tử %d vào danh sách.\n", data);
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } 
    else {
        Node* temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
    printList(*head);
}
void findValue(Node* head, int x) {
    printf("Tìm phần tử có giá trị %d.\n", x);
    int pos = 0;
    while (head != NULL) {
        printList(head);
        if (head->data == x) {
            printf("Tìm thấy %d tại vị trí %d.\n", x, pos);
            printList(head);
            return;
        }
        head = head->next;
        pos++;
    }
    printf("Không tìm thấy %d trong danh sách.\n", x);
    printList(head);
}
void deleteHead(Node** head) {
    if (*head == NULL) {
        printf("Danh sách rỗng.\n");
        return;
    }
    printf("Xóa phần tử đầu tiên có giá trị %d.\n", (*head)->data);
    Node* temp = *head;
    *head = (*head)->next;
    free(temp);
    printList(*head);
}
void deleteTail(Node** head) {
    if (*head == NULL) {
        printf("Danh sách rỗng.\n");
        return;
    }
    if ((*head)->next == NULL) {
        printf("Xóa phần tử duy nhất có giá trị %d.\n", (*head)->data);
        free(*head);
        *head = NULL;
        printList(*head);
        return;
    }

    Node* temp = *head;
    while (temp->next->next != NULL){
        printList(temp);
        temp = temp->next;
    }
    printf("Xóa phần tử cuối có giá trị %d.\n", temp->next->data);
    free(temp->next);
    temp->next = NULL;
    printList(*head);
}

void deleteValue(Node** head, int x) {
    int count = 0;
    Node* temp = *head;
    if (*head == NULL) {
        printf("Danh sách rỗng. Không thể xóa phần tử có giá trị %d.\n", x);
        return;
    }

    if ((*head)->data == x) {
        printf("Xóa phần tử đầu có giá trị %d.\n", x);
        deleteHead(head);
        count++;
    }
    while (temp != NULL && temp->next != NULL)
    {
        printList(temp);
        if (temp->next->data == x)
        {
            printf("Xóa phần tử có giá trị %d.\n", x);
            Node* toDelete = temp->next;
            temp->next = toDelete->next;
            free(toDelete);
            count++;
        } 
        else {
            temp = temp->next;
        }
    }
    if (count == 0) {
        printf("Không tìm thấy phần tử có giá trị %d để xóa.\n", x);
    }
    else {
        printf("Đã xóa tất cả phần tử có giá trị %d.\n", x);
    }
    printList(*head);
}
int main() {
    Node* head = NULL;
    int n, x;

    printf("Nhập số lượng phần tử: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int value;
        printf("Nhập phần tử thứ %d: ", i + 1);
        scanf("%d", &value);
        append(&head, value);
    }

    printf("\nNhập giá trị cần tìm: ");
    scanf("%d", &x);
    findValue(head, x);

    printf("\nXóa phần tử đầu:\n");
    deleteHead(&head);

    printf("\nXóa phần tử cuối:\n");
    deleteTail(&head);

    printf("\nNhập giá trị cần xóa: ");
    scanf("%d", &x);
    deleteValue(&head, x);

    return 0;
}
