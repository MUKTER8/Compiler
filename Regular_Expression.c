#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_valid_email(char email[]) {
    char email_copy[1000];
    strncpy(email_copy, email, sizeof(email_copy));
    email_copy[sizeof(email_copy) - 1] = '\0';

    int at_count = 0;
    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            at_count++;
        }
    }
    if (at_count != 1) {
        return 0;
    }

    char *local_part = strtok(email_copy, "@");
    char *domain = strtok(NULL, "@");

    if (!local_part || !domain || local_part[0] == '\0' || domain[0] == '\0') {
        return 0;
    }

    if (!isalpha(local_part[0])) {
        return 0;
    }

    for (int i = 0; local_part[i] != '\0'; i++) {
        if (!isalnum(local_part[i]) && local_part[i] != '.' && local_part[i] != '-' && local_part[i] != '_') {
            return 0;
        }
    }

    int dot_found = 0;
    int prev_char_was_dot = 0;
    for (int i = 0; domain[i] != '\0'; i++) {
        if (!isalnum(domain[i]) && domain[i] != '.') {
            return 0;
        }
        if (domain[i] == '.') {
            dot_found = 1;
            if (prev_char_was_dot) {
                return 0;
            }
            prev_char_was_dot = 1;
        } else {
            prev_char_was_dot = 0;
        }
    }

    if (domain[0] == '.' || domain[strlen(domain) - 1] == '.' || !dot_found) {
        return 0;
    }

    return 1;
}

int is_valid_web_address(char web[]) {
    if (strncmp(web, "http://", 7) == 0) {
        web += 7;
    } else if (strncmp(web, "https://", 8) == 0) {
        web += 8;
    } else if (strncmp(web, "www.", 4) == 0) {
        web += 4;
    }

    if (strchr(web, '.') == NULL || web[0] == '.' || web[strlen(web) - 1] == '.') {
        return 0;
    }

    for (int i = 0; web[i] != '\0'; i++) {
        if (!isalnum(web[i]) && web[i] != '.' && web[i] != '-') {
            return 0;
        }
    }

    return 1;
}

int main() {
 printf("Enter Email or Web (or type 'exit' to stop):\n ");
        while (1) {
            char input[1000];
            printf("Input: ");
           
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0';

            if (strcmp(input, "exit") == 0) {
                printf("Program stopped.\n");
                break;
            }

            if (is_valid_email(input)) {
                printf("Output:Valid Email\n");
            } else if (is_valid_web_address(input)) {
                printf("Output:Valid Web Address\n");
            } else {
                printf("Output:Invalid\n");
            }
        }

    return 0;
}
