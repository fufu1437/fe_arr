#ifndef FE_arr__fe_arr__fefe1437_h
#define FE_arr__fe_arr__fefe1437_h

/*
 * 这是一个极其简单的动态列表
 * 列表内部储存的是指针，而非值
 * 支持泛型，需要调用者自行处理类型
 * API与Python类似
*/

#include <stdio.h>

// 可自行修改ArrInt的类型，以适应不同环境的需求
typedef long ArrInt;

typedef struct FE_ARR FE_ARR;

FE_ARR* fearr_creat_arr(size_t s);
// FE_ARR* fearr_creat_arr(size_t s, size_t type_size);

// 获取 index 处的指针，超出数组长度返回NULL
void *fearr_get(FE_ARR *arr, ArrInt index);

// 向数组追加一个指针
int fearr_put(FE_ARR *arr, void *v);

// 设置 index 处的指针
// 只允许对现有数据进行修改
// 如超出数组长度，或 arr 是空指针返回NULL
int fearr_set(FE_ARR *arr, ArrInt index, void *v);

// 返回数组长度
ArrInt fearr_len(FE_ARR *arr);

// 返回数组大小
ArrInt fearr_size(FE_ARR *arr);

// 弹出数组末尾的指针，并返回它，如果数组长度为0，或arr为空指针，则返回NULL
void *fearr_pop(FE_ARR *arr);

// 删除 index 处的指针，超出数组长度，或 arr 是空指针返回NULL
void *fearr_del(FE_ARR *arr, ArrInt index);

// 删除arr这个数组容器，其内部指针如果使用malloc分配，则需自行释放
void fearr_free_container(FE_ARR *arr);

// 删除arr这个容器，和数组的指针，仅适用于所有值均为malloc/relloc/calloc分配的内存的数组
void fearr_free_all(FE_ARR *arr);

#endif
