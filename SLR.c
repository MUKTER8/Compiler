#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

char stack[MAX];
int stateStack[MAX];
int top;
char input[MAX];
int ip;

// Function to push symbol and state onto stack
void push(char symbol, int state) {
    stack[++top] = symbol;
    stateStack[top] = state;
}

// Function to pop from stack
void pop() {
    if (top >= 0) top--;
}

// Get parser action based on current state and input symbol
char* action(int state, char symbol) {
    if (state == 0 && symbol == 'a') return "shift1";
    if (state == 0 && symbol == 'b') return "shift2";
    if (state == 1 && symbol == 'a') return "shift1";
    if (state == 1 && symbol == 'b') return "shift2";
    if (state == 2 && symbol == '$') return "accept";
    return "error";
}

// Goto function after a reduction
int goTo(int state, char nonTerminal) {
    if (state == 0 && nonTerminal == 'S') return 3;
    if (state == 1 && nonTerminal == 'S') return 4;
    return -1; // error
}

// Print the current stack content
void printStack() {
    printf("Stack: ");
    for (int i = 0; i <= top; i++) {
        printf("%c%d ", stack[i], stateStack[i]);
    }
    printf("\n");
}

int main() {
    while (1) {
        printf("\nEnter input string ending with $ (or type 'stop' to exit): ");
        scanf("%s", input);

        if (strcmp(input, "stop") == 0) {
            printf("Program terminated by user.\n");
            break;
        }

        // Initialize stack
        top = -1;
        ip = 0;
        push(' ', 0); // initial state 0 with dummy symbol

        while (1) {
            printStack();
            int currentState = stateStack[top];
            char currentSymbol = input[ip];

            char *act = action(currentState, currentSymbol);

            if (strncmp(act, "shift", 5) == 0) {
                int nextState = act[5] - '0';
                push(currentSymbol, nextState);
                ip++;
            } 
            else if (strcmp(act, "accept") == 0) {
                printf("Input string accepted.\n");
                break;
            } 
            else {
                // Try reductions
                if (top >= 1 && stack[top] == 'b') {
                    printf("Reducing: S -> b\n");
                    pop(); // pop 'b'
                    int prevState = stateStack[top];
                    int nextState = goTo(prevState, 'S');
                    push('S', nextState);
                } 
                else if (top >= 2 && stack[top-1] == 'a' && stack[top] == 'S') {
                    printf("Reducing: S -> aS\n");
                    pop(); // pop 'S'
                    pop(); // pop 'a'
                    int prevState = stateStack[top];
                    int nextState = goTo(prevState, 'S');
                    push('S', nextState);
                } 
                else {
                    printf("Error: invalid string.\n");
                    break;
                }
            }
        }
    }
    return 0;
}
