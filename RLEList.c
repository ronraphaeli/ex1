#include "RLEList.h"
#include <stdlib.h>
#define HEAD 0
#include "tests/test_utilities.h"
#pragma warning(disable:4996)



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
    return list->size;
};

void mergeAdjacentNodesWithSameChar(RLEList list, RLEListItem node) {
    RLEListItem nextNode = node->next;
    while ((nextNode) && (node->data == nextNode->data))
    {
        node->counter = node->counter + nextNode->counter;
        node->next = nextNode->next;
        free(nextNode);
        nextNode = node->next;
        list->size--;
    }
    return;
}

RLEListResult RLEListRemove(RLEList list, int index) {
    if (list == NULL)
        return RLE_LIST_NULL_ARGUMENT;
    int count = 0;
    //bool foundToDelete = false;
    RLEListItem nodeToDelete = NULL;
    RLEListItem previousNode = list->head;
    RLEListItem item = list->head;
    while (item) {
        for (int i = 0; i < item->counter; i++) {
            if (index == count) {
                nodeToDelete = item;
                //foundToDelete = true;  //we are looking for the node that the index to delete is in
                break;
            }
            count++;
        }
        if (nodeToDelete) {
            break;
        }
        previousNode = item;
        item = item->next;
    }
    if (!nodeToDelete && (index >= count || index < 0)) {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    if (nodeToDelete && (nodeToDelete->counter)>1){
        list->size--;
        nodeToDelete->counter--;
        return RLE_LIST_SUCCESS;
    }
    if (nodeToDelete && (nodeToDelete==(list->head))){
        list->head = nodeToDelete->next;
    }
    if (nodeToDelete && (nodeToDelete == (list->last))){
        list->last = previousNode;
    }
    previousNode->next = nodeToDelete->next;
    list->size--;
    free(nodeToDelete);
    mergeAdjacentNodesWithSameChar(list,previousNode);
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

int getNumberOfNodes(RLEList list) {
    int counter = 0;
    RLEListItem node = list->head;
    while (node) {
        counter++;
        node = node->next;
    }
    return counter;
}

char* RLEListExportToString(RLEList list, RLEListResult* result) {
    if (!list) {
        if (result) {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    int numberOfNodes = getNumberOfNodes(list);
    char* exportedString = (char*)malloc(3*sizeof(char)*numberOfNodes + sizeof(char));
    RLEListItem node = list->head;
    int i;
    for (i = 0; node;) {
        exportedString[i] = node->data;
        i++;
        exportedString[i] = (char)('0' + node->counter);
        i++;
        exportedString[i] = '\n'; //0x0A is the ascii for \n
        i++;
        node = node->next;
    }
    i++;
    exportedString[i] = 0;
    if (result) {
        *result = RLE_LIST_SUCCESS;
    }
    return exportedString;
}

int main() {
    FILE* fp;
    int c;

    fp = fopen("C:\\Users\\LG\\OneDrive - Tel-Aviv University\\Documents\\technion\\A\\mtm\\hw1\\3.1\\hello.txt", "r");
    RLEList list = asciiArtRead(fp);
    printf("%s", RLEListExportToString(list, NULL));
    RLEListDestroy(list);
}
//implement the functions here
