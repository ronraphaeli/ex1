#include "RLEList.h"
#include <stdlib.h>
#define HEAD 0

typedef struct  RLEListItem_t {
    char data;
    struct RLEListItem_t* next;
    int counter;
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
        //printf("%d\n", toDelete->counter);
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
        list->last->counter++;
        list->size++;
        return  RLE_LIST_SUCCESS;
    }
    RLEListItem newItem = (RLEListItem)malloc(sizeof(*newItem));
    if (!newItem) {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    newItem->next = NULL;
    newItem->data = value;
    newItem->counter = 1;
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

int RLEListSize(RLEList list) {
    if (list == NULL)
        return -1;
    int count = 0;
    RLEListItem item = list->head;
    while (item) {
        count= count + item->counter;
        item = item->next;
    }
    return count;
};

RLEListResult RLEListRemove(RLEList list, int index) {
    if (list == NULL)
        return RLE_LIST_NULL_ARGUMENT;
    int count = 0;
    bool foundToDelete = false;
    RLEListItem nodeToDelete = NULL;
    RLEListItem previousNode = list->head;
    RLEListItem item = list->head;
    while (item) {
        for (int i = 0; i < item->counter; i++) {
            if (index == count) {
                nodeToDelete = item;
                foundToDelete = true;
                break;
            }
            count++;
        }
        if (nodeToDelete) {
            previousNode = item;
            break;
        }
        item = item->next;
    }
    if (!foundToDelete && index >= count || index < 0) {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    if ((nodeToDelete->counter)>1)
    {
        nodeToDelete->counter = nodeToDelete->counter - 1;
        return RLE_LIST_SUCCESS;
    }
    previousNode->next = nodeToDelete->next;
    free(nodeToDelete);
    return RLE_LIST_SUCCESS;
}

char RLEListGet(RLEList list, int index, RLEListResult* result) {
    if (!list) {
        if (result) {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }
    int count = 0;
    RLEListItem nodeToRead = NULL;
    RLEListItem item = list->head;
    while (item) {
        for (int i = 0; i < item->counter; i++) {
            if (index == count) {
                nodeToRead = item;
                break;
            }
            count++;
        }
        if (nodeToRead) {
            if (result)
            {
                *result = RLE_LIST_SUCCESS;
            }
            return nodeToRead->data;
        }
        item = item->next;
    }
    if (index >= count || index < 0) {
        if (result)
        {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return 0;
    }
    return 0;
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
    printf("%d\n", RLEListSize(list));
    printf("%c\n", RLEListGet(list,5, NULL));
    RLEListRemove(list,5);
    printf("%d\n", RLEListSize(list));
    printf("%c\n", RLEListGet(list, 5, NULL));

    RLEListDestroy(list);
}
//implement the functions here
