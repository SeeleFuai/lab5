#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int exp;       // số mũ
    double coef;   // hệ số
} Term;

typedef struct Node {
    Term data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} Poly;


void poly_init(Poly *P) {
    P->head = NULL;
}
Node* create_node(Term t) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = t;
    newNode->next = NULL;
    return newNode;
}
void poly_add_term(Poly *P, Term t) {
    if (t.coef == 0) return; // bỏ qua hệ số 0

    Node *p = P->head;
    Node *prev = NULL;
    while (p && p->data.exp > t.exp) { // tìm vị trí chèn
        prev = p; // lưu nút trước
        p = p->next; 
    }

    if (p && p->data.exp == t.exp) { // nếu cùng số mũ thì cộng hệ số
        p->data.coef += t.coef;      
        if (p->data.coef == 0) { // nếu hệ số trở thành 0 thì xóa
            if (prev) prev->next = p->next; // xóa giữa hoặc cuối
            else P->head = p->next; // xóa đầu
            free(p);
        }
    } else { // chèn nút mới
        Node *new_node = create_node(t);
        if (prev == NULL) { // chèn vào đầu
            new_node->next = P->head;
            P->head = new_node;
        } else { // chèn giữa hoặc cuối
            new_node->next = p;
            prev->next = new_node;
        }
    }
}

Poly poly_add(Poly *A, Poly *B) {
    Poly C;
    poly_init(&C);
    Node *p = A->head, *q = B->head;
    while (p) {
        poly_insert_term(&C, p->data);
        p = p->next;
    }
    while (q) {
        Term t = q->data;
        poly_insert_term(&C, t);
        q = q->next;
    }
    return C;
}

Poly poly_multiply(Poly *A, Poly *B) {
    Poly C;
    poly_init(&C);
    Node *p = A->head;
    while (p) {
        Node *q = B->head;
        while (q) {
            Term t;
            t.exp = p->data.exp + q->data.exp;
            t.coef = p->data.coef * q->data.coef;
            poly_add_term(&C, t);
            q = q->next;
        }
        p = p->next;
    }
    return C;
}

Poly poly_minus(Poly *A, Poly *B) {
    Poly C;
    poly_init(&C);
    Node *p = A->head;
    while (p) {
        poly_add_term(&C, p->data);
        p = p->next;
    }
    Node *q = B->head;
    while (q) {
        Term t = q->data;
        t.coef = -t.coef; // đổi dấu hệ số
        poly_add_term(&C, t);
        q = q->next;
    }
    return C;
}

void test_poly() {
    Poly A, B;
    poly_init(&A);
    poly_init(&B);

    poly_insert_term(&A, (Term){4, 3});
    poly_insert_term(&A, (Term){2, 2});
    poly_insert_term(&A, (Term){0, -5});

    poly_insert_term(&B, (Term){3, -1});
    poly_insert_term(&B, (Term){2, 2});
    poly_insert_term(&B, (Term){0, 1});

    printf("A(x) = "); poly_print(&A);
    printf("B(x) = "); poly_print(&B);

    Poly C1 = poly_add(&A, &B);
    printf("A + B = "); poly_print(&C1);

    Poly C2 = poly_sub(&A, &B);
    printf("A - B = "); poly_print(&C2);

    Poly C3 = poly_mul(&A, &B);
    printf("A * B = "); poly_print(&C3);

    double val = poly_eval(&A, 2);
    printf("A(2) = %.2f\n", val);
}

int main() {
    test_poly();
    return 0;
}