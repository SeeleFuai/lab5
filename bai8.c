#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
    Node *p = A->head;
    while (p) {
        poly_add_term(&C, p->data);
        p = p->next;
    }
    Node *q = B->head;
    while (q) {
        poly_add_term(&C, q->data);
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

void poly_print(Poly *P) {
    Node *p = P->head;
    if (!p) {
        printf("0\n");
        return;
    }
    while (p) {
        if (p != P->head && p->data.coef >= 0)
            printf(" + ");
        else if (p->data.coef < 0)
            printf(" - ");
        
        double abs_coef = p->data.coef < 0 ? -p->data.coef : p->data.coef;

        if (p->data.exp == 0)
            printf("%.2f", abs_coef);
        else if (p->data.exp == 1)
            printf("%.2fx", abs_coef);
        else
            printf("%.2fx^%d", abs_coef, p->data.exp);
        
        p = p->next;
    }
    printf("\n");
}
double poly_eval(Poly *P, double x) {
    double result = 0;
    Node *p = P->head;
    while (p) {
        result += p->data.coef * pow(x, p->data.exp);
        p = p->next;
    }
    return result;
}


void test_poly() {
    Poly A, B;
    poly_init(&A);
    poly_init(&B);

    // Tạo đa thức A: 3x^4 + 2x^2 + 1
    poly_add_term(&A, (Term){4, 3});
    poly_add_term(&A, (Term){2, 2});
    poly_add_term(&A, (Term){0, 1});

    // Tạo đa thức B: 5x^3 + 4x + 2
    poly_add_term(&B, (Term){3, 5});
    poly_add_term(&B, (Term){1, 4});
    poly_add_term(&B, (Term){0, 2});

    printf("Đa thức A: ");
    poly_print(&A);
    printf("Đa thức B: ");
    poly_print(&B);

    Poly C = poly_add(&A, &B);
    printf("A + B = ");
    poly_print(&C);

    Poly D = poly_multiply(&A, &B);
    printf("A * B = ");
    poly_print(&D);

    Poly E = poly_minus(&A, &B);
    printf("A - B = ");
    poly_print(&E);

    double x = 2.0;
    printf("Giá trị của A tại x = %.2f: %.2f\n", x, poly_eval(&A, x));
    printf("Giá trị của B tại x = %.2f: %.2f\n", x, poly_eval(&B, x));
}

int main() {
    test_poly();
    return 0;
}