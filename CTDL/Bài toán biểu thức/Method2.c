#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    char var;
    int value;
} Variable;

// Hàm tìm giá trị biến
int get_variable_value(Variable vars[], int var_count, char var) {
    for (int i = 0; i < var_count; ++i) {
        if (vars[i].var == var)
            return vars[i].value;
    }
    return 0; // Giá trị mặc định nếu biến chưa được định nghĩa
}

// Hàm cập nhật hoặc thêm mới biến
void set_variable_value(Variable vars[], int *var_count, char var, int value) {
    for (int i = 0; i < *var_count; ++i) {
        if (vars[i].var == var) {
            vars[i].value = value;
            return;
        }
    }
    // Nếu biến chưa tồn tại, thêm mới
    vars[*var_count].var = var;
    vars[*var_count].value = value;
    (*var_count)++;
}

// Hàm kiểm tra toán tử
int is_operator(char c) {
    return c == '+' || c == '-' || c == '*';
}

// Hàm ưu tiên toán tử
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*')
        return 2;
    return 0;
}

// Hàm chuyển đổi biểu thức từ trung tố sang hậu tố
int infix_to_postfix(char *infix, char *postfix) {
    char stack[MAX];
    int top = -1, k = 0;
    for (int i = 0; infix[i]; ++i) {
        if (isdigit(infix[i]) || isalpha(infix[i])) {
            postfix[k++] = infix[i]; // Chữ số hoặc biến được thêm vào chuỗi hậu tố
        } else if (infix[i] == '(') {
            stack[++top] = infix[i];
        } else if (infix[i] == ')') {
            while (top != -1 && stack[top] != '(')
                postfix[k++] = stack[top--];
            top--; // Loại bỏ dấu '(' khỏi ngăn xếp
        } else if (is_operator(infix[i])) {
            while (top != -1 && precedence(stack[top]) >= precedence(infix[i]))
                postfix[k++] = stack[top--];
            stack[++top] = infix[i];
        }
    }
    while (top != -1)
        postfix[k++] = stack[top--];
    postfix[k] = '\0';
    return k;
}

// Hàm đánh giá biểu thức hậu tố
int evaluate_postfix(char *postfix, Variable vars[], int var_count) {
    int stack[MAX], top = -1;
    for (int i = 0; postfix[i]; ++i) {
        if (isdigit(postfix[i])) {
            stack[++top] = postfix[i] - '0'; // Chuyển từ ký tự số sang giá trị số
        } else if (isalpha(postfix[i])) {
            stack[++top] = get_variable_value(vars, var_count, postfix[i]);
        } else if (is_operator(postfix[i])) {
            int b = stack[top--];
            int a = stack[top--];
            if (postfix[i] == '+') stack[++top] = a + b;
            if (postfix[i] == '-') stack[++top] = a - b;
            if (postfix[i] == '*') stack[++top] = a * b;
        }
    }
    return stack[top];
}

int main() {
    char s[MAX], cmd[10];
    Variable vars[MAX];
    int var_count = 0;

    scanf("%s", s);

    char postfix[MAX];
    infix_to_postfix(s, postfix);

    while (1) {
        scanf("%s", cmd);
        if (strcmp(cmd, "DONE") == 0)
            break;
        if (strcmp(cmd, "PRINT") == 0) {
            int result = evaluate_postfix(postfix, vars, var_count);
            printf("%d\n", result);
        } else if (strcmp(cmd, "SET") == 0) {
            char x;
            int v;
            scanf("%d %c", &v, &x);
            set_variable_value(vars, &var_count, x, v);
        }
    }

    return 0;
}
