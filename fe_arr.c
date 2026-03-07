#include "fe_arr.h"

#include <stdio.h>
#include <stdlib.h>

// TYPE_CHAR,
// TYPE_INT,
// TYPE_FLOAT,
// TYPE_DOUBLE,
// TYPE_LONG,
// TYPE_LONG_LONG,

#define bate 1.5

typedef struct FU_ARR{
    void** value;
    size_t size;
    size_t used; //已储存元素数
}FU_ARR;

FU_ARR *fuarr_creat_arr(size_t s) {
// FU_ARR* fuarr_creat_arr(size_t s, size_t type_size);
    FU_ARR* arr = malloc(sizeof(FU_ARR));
    if(arr==NULL) return NULL;
    arr->value = calloc(s , sizeof(void*));
    if(arr->value==NULL) { free(arr); return NULL; }
    // arr->type_s = type_size;
    arr->size = s;
    arr->used = 0;
    return arr;
}

void *fuarr_get(FU_ARR *arr, ArrInt index) {
    if( (index>=arr->used)||(arr==NULL)  ) {
        return NULL;
    }
    return arr->value[index];
}

int fuarr_put(FU_ARR *arr, void* v) {
    if(arr==NULL) return -1;
    if(arr->used>=arr->size) {
        void** temp = realloc(arr->value,(arr->size*bate) * sizeof(void*));
        if(temp==NULL) {
            return -1;
        }
        arr->value = temp;
        arr->size *= bate;
    }
    arr->value[arr->used] = v;
    arr->used++;
    return 0;
}

int fuarr_set(FU_ARR *arr, ArrInt index, void* v) {
    if(arr==NULL) return -1;
    if(index >= arr->used) return -1;
    if(arr->used>=arr->size) {
        void** temp = realloc(arr->value,(arr->size*bate) * sizeof(void*));
        if(temp==NULL) {
            return -1;
        }
        arr->value = temp;
        arr->size = arr->size* 2;
    }
    if(index>=arr->used) {
        arr->used++;
    }
    arr->value[index] = v;
    return 0;
}

void *fuarr_pop(FU_ARR *arr) {
    if(arr==NULL) return NULL;
    arr->used--;
    void *temp = arr->value[arr->used];
    arr->value[arr->used]=NULL;
    return temp;
}

void *fuarr_del(FU_ARR *arr, ArrInt index) {
    if(arr==NULL) return NULL;
    void *temp;
    arr->used--;
    if(index==(arr->used + 1)) {
        temp = arr->value[arr->used];
        arr->value[arr->used]=NULL;
        return temp;
    }
    temp = arr->value[index];
    for(ArrInt i=index; i<arr->used + 1; i++) {
        arr->value[i] = arr->value[i+1];
        if(i==arr->used) {
            arr->value[i]=NULL;
        }
    }
    return temp;
}

ArrInt fuarr_len(FU_ARR *arr) {
    if(arr==NULL) return -1;
    return arr->used;
}

ArrInt fuarr_size(FU_ARR *arr) {
    if(arr==NULL) return -1;
    return arr->size;
}

void fuarr_free_container(FU_ARR *arr) {
    if(arr==NULL) return;
    if(arr->value==NULL) { free(arr); return; }
    free(arr->value);
    free(arr);
}

void fuarr_free_all(FU_ARR *arr) {
    if(arr==NULL) return;
    if(arr->value==NULL) { free(arr); return; }
    for(ArrInt i=0;i<arr->used;i++) {
        free(arr->value[i]);
    }
    free(arr->value);
    free(arr);
}
