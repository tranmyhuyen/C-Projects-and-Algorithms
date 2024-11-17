/*
Stack (Ngăn xếp):

Dùng để chuyển đổi biểu thức từ dạng trung tố (infix) sang dạng hậu tố (postfix) theo thuật toán Shunting-yard.
Hỗ trợ trong quá trình xây dựng cây biểu thức từ biểu thức hậu tố bằng cách lưu trữ các nút khi gặp toán tử.

Tree (Cây biểu thức):

Cấu trúc cây biểu thức giúp biểu diễn và đánh giá biểu thức toán học. Cây giúp xác định thứ tự thực hiện các phép toán và cho phép đánh giá biểu thức một cách tự nhiên theo cấu trúc cây.
Khi cây đã được tạo, việc tính toán giá trị của biểu thức trở nên dễ dàng thông qua duyệt cây (theo thứ tự hậu tự).

Hash Table (Bảng băm):

Dùng để lưu trữ và quản lý giá trị của các biến trong biểu thức.
Khi gặp lệnh SET, bảng băm sẽ cập nhật hoặc thêm giá trị cho biến tương ứng.
Khi đánh giá biểu thức, nếu gặp biến, chương trình sẽ tra cứu giá trị biến trong bảng băm.
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define TABLE_SIZE 100

// ---------- Cấu trúc Stack ----------
typedef struct {
    void* items[MAX_STACK_SIZE];
    int top;
} Stack;

void init_stack(Stack* s) {
    s->top = -1;
}

int is_empty(Stack* s) {
    return s->top == -1;
}

int is_full(Stack* s) {
    return s->top == MAX_STACK_SIZE - 1;
}

void push(Stack* s, void* item) {
    if (is_full(s)) {
        printf("Stack đầy!\n");
        return;
    }
    s->items[++(s->top)] = item;
}

void* pop(Stack* s) {
    if (is_empty(s)) {
        printf("Stack rỗng!\n");
        return NULL;
    }
    return s->items[(s->top)--];
}

void* peek(Stack* s) {
    if (is_empty(s)) {
        return NULL;
    }
    return s->items[s->top];
}

// ---------- Cấu trúc Cây Biểu Thức ----------
typedef struct TreeNode {
    char value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* create_tree_node(char value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ---------- Cấu trúc Bảng Băm (HashTable) ----------
typedef struct {
    char key;
    int value;
} HashEntry;

typedef struct {
    HashEntry table[TABLE_SIZE];
} HashTable;

int hash_function(char key) {
    return key % TABLE_SIZE;
}

void init_hash_table(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i].key = '\0';
        ht->table[i].value = 0;
    }
}

void set_variable(HashTable* ht, char key, int value) {
    int index = hash_function(key);
    ht->table[index].key = key;
    ht->table[index].value = value;
}

int get_variable(HashTable* ht, char key) {
    int index = hash_function(key);
    if (ht->table[index].key == key) {
        return ht->table[index].value;
    }
    return 0;
}

// ---------- Đánh giá Cây Biểu Thức ----------
int evaluate_tree(TreeNode* root, HashTable* ht) {
    if (!root) return 0;

    if (!root->left && !root->right) {
        if (isdigit(root->value)) {
            return root->value - '0';
        }
        return get_variable(ht, root->value);
    }

    int left_val = evaluate_tree(root->left, ht);
    int right_val = evaluate_tree(root->right, ht);

    switch (root->value) {
        case '+': return left_val + right_val;
        case '-': return left_val - right_val;
        case '*': return left_val * right_val;
        default: return 0;
    }
}

// ---------- Hàm Chuyển Đổi Biểu Thức Trung Tố Sang Hậu Tố ----------
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*') return 2;
    return 0;
}

int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*');
}

void infix_to_postfix(const char* infix, char* postfix) {
    Stack s;
    init_stack(&s);
    int j = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];

        if (isalnum(c)) {
            postfix[j++] = c;
        } else if (c == '(') {
            push(&s, (void*)(long)c);  // Chuyển đổi để lưu char vào stack
        } else if (c == ')') {
            while (!is_empty(&s) && (char)(long)peek(&s) != '(') {
                postfix[j++] = (char)(long)pop(&s);
            }
            pop(&s); // Loại bỏ '(' khỏi stack
        } else if (is_operator(c)) {
            while (!is_empty(&s) && precedence((char)(long)peek(&s)) >= precedence(c)) {
                postfix[j++] = (char)(long)pop(&s);
            }
            push(&s, (void*)(long)c);
        }
    }

    while (!is_empty(&s)) {
        postfix[j++] = (char)(long)pop(&s);
    }
    postfix[j] = '\0';
}

// ---------- Xây Dựng Cây Biểu Thức từ Biểu Thức Hậu Tố ----------
TreeNode* build_expression_tree(const char* postfix) {
    Stack nodeStack;
    init_stack(&nodeStack);

    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];

        TreeNode* node = create_tree_node(c);
        if (is_operator(c)) {
            node->right = (TreeNode*)pop(&nodeStack);
            node->left = (TreeNode*)pop(&nodeStack);
        }
        push(&nodeStack, node);
    }
    return (TreeNode*)pop(&nodeStack);
}

// ---------- Hàm Chính ----------
int main() {
    char expression[100];
    char cmd[10];
    HashTable ht;
    init_hash_table(&ht);

    scanf("%s", expression);

    char postfix[100];
    infix_to_postfix(expression, postfix);

    TreeNode* root = build_expression_tree(postfix);

    while (1) {
        scanf("%s", cmd);
        if (strcmp(cmd, "DONE") == 0) {
            break;
        } else if (strcmp(cmd, "PRINT") == 0) {
            int result = evaluate_tree(root, &ht);
            printf("%d\n", result);
        } else if (strcmp(cmd, "SET") == 0) {
            char var;
            int value;
            scanf(" %d %c", &value, &var);
            set_variable(&ht, var, value);
        }
    }

    return 0;
}

