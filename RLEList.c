#include "RLEList.h"
#include <stdlib.h>

typedef struct  RLEList_t {
    char data;
    struct RLEList_t * next;
    int multiplier;
    //TODO: implement
} RLEList_t;




void RLEListDestroy(RLEList list) {


};

int main() {
    RLEList list;
    list = (RLEList)malloc(sizeof(RLEList_t));
    list->data = 'c';
    printf("%c", list->data);
    free(list);
    return 0;
}
//implement the functions here
