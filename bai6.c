#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int id;
    char name[64];
    float gpa;
} Student;


typedef struct Node {
    Student data;
    struct Node *prev, *next;
} Node;

typedef struct {
    Node *head, *tail;
    size_t size;
} DList;

void dll_init(DList *L) {
    L->head = L->tail = NULL;
    L->size = 0;
}

Node* dll_create_node(Student s) {
    Node *p = (Node*)malloc(sizeof(Node));
    p->data = s;
    p->prev = p->next = NULL;
    return p;
}

void dll_insert_student(DList *L, Student s) {
    Node *p = L->head;
    while (p) {
        if (p->data.id == s.id) return; // id trùng
        if (p->data.id > s.id) break;
        p = p->next;
    }

    Node *new_node = dll_create_node(s);
    if (p == NULL) {
        if (L->tail == NULL) L->head = L->tail = new_node;
        else {
            L->tail->next = new_node;
            new_node->prev = L->tail;
            L->tail = new_node;
        }
    } else if (p->prev == NULL) {
        new_node->next = p;
        p->prev = new_node;
        L->head = new_node;
    } else {
        new_node->prev = p->prev;
        new_node->next = p;
        p->prev->next = new_node;
        p->prev = new_node;
    }
    L->size++;
}

int dll_remove_by_id(DList *L, int id) {
    Node *p = L->head;
    while (p) {
        if (p->data.id == id) {
            if (p->prev) p->prev->next = p->next; // nếu có prev thì prev->next trỏ tới next
            else L->head = p->next; // nếu không có prev thì p là head, cập nhật head
            if (p->next) p->next->prev = p->prev;  // nếu có next thì next->prev trỏ tới prev
            else L->tail = p->prev;  // nếu không có next thì p là tail, cập nhật tail
            free(p);
            L->size--;
            return 1;
        }
        p = p->next;
    }
    return 0;
}

int dll_update_student(DList *L, int id, const char *new_name, float new_gpa) {
    Node *p = L->head;
    while (p) {
        if (p->data.id == id) {
            if (new_name) strcpy(p->data.name, new_name);
            if (new_gpa >= 0) p->data.gpa = new_gpa;
            return 1;
        }
        p = p->next;
    }
    return 0;
}

Student* dll_find_by_id(DList *L, int id) {
    Node *p = L->head;
    while (p) {
        if (p->data.id == id) return &p->data;
        p = p->next;
    }
    return NULL;
}

void dll_find_by_gpa_range(DList *L, float min_gpa, float max_gpa) {
    Node *p = L->head;
    while (p) {
        if (p->data.gpa >= min_gpa && p->data.gpa <= max_gpa) {
            printf("ID: %d | Name: %s | GPA: %.2f\n", p->data.id, p->data.name, p->data.gpa);
        }
        p = p->next;
    }
}

void dll_list_honor_students(DList *L) {
    dll_find_by_gpa_range(L, 3.2, 4.0);
}
void dll_report(DList *L) {
    int count = 0;
    float sum = 0;
    Student *max = NULL, *min = NULL;

    Node *p = L->head;
    while (p) {
        count++;
        sum += p->data.gpa;
        if (!max || p->data.gpa > max->gpa) max = &p->data; 
        if (!min || p->data.gpa < min->gpa) min = &p->data;
        p = p->next;
    }

    printf("Tổng số SV: %d\n", count);
    printf("GPA trung bình: %.2f\n", count ? sum / count : 0);
    if (max) printf("SV cao nhất: %s (ID %d) - GPA: %.2f\n", max->name, max->id, max->gpa);
    if (min) printf("SV thấp nhất: %s (ID %d) - GPA: %.2f\n", min->name, min->id, min->gpa);
}

int main() {
    DList L;
    dll_init(&L);

    // Thêm sinh viên
    Student s1 = {101, "Nguyen Van A", 3.5};
    Student s2 = {102, "Tran Thi B", 2.8};
    Student s3 = {103, "Le Van C", 3.9};
    dll_insert_student(&L, s1);
    dll_insert_student(&L, s2);
    dll_insert_student(&L, s3);

    // Cập nhật sinh viên
    dll_update_student(&L, 102, "Tran Thi B Updated", 3.1);

    // Xóa sinh viên
    dll_remove_by_id(&L, 101);

    // Tìm kiếm sinh viên theo ID
    Student *found = dll_find_by_id(&L, 103);
    if (found) {
        printf("Tìm thấy SV: %s (ID %d) - GPA: %.2f\n", found->name, found->id, found->gpa);
    } else {
        printf("Không tìm thấy SV với ID 103\n");
    }

    // Liệt kê sinh viên có GPA từ 3.2 đến 4.0
    printf("Danh sách SV có GPA từ 3.2 đến 4.0:\n");
    dll_list_honor_students(&L);

    // Báo cáo thống kê
    printf("Báo cáo thống kê:\n");
    dll_report(&L);

    return 0;
}