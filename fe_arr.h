#ifndef fe_arr_header_h
#define fe_arr_header_h

/* 
 *  修改该宏，以调整数据大小
*/
#define ArrInt int

/* 
 * 严禁在非初始化时操作列表，这将会产生不可控的结果
*/
typedef struct FE_ARR{
    void** value;
    size_t size;
    size_t used; //已储存元素数
}FE_ARR;

#ifndef FEARR_IMPLEMENTATION

extern FE_ARR *fearr_creat_arr(size_t size);

// 获取 index 处的指针，超出数组长度返回NULL
extern void *fearr_get(FE_ARR *arr, ArrInt index);

// 向数组追加一个指针
extern int fearr_put(FE_ARR *arr, void *v);

// 设置 index 处的指针
// 只允许对现有数据进行修改
// 如超出数组长度，或 arr 是空指针返回NULL
extern int fearr_set(FE_ARR *arr, ArrInt index, void *v);

// 返回数组长度
ArrInt fearr_len(FE_ARR *arr);

// 返回数组大小
ArrInt fearr_size(FE_ARR *arr);

// 弹出数组末尾的指针，并返回它，如果数组长度为0，或arr为空指针，则返回NULL
extern void *fearr_pop(FE_ARR *arr);

// 删除 index 处的指针，超出数组长度，或 arr 是空指针返回NULL
extern void *fearr_del(FE_ARR *arr, ArrInt index);

// 删除arr这个数组容器，其内部指针如果使用malloc分配，则需自行释放
extern void fearr_free_container(FE_ARR *arr);

// 删除arr这个容器，和数组的指针，仅适用于所有值均为malloc/relloc/calloc分配的内存的数组
extern void fearr_free_all(FE_ARR *arr);

#endif


#ifdef FEARR_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>

// 扩容系数
#define bate 1.5

FE_ARR *fearr_creat_arr(size_t size) {
    return malloc(sizeof(void*) * size);
}

void *fearr_get(FE_ARR *arr, ArrInt index) {
    if( (index>=arr->used)||(arr==NULL)  ) {
        return NULL;
    }
    return arr->value[index];
}

int fearr_put(FE_ARR *arr, void* v) {
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

int fearr_set(FE_ARR *arr, ArrInt index, void* v) {
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

void *fearr_pop(FE_ARR *arr) {
    if(arr==NULL) return NULL;
    arr->used--;
    void *temp = arr->value[arr->used];
    arr->value[arr->used]=NULL;
    return temp;
}

void *fearr_del(FE_ARR *arr, ArrInt index) {
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

ArrInt fearr_len(FE_ARR *arr) {
    if(arr==NULL) return -1;
    return arr->used;
}

ArrInt fearr_size(FE_ARR *arr) {
    if(arr==NULL) return -1;
    return arr->size;
}

void fearr_free_container(FE_ARR *arr) {
    if(arr==NULL) return;
    if(arr->value==NULL) { free(arr); return; }
    free(arr->value);
    free(arr);
}

void fearr_free_all(FE_ARR *arr) {
    if(arr==NULL) return;
    if(arr->value==NULL) { free(arr); return; }
    for(ArrInt i=0;i<arr->used;i++) {
        free(arr->value[i]);
    }
    free(arr->value);
    free(arr);
}

#endif
#endif
