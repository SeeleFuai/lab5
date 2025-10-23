
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char id[16];
    char name[64];
    char khoa[64];
} Student;

typedef struct Node {
    Student data;
    struct Node* next;
} Node;

Node* createNode(Student s) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = s;
    newNode->next = NULL;
    return newNode;
}

void printList(Node* head) {
    printf("Danh sách sinh viên:\n");
    if (head == NULL) {
        printf("(Danh sách rỗng)\n");
        return;
    }
    while (head != NULL) {
        printf("MSSV: %s | Tên: %s | Khoa: %s\n", head->data.id, head->data.name, head->data.khoa);
        head = head->next;
    }
    printf("\n");
}

void append(Node** head, Student s) {
    printf("Thêm sinh viên: %s - %s - %s\n", s.id, s.name, s.khoa);
    Node* newNode = createNode(s);
    if (*head == NULL) {
        *head = newNode;
    } 
    else {
        Node* temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
            printList(temp);
        temp->next = newNode;
    }
    printList(*head);
}

void findStudent(Node* head, const char* id) {
    printf("Tìm sinh viên có mã: %s\n", id);
    while (head != NULL) {
        printList(head);
        if (strcmp(head->data.id, id) == 0) {
            printf("Tìm thấy: %s - %s - %s\n", head->data.id, head->data.name, head->data.khoa);
            printList(head);
            return;
        }
        head = head->next;
    }
    printf("Không tìm thấy sinh viên có mã %s\n", id);
    printList(head);
}
void deleteHead(Node** head) {
    if (*head == NULL) {
        printf("Danh sách rỗng. Không thể xóa đầu.\n");
        return;
    }
    printf("Xóa sinh viên đầu: %s\n", (*head)->data.id);
    Node* temp = *head;
    *head = (*head)->next;
    free(temp);
    printList(*head);
}
void deleteTail(Node** head) {
    if (*head == NULL) {
        printf("Danh sách rỗng. Không thể xóa cuối.\n");
        return;
    }
    if ((*head)->next == NULL) {
        printf("Xóa sinh viên duy nhất: %s\n", (*head)->data.id);
        free(*head);
        *head = NULL;
        printList(*head);
        return;
    }
    Node* temp = *head;
    while (temp->next->next != NULL)
        temp = temp->next;
    printf("Xóa sinh viên cuối: %s\n", temp->next->data.id);
    free(temp->next);
    temp->next = NULL;
    printList(*head);
}
void deleteById(Node** head, const char* id) {
    if (*head == NULL) {
        printf("Danh sách rỗng. Không thể xóa.\n");
        return;
    }
    if (strcmp((*head)->data.id, id) == 0) {
        printf("Xóa sinh viên đầu có mã %s\n", id);
        deleteHead(head);
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL && strcmp(temp->next->data.id, id) != 0) 
        temp = temp->next;
    if (temp->next != NULL) {
        printf("Xóa sinh viên có mã %s\n", id);
        Node* toDelete = temp->next;
        temp->next = toDelete->next;
        free(toDelete);
    } else {
        printf("Không tìm thấy sinh viên có mã %s để xóa.\n", id);
    }
    printList(*head);
}
int main() {
    Node* head = NULL;
    int n;
    Student s;
    char idToFind[16], idToDelete[16];

    printf("Nhập số lượng sinh viên: ");
    scanf("%d", &n);
    getchar(); // loại bỏ ký tự newline

    for (int i = 0; i < n; i++) {
        printf("Nhập thông tin sinh viên thứ %d:\n", i + 1);
        printf("Mã sinh viên: "); fgets(s.id, sizeof(s.id), stdin); s.id[strcspn(s.id, "\n")] = 0;
        printf("Tên: "); fgets(s.name, sizeof(s.name), stdin); s.name[strcspn(s.name, "\n")] = 0;
        printf("Khoa: "); fgets(s.khoa, sizeof(s.khoa), stdin); s.khoa[strcspn(s.khoa, "\n")] = 0;
        append(&head, s);
    }

    printf("Nhập mã sinh viên cần tìm: ");
    fgets(idToFind, sizeof(idToFind), stdin); idToFind[strcspn(idToFind, "\n")] = 0;
    findStudent(head, idToFind);

    printf("Thực hiện xóa phần tử đầu:\n");
    deleteHead(&head);

    printf("Thực hiện xóa phần tử cuối:\n");
    deleteTail(&head);

    printf("Nhập mã sinh viên cần xóa: ");
    fgets(idToDelete, sizeof(idToDelete), stdin); idToDelete[strcspn(idToDelete, "\n")] = 0;
    deleteById(&head, idToDelete);

    return 0;
}

