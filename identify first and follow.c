#include <stdio.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>

#define MAX 10

char production[MAX][MAX], first[MAX][MAX], follow[MAX][MAX];
int n, firstComputed[MAX], followComputed[MAX];

void findFirst(char, int);
void findFollow(char);
void addToResultSet(char[], char);
int isNonTerminal(char);

int main() {
    int i;
    char ch;

    printf("Enter the number of productions: ");
    scanf("%d", &n);

    printf("Enter the productions (e.g., S=AB):\n");
    for (i = 0; i < n; i++) {
        scanf("%s", production[i]);
        first[i][0] = '\0';  // Initialize first set
        follow[i][0] = '\0'; // Initialize follow set
        firstComputed[i] = 0;
        followComputed[i] = 0;
    }

    for (i = 0; i < n; i++) {
        ch = production[i][0];
        if (!firstComputed[i]) {
            findFirst(ch, i);
        }
    }

    printf("\nFirst Sets:\n");
    for (i = 0; i < n; i++) {
        printf("FIRST(%c) = { %s }\n", production[i][0], first[i]);
    }

    follow[0][0] = '$'; // Start symbol always follows '$'
    follow[0][1] = '\0';

    for (i = 0; i < n; i++) {
        ch = production[i][0];
        if (!followComputed[i]) {
            findFollow(ch);
        }
    }

    printf("\nFollow Sets:\n");
    for (i = 0; i < n; i++) {
        printf("FOLLOW(%c) = { %s }\n", production[i][0], follow[i]);
    }

    return 0;
}

void findFirst(char ch, int prodIndex) {
    if (!isNonTerminal(ch)) {
        addToResultSet(first[prodIndex], ch);
        return;
    }

    firstComputed[prodIndex] = 1;

    for (int i = 0; i < n; i++) {
        if (production[i][0] == ch) {
            int j = 2;
            while (production[i][j] != '\0') {
                char nextSymbol = production[i][j];

                if (!isNonTerminal(nextSymbol)) {
                    addToResultSet(first[prodIndex], nextSymbol);
                    break;
                } else {
                    int nextIndex = -1;
                    for (int k = 0; k < n; k++) {
                        if (production[k][0] == nextSymbol) {
                            nextIndex = k;
                            break;
                        }
                    }

                    if (nextIndex != -1) {
                        if (!firstComputed[nextIndex]) {
                            findFirst(nextSymbol, nextIndex);
                        }

                        strcat(first[prodIndex], first[nextIndex]);

                        if (!strchr(first[nextIndex], '#')) {
                            break;
                        }
                    }
                }

                j++;
            }
        }
    }
}

void findFollow(char ch) {
    if (ch == production[0][0]) {
        addToResultSet(follow[0], '$');
    }

    followComputed[ch - 'A'] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 2; production[i][j] != '\0'; j++) {
            if (production[i][j] == ch) {
                if (production[i][j + 1] != '\0') {
                    int nextIndex = -1;
                    for (int k = 0; k < n; k++) {
                        if (production[k][0] == production[i][j + 1]) {
                            nextIndex = k;
                            break;
                        }
                    }

                    if (nextIndex != -1) {
                        strcat(follow[ch - 'A'], first[nextIndex]);

                        if (strchr(first[nextIndex], '#')) {
                            findFollow(production[i][0]);
                            strcat(follow[ch - 'A'], follow[i]);
                        }
                    }
                } else {
                    findFollow(production[i][0]);
                    strcat(follow[ch - 'A'], follow[i]);
                }
            }
        }
    }
}

void addToResultSet(char result[], char ch) {
    if (!strchr(result, ch)) {
        int len = strlen(result);
        result[len] = ch;
        result[len + 1] = '\0';
    }
}

int isNonTerminal(char ch) {
    return (ch >= 'A' && ch <= 'Z');
}