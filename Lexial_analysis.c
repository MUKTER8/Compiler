#include <stdio.h>//this 
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_TLEN 100
#define MAX_OLEN 1000
#define MAX_TKS 500

const char *keywords[] = {"int", "float", "if", "else"};
#define KW_COUNT (sizeof(keywords) / sizeof(keywords[0]))

char tokens[MAX_TKS][MAX_TLEN];
int tk_count = 0;
int kw_count = 0, id_count = 0, mop_count = 0;
int lop_count = 0, num_count = 0, oth_count = 0;

int is_keyword(const char *str) {
    for (int i = 0; i < KW_COUNT; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

void add_to_output(char *output, const char *token) {
    strcat(output, token);
    strcat(output, " ");
}

void add_token(const char *token) {
    if (tk_count < MAX_TKS) {
        strcpy(tokens[tk_count], token);
        tk_count++;
    }
}

void classify_token(const char *token, char *outputs[]) {
    if (is_keyword(token)) {
        add_to_output(outputs[0], token);
        add_token(token);
        kw_count++;
    } else if (isdigit(token[0]) || token[0] == '.') {
        for (int i = 0; token[i] != '\0'; i++) {
            if (!isdigit(token[i]) && token[i] != '.') {
                printf("Error: Invalid number '%s'\n", token);
                return;
            }
        }
        add_to_output(outputs[4], token);
        add_token(token);
        num_count++;
    } else if (isalpha(token[0])) {
        add_to_output(outputs[1], token);
        add_token(token);
        id_count++;
    } else if (strchr("+-=*/", token[0])) {
        add_to_output(outputs[2], token);
        add_token(token);
        mop_count++;
    } else if (strchr("<>", token[0])) {
        add_to_output(outputs[3], token);
        add_token(token);
        lop_count++;
    } else {
        printf("Error: Unrecognized token '%s'\n", token);
        oth_count++;
    }
}

void parse_input(FILE *file) {
    char ch, token[MAX_TLEN];
    int token_len = 0;
    char kw_out[MAX_OLEN] = "Keywords: ";
    char id_out[MAX_OLEN] = "Identifiers: ";
    char mop_out[MAX_OLEN] = "Math Operators: ";
    char lop_out[MAX_OLEN] = "Logical Operators: ";
    char num_out[MAX_OLEN] = "Numerical Values: ";
    char oth_out[MAX_OLEN] = "Others: ";
    char *outputs[] = {kw_out, id_out, mop_out, lop_out, num_out, oth_out};

    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch) || strchr(",;(){}[]", ch)) {
            if (token_len > 0) {
                token[token_len] = '\0';
                classify_token(token, outputs);
                token_len = 0;
            }
            if (strchr(",;(){}[]", ch)) {
                char symbol[2] = {ch, '\0'};
                add_to_output(oth_out, symbol);
                oth_count++;
            }
        } else {
            token[token_len++] = ch;
        }
    }
    if (token_len > 0) {
        token[token_len] = '\0';
        classify_token(token, outputs);
    }

    for (int i = 0; i < 6; i++) {
        printf("%s\n", outputs[i]);
    }

    printf("\nTotal Keywords: %d\n", kw_count);
    printf("Total Identifiers: %d\n", id_count);
    printf("Total Math Operators: %d\n", mop_count);
    printf("Total Logical Operators: %d\n", lop_count);
    printf("Total Numerical Values: %d\n", num_count);
    printf("Total Others: %d\n", oth_count);
}

int main()
 {
    FILE *file = fopen("D://Compiler/input.txt", "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }
    parse_input(file);
    fclose(file);

    return 0;
}
