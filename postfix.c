#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Stack for characters (operators)
char stack[MAX];
int top = -1;

void push(char x) {
    stack[++top] = x;
}

char pop() {
    if (top == -1) return -1;
    return stack[top--];
}

int precedence(char x) {
    if (x == '+' || x == '-') return 1;
    if (x == '*' || x == '/') return 2;
    if (x == '^') return 3;
    return 0;
}

// Infix to Postfix conversion
void infixToPostfix(char infix[], char postfix[]) {
    int i = 0, k = 0;
    char ch;
    while ((ch = infix[i++]) != '\0') {
        if (isalnum(ch)) {  // operand
            postfix[k++] = ch;
        }
        else if (ch == '(') {
            push(ch);
        }
        else if (ch == ')') {
            while (top != -1 && stack[top] != '(')
                postfix[k++] = pop();
            pop(); // remove '('
        }
        else { // operator
            while (top != -1 && precedence(stack[top]) >= precedence(ch))
                postfix[k++] = pop();
            push(ch);
        }
    }
    while (top != -1)
        postfix[k++] = pop();
    postfix[k] = '\0';
}

// Stack for integers (Postfix evaluation)
int valStack[MAX];
int valTop = -1;

void pushVal(int x) {
    valStack[++valTop] = x;
}

int popVal() {
    return valStack[valTop--];
}

// Postfix Evaluation
int evaluatePostfix(char postfix[]) {
    int i = 0;
    char ch;
    while ((ch = postfix[i++]) != '\0') {
        if (isdigit(ch)) {
            char temp[2];
            temp[0] = ch; temp[1] = '\0';
            pushVal(atoi(temp));  // convert char → int
        }
        else {
            int val2 = popVal();
            int val1 = popVal();
            switch (ch) {
                case '+': pushVal(val1 + val2); break;
                case '-': pushVal(val1 - val2); break;
                case '*': pushVal(val1 * val2); break;
                case '/': pushVal(val1 / val2); break;
            }
        }
    }
    return popVal();
}

// Menu
int main() {
    char infix[MAX], postfix[MAX];
    int choice;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Infix to Postfix\n");
        printf("2. Postfix Evaluation\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // consume newline

        switch (choice) {
            case 1:
                printf("Enter Infix Expression: ");
                gets(infix);
                infixToPostfix(infix, postfix);
                printf("Postfix Expression: %s\n", postfix);
                break;

            case 2:
                printf("Enter Postfix Expression: ");
                gets(postfix);
                printf("Result = %d\n", evaluatePostfix(postfix));
                break;

            case 3:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 3);

    return 0;
}
