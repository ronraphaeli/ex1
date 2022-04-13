#include "RLEList.h"
#include <stdlib.h>
#define HEAD 0

struct  RLEList_t {
    char data;
    struct RLEList_t * next;
    struct RLEList_t * last;
    int multiplier;
};

void RLEListDestroy(RLEList list) {
    while (list) {
        RLEList toDelete = list;
        //printf("%d\n", toDelete->multiplier);
        list = list->next;
        free(toDelete);
    }
};

RLEList RLEListCreate() {
    RLEList list = malloc(sizeof(*list));
    if (!list) return NULL;
    list->data = HEAD;
    list->next = NULL;
    list->last = list;
    return list;
}

RLEListResult RLEListAppend(RLEList list, char value) {
    if (!list || !list->last)
        return RLE_LIST_NULL_ARGUMENT;
    if (list->last->data == value) {
        list->last->multiplier++;
        return RLE_LIST_SUCCESS;
    }
    RLEList newLink = malloc(sizeof(*list));
    if (!newLink) return RLE_LIST_OUT_OF_MEMORY;
    newLink->next = NULL;
    newLink->data = value;
    newLink->multiplier = 1;
    list->last->next = newLink;
    list->last = newLink;
    return  RLE_LIST_SUCCESS;
}

int main() {
    RLEList list = RLEListCreate();
    RLEListAppend(list, 'C');
    RLEListAppend(list, 'C');
    RLEListAppend(list, 'r');
    RLEListAppend(list, 'r');
    RLEListAppend(list, 'r');
    RLEListDestroy(list);
}
//implement the functions here
