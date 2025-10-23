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

void dll_insert_sorted(DList *L, int key) {
    Node *p = L->head;
    while (p) {
        if (p->key == key) return; // bỏ qua nếu trùng
        if (p->key > key) break; 
        p = p->next;
    }
    
    Node *new_node = dll_create_node_int(key);
    if (p==NULL) { // chèn vào cuối
        if (L->tail==NULL) {
            L->head = L->tail = new_node;
        }
        else { // chèn sau tail
            L->tail->next = new_node;
            new_node->prev = L->tail;
            L->tail = new_node;
        }
    } 
    else if (p->prev==NULL) { // chèn vào đầu
        new_node->next = p; 
        p->prev = new_node;
        L->head = new_node;
    } 
    else { // chèn giữa
        new_node->prev = p->prev; // cập nhật prev của nút mới
        new_node->next = p; // cập nhật next của nút mới
        p->prev->next = new_node; // cập nhật next của nút trước
        p->prev = new_node; // cập nhật prev của p
    }
    L->size++;
}


void dll_print_forward(DList *L) {
    Node *p = L->head;
    while (p) {
        printf("%d ", p->key);
        p = p->next;
    }
    printf("\n");
}

int main() {
    DList L;
    dll_init(&L);
    int a[] = {5, 1, 3, 3, 2, 9, 7};
    int n = sizeof(a) / sizeof(a[0]);

    for (int i = 0; i < n; i++) {
        dll_insert_sorted(&L, a[i]); 
    }

    printf("DLL:\n"); 
    dll_print_forward(&L); //
}
