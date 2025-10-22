#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char sku[20];
    char name[64];
    int qty;
    double price;
} Item;

typedef struct Node {
    Item data;
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

Node* dll_create_node(Item item) {
    Node *p = (Node*)malloc(sizeof(Node));
    p->data = item;
    p->prev = p->next = NULL;
    return p;
}
void dll_add_item(DList *L, Item item) {
    Node *p = L->head;
    while (p) {
        if (strcmp(p->data.sku, item.sku) == 0) return; // trùng SKU
        p = p->next;
    }

    Node *new_node = dll_create_node(item);
    if (!L->tail) {
        L->head = L->tail = new_node;
    } else {
        L->tail->next = new_node;
        new_node->prev = L->tail;
        L->tail = new_node;
    }
    L->size++;
}
int dll_import_stock(DList *L, const char *sku, int amount) {
    Node *p = L->head;
    while (p) {
        if (strcmp(p->data.sku, sku) == 0) {
            p->data.qty += amount;
            return 1;
        }
        p = p->next;
    }
    return 0;
}
int dll_export_stock(DList *L, const char *sku, int amount) {
    Node *p = L->head;
    while (p) {
        if (strcmp(p->data.sku, sku) == 0) {
            if (p->data.qty >= amount) {
                p->data.qty -= amount;
                return 1;
            } else {
                return -1; // không đủ hàng
            }
        }
        p = p->next;
    }
    return 0; // không tìm thấy SKU
}

int dll_update_price(DList *L, const char *sku, double new_price) {
    Node *p = L->head;
    while (p) {
        if (strcmp(p->data.sku, sku) == 0) {
            p->data.price = new_price;
            return 1;
        }
        p = p->next;
    }
    return 0;
}

Item* dll_find_by_sku(DList *L, const char *sku) {
    Node *p = L->head;
    while (p) {
        if (strcmp(p->data.sku, sku) == 0) return &p->data;
        p = p->next;
    }
    return NULL;
}

void dll_search_by_name(DList *L, const char *keyword) {
    Node *p = L->head;
    while (p) {
        if (strstr(p->data.name, keyword)) {
            printf("SKU: %s | Name: %s | Qty: %d | Price: %.2f\n",
                   p->data.sku, p->data.name, p->data.qty, p->data.price);
        }
        p = p->next;
    }
}

void dll_low_stock_alert(DList *L, int reorder_level) {
    Node *p = L->head;
    while (p) {
        if (p->data.qty <= reorder_level) {
            printf(" SKU: %s | Name: %s | Qty: %d\n",
                   p->data.sku, p->data.name, p->data.qty);
        }
        p = p->next;
    }
}

double dll_total_inventory_value(DList *L) {
    double total = 0;
    Node *p = L->head;
    while (p) {
        total += p->data.qty * p->data.price;
        p = p->next;
    }
    return total;
}

void dll_merge_inventory(DList *A, DList *B) {
    Node *p = B->head;
    while (p) {
        Item *existing = dll_find_by_sku(A, p->data.sku);
        if (existing) {
            existing->qty += p->data.qty;
            if (p->data.price > 0) existing->price = p->data.price;
        } else {
            dll_add_item(A, p->data);
        }
        p = p->next;
    }
}
void dll_print_inventory(DList *L) {
    Node *p = L->head;
    printf("Current Inventory:\n");
    printf("--------------------------------------------------\n");
    printf("| %-10s | %-20s | %-5s | %-10s |\n", "SKU", "Name", "Qty", "Price");
    printf("--------------------------------------------------\n");
    while (p) {
        printf("| %-10s | %-20s | %-5d | %-10.2f |\n",
               p->data.sku, p->data.name, p->data.qty, p->data.price);
        p = p->next;
    }
    printf("--------------------------------------------------\n");
}