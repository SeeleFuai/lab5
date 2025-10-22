#include <stdio.h> 
#include <stdlib.h>

typedef struct Node {
    int key;
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

Node* dll_create_node_int(int key) {
    Node *p = (Node*)malloc(sizeof(Node));
    p->key = key;
    p->prev = p->next = NULL;
    return p;
}

void dll_push_back(DList *L, Node *p) {
    if (!L->tail) {
        L->head = L->tail = p;
    } 
    else {
        L->tail->next = p;
        p->prev = L->tail;
        L->tail = p;
    }
    L->size++;
}

void dll_remove(DList *L, Node *p) {
    if (!p) return; 
    if (p->prev) p->prev->next = p->next; // nếu có prev thì prev->next trỏ tới next
    else L->head = p->next; // nếu không có prev thì p là head, cập nhật head
    if (p->next) p->next->prev = p->prev; // nếu có next thì next->prev trỏ tới prev
    else L->tail = p->prev; // nếu không có next thì p là tail, cập nhật tail
    free(p);
    L->size--;
}

int array_from_dll(DList *L, int out[], int max_out) {
    int i = 0;
    Node *p = L->head;
    while (p && i < max_out) {
        out[i] = p->key;
        p = p->next;
        i++;
    }
    return i; // số lượng phần tử đã ghi vào mảng
}


DList dll_from_array(int a[], int n) {
    DList L;
    dll_init(&L);
    for (int i = 0; i < n; i++) {
        Node *p = dll_create_node_int(a[i]);
        dll_push_back(&L, p);
    }
    return L;

}
int main() {
    // int a[10];
    // srand(time(NULL));
    // for (int i = 0; i < 10; i++) {
    //     a[i] = rand() % 100;
    // }

    // printf("Mảng ban đầu:\n");
    // for (int i = 0; i < 10; i++) {
    //     printf("%d ", a[i]);
    // }
    // printf("\n");

    // DList L = dll_from_array(a, 10);

    // // Xóa các phần tử chẵn
    // Node *p = L.head;
    // while (p) {
    //     Node *next = p->next;
    //     if (p->key % 2 == 0) {
    //         dll_remove(&L, p); 
    //     }
    //     p = next;
    // }

    // // Xuất lại mảng
    // int out[10];
    // int count = array_from_dll(&L, out, 10);
    // printf("Mảng sau khi xóa phần tử chẵn:\n");
    // for (int i = 0; i < count; i++) {
    //     printf("%d ", out[i]);
    // }
    // printf("\n");

    int n;
    printf("Nhập n:"); scanf("%d",&n);
    int a[n];
    for (int i = 0; i < n; i++) {
        printf("Nhập giá trị %d:",i);
        scanf("%d",&a[i]);

    }

    printf("Mảng ban đầu:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    DList L = dll_from_array(a,n);

    Node *p = L.head;
    while (p!=NULL)
    {
        Node *next = p->next;
        if (p->key % 2 == 0) {
            dll_remove(&L, p); 
        }
        p = next;
    }
    
    int out[n];
    int count = array_from_dll(&L,out,n);
    printf("Mảng sau khi xóa phần tử chẵn:\n");
    for (int i = 0; i < count; i++) {
        printf("%d ", out[i]);
    }
    printf("\n");

}

