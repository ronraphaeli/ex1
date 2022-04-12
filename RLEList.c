#include "RLEList.h"
#include <stdlib.h>


struct  RLEList_t {
    char data;
    struct RLEList_t * next;
    int multiplier;
};

void RLEListDestroy(RLEList list) {
    while (list) {
        RLEList toDelete = list;
        printf("%c", list->data);
        list = list->next;
        free(toDelete);
    }
};

RLEList RLEListCreate() {
    RLEList list = malloc(sizeof(*list));
    if (!list) return NULL;
    list->next = NULL;
    return list;
}

int main() {
    RLEList list1 = RLEListCreate(), list2 = RLEListCreate();
    list1->data = 'a';
    list2->data = 'b';
    list1->next = list2;
    RLEListDestroy(list1);
}
//implement the functions here
