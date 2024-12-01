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

void sort(List *list)
{
    for (int i = 0; i < list->size; i++) {
        for (int j = i + 1; j < list->size; j++) {
            if (list->list[i] > list->list[j]) {
                int tmp = list->list[i];
                list->list[i] = list->list[j];
                list->list[j] = tmp;
            }
        }
    }
}

int part1()
{
    char buf[256];
    List *list1 = (List *)malloc(sizeof(List));
    List *list2 = (List *)malloc(sizeof(List));
    if (list1 == NULL || list2 == NULL)
        return 1;

    init(list1);
    init(list2);

    FILE *fp = fopen("test.txt", "r");
    if (fp == NULL)
        return 1;

    while (fgets(buf, sizeof(buf), fp)) {
        char *num1 = strtok(buf, " ");
        char *num2 = strtok(NULL, " ");

        add(list1, atoi(num1));
        add(list2, atoi(num2));
    }

    sort(list1);
    sort(list2);

    int result = 0;

    for (int i = 0; i < list1->size; i++) {
        result += abs(list1->list[i] - list2->list[i]);
    }

    return result;
}

int part2()
{
    char buf[256];
    List *list1 = (List *)malloc(sizeof(List));
    List *list2 = (List *)malloc(sizeof(List));
    if (list1 == NULL || list2 == NULL)
        return 1;

    init(list1);
    init(list2);

    FILE *fp = fopen("test.txt", "r");
    if (fp == NULL)
        return 1;

    while (fgets(buf, sizeof(buf), fp)) {
        char *num1 = strtok(buf, " ");
        char *num2 = strtok(NULL, " ");

        add(list1, atoi(num1));
        add(list2, atoi(num2));
    }

    int result = 0;

    for (int i = 0; i < list1->size; i++) {
        int simcount = 0;

        for (int j = 0; j < list2->size; j++) {
            if (list1->list[i] == list2->list[j])
                simcount++;
        }

        result += list1->list[i] * simcount;
    }

    return result;
}

int main()
{
    printf("Part 1: %d\n", part1());
    printf("Part 2: %d\n", part2());
    return 0;
}
