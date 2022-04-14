#include "RLEList.h"
#include <stdlib.h>
#define HEAD 0

typedef struct  RLEListItem_t {
    char data;
    struct RLEListItem_t* next;
    int multiplier;
} *RLEListItem;

struct  RLEList_t {
     RLEListItem  head;
    RLEListItem  last;
    int size;
};

void RLEListDestroy(RLEList list) {
    if (list == NULL)
       return;
    RLEListItem item  = list->head;
    free(list);
    while (item) {
        RLEListItem toDelete = item;
        printf("%d\n", toDelete->multiplier);
        item = item->next;
        free(toDelete);
    }
};

RLEList RLEListCreate() {
    RLEList list = (RLEList)malloc(sizeof(*list));
    if (!list) return NULL;
    list->head = NULL;
    list->last = NULL;
    list->size = 0;
    return list;
}

RLEListResult RLEListAppend(RLEList list, char value) {
    if (!list) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if ((list->last) && (list->last->data == value)) {
        list->last->multiplier++;
        list->size++;
        return  RLE_LIST_SUCCESS;
    }
    RLEListItem newItem = (RLEListItem)malloc(sizeof(*newItem));
    if (!newItem) {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    newItem->next = NULL;
    newItem->data = value;
    newItem->multiplier = 1;
    if (list->last == NULL) {
        list->head = newItem;
    }
    else {
        list->last->next = newItem;
    }
    list->last = newItem;
    list->size++;
    return  RLE_LIST_SUCCESS;
}

int main() {
    RLEList list = RLEListCreate();
    RLEListAppend(list, 'C');
    RLEListAppend(list, 'C');
    RLEListAppend(list, 'r');
    RLEListAppend(list, 'r');
    RLEListAppend(list, 'r');
    RLEListAppend(list, 'r');
    RLEListAppend(list, 'b');
    RLEListAppend(list, 'b');
    RLEListAppend(list, 'b');
    RLEListAppend(list, 'b');
    RLEListAppend(list, 'b');
    RLEListAppend(list, 'b');


    RLEListDestroy(list);
}
//implement the functions here
