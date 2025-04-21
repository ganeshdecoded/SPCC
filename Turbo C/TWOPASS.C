#include <stdio.h>
#include <string.h>
#include <conio.h>

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

void main() {
    struct symb sy[10];
    struct base ba[10];
    char data[9][40] = {
        "START 0",
        "USING *,15",
        "L 1,FIVE",
        "A 1,FOUR",
        "ST 1,TEMP",
        "FOUR DC F'4'",
        "FIVE DC F'5'",
        "TEMP DS 1F",
        "END"
    };

    char token[20], *ptr;
    char oneword[100], base[10];
    int i = 0, j = 0, k = 0, l = 0, f = 0, length = 0;

    clrscr();

    printf("Program input:\n");
    for (i = 0; i < 9; i++) {
        puts(data[i]);
    }

    printf("\nPASS 1\n");
    l = 0;
    i = 0;
    for (k = 0; k < 9; k++) {
        strcpy(oneword, data[k]);
        ptr = strtok(oneword, " ,\n");

        if (strcmp(ptr, "USING") == 0) {
            f = 1;
            ptr = strtok(NULL, " ,\n");
            strcpy(base, ptr);
            strcpy(ba[i].base, base);
            ba[i].content = 0;
            ba[i].indicator = 'y';
            i++;
            j = i;
        } else if (f == 1 && strcmp(ptr, "END") != 0 && strcmp(ptr, "START") != 0) {
            printf("%d\t%s\t", l, ptr);
            ptr = strtok(NULL, " ,\n");

            if (strcmp(ptr, "DC") == 0 || strcmp(ptr, "DS") == 0) {
                l += 4;
                continue;
            } else {
                printf("%s,_(0,%s)", ptr, base);
                l += 4;
            }
        }
    }

    printf("\n\nSymbol Table:\n");
    l = 0;
    i = 0;
    for (k = 0; k < 9; k++) {
        strcpy(oneword, data[k]);
        ptr = strtok(oneword, " ,\n");

        if (strcmp(ptr, "START") == 0) {
            ptr = strtok(NULL, " ,\n");
            l = atoi(ptr);
            continue;
        }

        if (strcmp(ptr, "USING") == 0) {
            l = 0;
            continue;
        } else if (strcmp(ptr, "L") == 0 || strcmp(ptr, "A") == 0 || strcmp(ptr, "ST") == 0) {
            l += 4;
            continue;
        } else if (strcmp(ptr, "END") == 0) {
            continue;
        } else {
            strcpy(sy[i].s, ptr);
            sy[i].value = l;
            sy[i].length = 4;
            sy[i].a = 'R';
            l += 4;
            i++;
        }
    }

    length = i;

    printf("Symbol\tValue\tLength\tRegister\n");
    for (i = 0; i < length; i++) {
        printf("%s\t%d\t%d\t%c\n", sy[i].s, sy[i].value, sy[i].length, sy[i].a);
    }

    printf("\nBase Table:\n");
    printf("Base\tIndicator\tContent\n");
    for (i = 0; i < j; i++) {
        printf("%s\t%c\t\t%d\n", ba[i].base, ba[i].indicator, ba[i].content);
    }

    printf("\nPASS 2\n");
    l = 0;
    for (k = 0; k < 9; k++) {
        strcpy(oneword, data[k]);
        ptr = strtok(oneword, " ,\n");

        if (strcmp(ptr, "START") == 0 || strcmp(ptr, "USING") == 0) {
            l = 0;
            continue;
        } else if (strcmp(ptr, "END") != 0) {
            printf("%d\t%s\t", l, ptr);
            ptr = strtok(NULL, " ,\n");

            if (strcmp(ptr, "DC") == 0 || strcmp(ptr, "DS") == 0) {
                l += 4;
                continue;
            } else {
                printf("%s,", ptr);
            }

            ptr = strtok(NULL, "\n");
            for (i = 0; i < length; i++) {
                if (strcmp(ptr, sy[i].s) == 0) {
                    printf("%d(0,%s)", sy[i].value, base);
                    break;
                }
            }
            l += 4;
        }
    }

    getch();
}
