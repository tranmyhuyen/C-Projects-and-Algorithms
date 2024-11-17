#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Struct cho một nút cây biểu thức
typedef struct Node {
    char value;
    struct Node *left, *right;
} Node;

// Struct cho bảng hăm đơn giản
typedef struct {
    char var;
    int value;
} Variable;

Variable vars[MAX];
int var_count = 0;

// Struct cho ngăn xếp
typedef struct {
    Node* data[MAX];
    int top;
} Stack;

// Khởi tạo ngăn xếp
void init_stack(Stack *s) {
    s->top = -1;
}

// Kiểm tra ngăn xếp rỗng
int is_empty(Stack *s) {
    return s->top == -1;
}

// Thêm phần tử vào ngăn xếp
void push(Stack *s, Node* value) {
    s->data[++s->top] = value;
}

// Lấy phần tử từ ngăn xếp
Node* pop(Stack *s) {
    if (!is_empty(s))
        return s->data[s->top--];
    return NULL;
}

// Tạo nút mới
Node* create_node(char value) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->left = node->right = NULL;
    return node;
}

// Kiểm tra toán tử
int is_operator(char c) {
    return c == '+' || c == '-' || c == '*';
}

// Độ ưu tiên của toán tử
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*') return 2;
    return 0;
}

// Chuyển đổi biểu thức trung tố sang hậu tố
void infix_to_postfix(char* infix, char* postfix) {
    Stack s;
    init_stack(&s);
    int k = 0;
    for (int i = 0; infix[i]; ++i) {
        char token = infix[i];

        if (isalnum(token)) {
            postfix[k++] = token;
        } else if (token == '(') {
            push(&s, create_node(token));
        } else if (token == ')') {
            while (!is_empty(&s) && s.data[s.top]->value != '(') {
                postfix[k++] = pop(&s)->value;
            }
            pop(&s); // Loại bỏ '('
        } else if (is_operator(token)) {
            while (!is_empty(&s) && precedence(s.data[s.top]->value) >= precedence(token)) {
                postfix[k++] = pop(&s)->value;
            }
            push(&s, create_node(token));
        }
    }
    while (!is_empty(&s)) {
        postfix[k++] = pop(&s)->value;
    }
    postfix[k] = '\0';
}

// Xây dựng cây từ biểu thức hậu tố
Node* build_expression_tree(char *postfix) {
    Stack s;
    init_stack(&s);

    for (int i = 0; postfix[i]; ++i) {
        char token = postfix[i];
        Node *node = create_node(token);

        if (is_operator(token)) {
            node->right = pop(&s);
            node->left = pop(&s);
        }
        push(&s, node);
    }

    return pop(&s);
}

// Lấy giá trị biến từ bảng băm
int get_variable_value(char var) {
    for (int i = 0; i < var_count; ++i) {
        if (vars[i].var == var)
            return vars[i].value;
    }
    return 0; // Nếu biến chưa được định nghĩa, trả về 0
}

// Đặt giá trị cho biến
void set_variable_value(char var, int value) {
    for (int i = 0; i < var_count; ++i) {
        if (vars[i].var == var) {
            vars[i].value = value;
            return;
        }
    }
    vars[var_count].var = var;
    vars[var_count].value = value;
    var_count++;
}

// Đánh giá cây biểu thức
int evaluate_tree(Node *root) {
    if (!root)
        return 0;

    // Nếu nút là số hoặc biến
    if (!root->left && !root->right) {
        if (isdigit(root->value))
            return root->value - '0';
        else
            return get_variable_value(root->value);
    }

    // Đánh giá giá trị của con trái và con phải
    int left_val = evaluate_tree(root->left);
    int right_val = evaluate_tree(root->right);

    // Thực hiện phép tính
    if (root->value == '+') return left_val + right_val;
    if (root->value == '-') return left_val - right_val;
    if (root->value == '*') return left_val * right_val;

    return 0;
}

int main() {
    char s[MAX];
    char cmd[10];

    // Đọc biểu thức
    scanf("%s", s);

    // Chuyển đổi sang biểu thức hậu tố
    char postfix[MAX];
    infix_to_postfix(s, postfix);

    // Xây dựng cây biểu thức
    Node* root = build_expression_tree(postfix);

    while (1) {
        scanf("%s", cmd);

        if (strcmp(cmd, "DONE") == 0) {
            break;
        } else if (strcmp(cmd, "PRINT") == 0) {
            printf("%d\n", evaluate_tree(root));
        } else if (strcmp(cmd, "SET") == 0) {
            int value;
            char var;
            scanf("%d %c", &value, &var);
            set_variable_value(var, value);
        }
    }

    return 0;
}
