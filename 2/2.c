#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *list;
    int size;
} List;

void init(List *list)
{
    list->list = NULL;
    list->size = 0;
}

void add(List *list, int value)
{
    list->size++;
    list->list = (int *)realloc(list->list, sizeof(int) * list->size);
    list->list[list->size - 1] = value;
}

void deinit(List *list)
{
    free(list->list);
    free(list);
}

int compare(int a, int b)
{
    if (a > b)
        return 1;
    else if (a < b)
        return 0;
    else
        return 2;
}

int difference(char *a, char *b)
{
    if (abs(atoi(a) - atoi(b)) > 3) {
        return 1;
    } else {
        return 0;
    }
}

int part1()
{
    int safecount = 0;
    char buf[256];

    FILE *fp = fopen("test.txt", "r");
    if (fp == NULL)
        return 1;

    while (fgets(buf, sizeof(buf), fp)) {
        int safe = 1;

        char *current = strtok(buf, " ");
        char *next = strtok(NULL, " ");

        int state = compare(atoi(current), atoi(next));

        if (state == 2)
            continue;

        while (next != NULL) {
            if (compare(atoi(current), atoi(next)) == state) {
                if (abs(atoi(current) - atoi(next)) > 3) {
                    safe = 0;
                    break;
                }
                
                current = next;
                next = strtok(NULL, " ");
            } else {
                safe = 0;
                break;
            }
        }

        if (safe == 1)
            safecount++;
    }

    fclose(fp);

    return safecount;
}

int part2()
{
    List *nums = (List *)malloc(sizeof(List));

    int safecount = 0;
    char buf[256];

    FILE *fp = fopen("test.txt", "r");
    if (fp == NULL)
        return 1;

    while (fgets(buf, sizeof(buf), fp)) {
        int safe = 1;

        char *num = strtok(buf, " ");

        while (num != NULL) {
            add(nums, atoi(num));
            num = strtok(NULL, " ");
        }

        int ignored = 0;

        while (ignored < nums->size) {
            safe = 1;
            int current = 0;
            int next = 1;
            int state = compare(nums->list[current], nums->list[next]);

            while (next < nums->size) {
                if (current == ignored) {
                    current++;
                    next++;
                    continue;
                }

                if (next == ignored) {
                    next++;
                    continue;
                }

                if (compare(nums->list[current], nums->list[next]) == state) {
                    if (abs(nums->list[current] - nums->list[next]) > 3) {
                        safe = 0;
                        break;
                    }

                    current = next;
                    next++;
                } else {
                    safe = 0;
                    break;
                }
            }

            ignored++;
        }
    }

    deinit(nums);

    return safecount;
}

int main(void)
{
    printf("Part 1: %d\n", part1());
    printf("Part 2: %d\n", part2());
}
