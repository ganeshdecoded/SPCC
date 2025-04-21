#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int length = 0;

struct symb {
    char s[10];
    int value;
    int length;
    char a;
};

struct base {
    char base[10];
    int content;
    char indicator;
};

struct symb sy[10];

int main() {
    struct base ba[10];

    // Hardcoded input lines
    const char *lines[] = {
        "START 0",
        "USING *, 15",
        "L 1,FIVE",
        "A 1,FOUR",
        "ST 1,TEMP",
        "FOUR DC F'4'",
        "FIVE DC F'5'",
        "TEMP DS 1F",
        "END"
    };

    char oneword[100], base[10];
    char *token;
    int i = 0, l = 0, j = 0, k = 0, f = 0;
    int lineCount = sizeof(lines) / sizeof(lines[0]);

    printf("Program input:\n");
    for (int idx = 0; idx < lineCount; idx++) {
        printf("\t%s\n", lines[idx]);
    }

    /********** PASS 1 ************/
    printf("\nPASS 1\n");
    i = 0;
    l = 0;
    for (int idx = 0; idx < lineCount; idx++) {
        strcpy(oneword, lines[idx]);
        token = strtok(oneword, " \t\n");

        if (token == NULL) continue;

        if (strcmp(token, "USING") == 0) {
            f = 1;
            token = strtok(NULL, " *,\t\n");
            if (token != NULL) {
                strcpy(base, token);
                strcpy(ba[i].base, base);
                ba[i].content = 0;
                ba[i].indicator = 'y';
                i++;
                j = i;
            }
        } else if (f == 1 && strcmp(token, "END") != 0 && strcmp(token, "START") != 0) {
            printf("\n%d\t%s\t", l, token);
            token = strtok(NULL, " ,\t\n");
            if (token != NULL && (strcmp(token, "DC") == 0 || strcmp(token, "DS") == 0)) {
                l += 4;
                continue;
            } else if (token != NULL) {
                printf("%s,_(0,%s)", token, base);
                l += 4;
            }
        }
    }

    /********** SYMBOL TABLE **********/
    l = 0;
    i = 0;
    for (int idx = 0; idx < lineCount; idx++) {
        strcpy(oneword, lines[idx]);
        token = strtok(oneword, " \t\n");

        if (token == NULL) continue;

        if (strcmp(token, "START") == 0) {
            token = strtok(NULL, " \t\n");
            if (token != NULL) {
                l = atoi(token);
            }
            continue;
        }

        if (strcmp(token, "USING") == 0) {
            l = 0;
            continue;
        } else if (strcmp(token, "L") == 0 || strcmp(token, "ST") == 0 || strcmp(token, "A") == 0) {
            l += 4;
            continue;
        } else if (strcmp(token, "END") == 0) {
            continue;
        } else {
            strcpy(sy[i].s, token);
            sy[i].value = l;
            sy[i].length = 4;
            sy[i].a = 'R';
            l += 4;
            i++;
        }
    }
    length = i;

    printf("\nSymbol Table:\n");
    printf("Symbol\tValue\tLength\tRegister\n");
    for (k = 0; k < length; k++) {
        printf("%s\t%d\t%d\t%c\n", sy[k].s, sy[k].value, sy[k].length, sy[k].a);
    }

    /********** BASE TABLE **********/
    printf("\nBase Table:\n");
    printf("Base\tIndicator\tContent\n");
    for (k = 0; k < j; k++) {
        printf("%s\t%c\t\t%d\n", ba[k].base, ba[k].indicator, ba[k].content);
    }

    /********** PASS 2 **********/
    printf("\nPASS 2\n");
    l = 0;
    for (int idx = 0; idx < lineCount; idx++) {
        strcpy(oneword, lines[idx]);
        token = strtok(oneword, " ,\t\n");

        if (token == NULL) continue;

        if (strcmp(token, "PROG") == 0 || strcmp(token, "USING") == 0 || strcmp(token, "START") == 0) {
            l = 0;
            continue;
        } else if (strcmp(token, "END") != 0) {
            printf("\n%d\t%s\t", l, token);
            token = strtok(NULL, " ,\t\n");
            if (token == NULL) continue;

            if (strcmp(token, "DC") == 0 || strcmp(token, "DS") == 0) {
                l += 4;
                continue;
            } else {
                printf("%s,", token);
            }

            token = strtok(NULL, "\n");
            for (i = 0; i < length; i++) {
                if (token != NULL && strcmp(token, sy[i].s) == 0) {
                    printf("%d(0,%s)", sy[i].value, base);
                    break;
                }
            }
            l += 4;
        }
    }

    printf("\n");
    return 0;
}
