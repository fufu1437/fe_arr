#ifndef FU_arr__fu_arr__fufu1437_h
#define FU_arr__fu_arr__fufu1437_h

/*
 * 这是一个极其简单的动态列表
 * 列表内部储存的是指针，而非值
 * 支持泛型，需要调用者自行处理类型
 * API与Python类似
*/

#include <stdio.h>

// 可自行修改ArrInt的类型，以适应不同环境的需求
typedef long ArrInt;

typedef struct FU_ARR FU_ARR;

FU_ARR* fuarr_creat_arr(size_t s);
// FU_ARR* fuarr_creat_arr(size_t s, size_t type_size);

// 获取 index 处的指针，超出数组长度返回NULL
void *fuarr_get(FU_ARR *arr, ArrInt index);

// 向数组追加一个指针
int fuarr_put(FU_ARR *arr, void *v);

// 设置 index 处的指针
// 只允许对现有数据进行修改
// 如超出数组长度，或 arr 是空指针返回NULL
int fuarr_set(FU_ARR *arr, ArrInt index, void *v);

// 返回数组长度
ArrInt fuarr_len(FU_ARR *arr);

// 返回数组大小
ArrInt fuarr_size(FU_ARR *arr);

// 弹出数组末尾的指针，并返回它，如果数组长度为0，或arr为空指针，则返回NULL
void *fuarr_pop(FU_ARR *arr);

// 删除 index 处的指针，超出数组长度，或 arr 是空指针返回NULL
void *fuarr_del(FU_ARR *arr, ArrInt index);

// 删除arr这个数组容器，其内部指针如果使用malloc分配，则需自行释放
void fuarr_free_container(FU_ARR *arr);

// 删除arr这个容器，和数组的指针，仅适用于所有值均为malloc/relloc/calloc分配的内存的数组
void fuarr_free_all(FU_ARR *arr);

#endif
