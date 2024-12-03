#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *number;
    int length;
} Number_t;

void init(Number_t *num)
{
    num->number = NULL;
    num->length = 0;
}

void add(Number_t *num, char c)
{
    num->length++;
    num->number = (char *)realloc(num->number, sizeof(char) * num->length);
    if (num->number == NULL) {
        return;
    }

    num->number[num->length - 1] = c;
}

void deinit(Number_t *num)
{
    free(num->number);
    free(num);
}

int part1()
{
    int result = 0;
    char c;
    Number_t *number1 = (Number_t *)malloc(sizeof(Number_t));
    Number_t *number2 = (Number_t *)malloc(sizeof(Number_t));

    init(number1);
    init(number2);

    int inmul = 0;
    FILE *fp = fopen("test.txt", "r");

    while ((c = fgetc(fp)) != EOF) {
        if (c == 'm') {
            inmul = 1;
        } else if (c == 'u' && inmul == 1) {
            inmul = 2;
        } else if (c == 'l' && inmul == 2) {
            inmul = 3;
        } else if (c == '(' && inmul == 3) {
            inmul = 4;
        } else if (c >= '0' && c <= '9') {
            if (inmul == 4 || inmul == 5) {
                add(number1, c);
                inmul = 5;
            } else if (inmul == 6 || inmul == 7) {
                add(number2, c);
                inmul = 7;
            } else {
                inmul = 0;
            }
        } else if (c == ',' && inmul == 5) {
            inmul = 6;
        } else if (c == ')' && inmul == 7) {
            result += atoi(number1->number) * atoi(number2->number);

            init(number1);
            init(number2);

            inmul = 0;
        } else {
            inmul = 0;
        }

        if (inmul == 0) {
            init(number1);
            init(number2);
        }
    }

    deinit(number1);
    deinit(number2);

    fclose(fp);

    return result;
}

int part2()
{
    int result = 0;
    char c;
    int disabled = 0;

    Number_t *number1 = (Number_t *)malloc(sizeof(Number_t));
    Number_t *number2 = (Number_t *)malloc(sizeof(Number_t));

    init(number1);
    init(number2);

    int inmul = 0;
    int indis = 0;
    int inena = 0;
    FILE *fp = fopen("test.txt", "r");

    while ((c = fgetc(fp)) != EOF) {
        if (c == 'd' && indis == 0) {
            indis = 1;
        } else if (c == 'o' && indis == 1) {
            indis = 2;
        } else if (c == '(' && indis == 2) {
            indis = 0;
            inena = 3;
        } else if (c == ')' && inena == 3) {
            disabled = 0;
            inena = 0;
        } else if (c == 'n' && indis == 2) {
            indis = 3;
        } else if (c == '\'' && indis == 3) {
            indis = 4;
        } else if (c == 't' && indis == 4) {
            indis = 5;
        } else if (c == '(' && indis == 5) {
            indis = 6;
        } else if (c == ')' && indis == 6) {
            indis = 0;
            disabled = 1;
        } else {
            indis = 0;
            inena = 0;
        }

        if (c == 'm') {
            inmul = 1;
        } else if (c == 'u' && inmul == 1) {
            inmul = 2;
        } else if (c == 'l' && inmul == 2) {
            inmul = 3;
        } else if (c == '(' && inmul == 3) {
            inmul = 4;
        } else if (c >= '0' && c <= '9') {
            if (inmul == 4 || inmul == 5) {
                add(number1, c);
                inmul = 5;
            } else if (inmul == 6 || inmul == 7) {
                add(number2, c);
                inmul = 7;
            } else {
                inmul = 0;
            }
        } else if (c == ',' && inmul == 5) {
            inmul = 6;
        } else if (c == ')' && inmul == 7 && disabled == 0) {
            result += atoi(number1->number) * atoi(number2->number);

            init(number1);
            init(number2);

            inmul = 0;
        } else {
            inmul = 0;
        }

        if (inmul == 0) {
            init(number1);
            init(number2);
        }
    }

    deinit(number1);
    deinit(number2);

    fclose(fp);

    return result;
}

int main(void)
{
    printf("Part 1: %d\n", part1());
    printf("Part 2: %d\n", part2());
}
