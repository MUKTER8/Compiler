#include <stdio.h>
#include <string.h>

#define STACK_SIZE 100
#define MAX_PROD 20
#define MAX_SYMBOLS 10

typedef struct {
    int stack[STACK_SIZE];
    int top;
} Stack;

void push(Stack *s, int item) {
    if (s->top < STACK_SIZE - 1)
        s->stack[++(s->top)] = item;
    else
        printf("Stack Overflow\n");
}

int pop(Stack *s) {
    if (s->top >= 0)
        return s->stack[(s->top)--];
    else {
        printf("Stack Underflow\n");
        return -1;
    }
}

int peek(Stack *s) {
    if (s->top >= 0)
        return s->stack[s->top];
    else
        return -1;
}

char productions[MAX_PROD][20];
int productionLength[MAX_PROD];
int numProductions;

// Action Table and Number Table
char actionTable[10][MAX_SYMBOLS];
int numberTable[10][MAX_SYMBOLS];

// Goto Table
int gotoTable[10];

// Symbol mapping
char symbols[MAX_SYMBOLS];
int numSymbols = 0;

int getSymbolIndex(char symbol) {
    for (int i = 0; i < numSymbols; i++) {
        if (symbols[i] == symbol) return i;
    }
    return -1;
}

void slrParser(char *input) {
    Stack stateStack;
    stateStack.top = -1;
    push(&stateStack, 0); // Push initial state

    int ip = 0; // input pointer

    while (1) {
        int currentState = peek(&stateStack);
        char currentSymbol = input[ip];
        int symbolIndex = getSymbolIndex(currentSymbol);

        if (symbolIndex == -1) {
            printf("Invalid symbol encountered: %c\n", currentSymbol);
            break;
        }

        char action = actionTable[currentState][symbolIndex];
        int number = numberTable[currentState][symbolIndex];

        if (action == 's') {
            printf("Shift operation (shift to state %d)\n", number);
            push(&stateStack, number);
            ip++;
        } 
        else if (action == 'r') {
            printf("Reduce using production: %s\n", productions[number]);
            for (int i = 0; i < productionLength[number]; i++) {
                pop(&stateStack);
            }
            int topState = peek(&stateStack);
            push(&stateStack, gotoTable[topState]);
        } 
        else if (action == 'a') {
            printf("String accepted!\n");
            break;
        } 
        else {
            printf("Error: Invalid action\n");
            break;
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &numProductions);

    for (int i = 1; i <= numProductions; i++) {
        printf("Enter production %d (format: S->aS): ", i);
        scanf("%s", productions[i]);
        productionLength[i] = strlen(productions[i]) - 3; // Count symbols on RHS
    }

    printf("Enter number of input symbols (terminals + $): ");
    scanf("%d", &numSymbols);

    printf("Enter symbols one by one (example: a b $): ");
    for (int i = 0; i < numSymbols; i++) {
        scanf(" %c", &symbols[i]);
    }

    printf("Enter Action Table (row by row):\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < numSymbols; j++) {
            printf("Action[%d][%c] (s=shift, r=reduce, a=accept, .=error): ", i, symbols[j]);
            scanf(" %c", &actionTable[i][j]);
            if (actionTable[i][j] == 's' || actionTable[i][j] == 'r') {
                printf("Enter number (state number or production number): ");
                scanf("%d", &numberTable[i][j]);
            } else {
                numberTable[i][j] = -1;
            }
        }
    }

    printf("Enter Goto Table for non-terminal S (10 entries, -1 if invalid):\n");
    for (int i = 0; i < 10; i++) {
        printf("Goto[%d]: ", i);
        scanf("%d", &gotoTable[i]);
    }

    char input[STACK_SIZE];
    printf("Enter input string ending with $: ");
    scanf("%s", input);

    slrParser(input);

    return 0;
}
