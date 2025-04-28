#ifndef __DSAL_LIST_H
#define __DSAL_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "dsal.h"

typedef struct dsal_list_node_t
{
    void *data;
    struct dsal_list_node_t *next;
    struct dsal_list_node_t *last;
} dsal_list_node_t, *dsal_list_node_handle_t;

typedef struct
{
    dsal_list_node_t *head;
    dsal_list_node_t *tail;
    size_t data_size;
    int length;
} dsal_list_t, *dsal_list_handle_t;

dsal_list_handle_t dsal_list_create_list(size_t data_size);
void dsal_list_delete_list(dsal_list_handle_t list);
dsal_list_node_handle_t dsal_list_create_node(size_t data_size);
void dsal_list_delete_node(dsal_list_node_handle_t node);
void dsal_list_insert_at_head(dsal_list_handle_t list, dsal_list_node_handle_t node);
void dsal_list_insert_at_tail(dsal_list_handle_t list, dsal_list_node_handle_t node);
void dsal_list_insert_at_index(dsal_list_handle_t list, int index, dsal_list_node_handle_t node);
void dsal_list_remove_at_head(dsal_list_handle_t list, dsal_list_node_handle_t *removed_node);
void dsal_list_remove_at_tail(dsal_list_handle_t list, dsal_list_node_handle_t *removed_node);
void dsal_list_remove_at_index(dsal_list_handle_t list, int index, dsal_list_node_handle_t *removed_node);
dsal_list_node_handle_t dsal_list_add(dsal_list_handle_t list, int index, void *data);
void dsal_list_delete(dsal_list_handle_t list, int index);
dsal_list_node_handle_t dsal_list_get(dsal_list_handle_t list, int index);
inline void *dsal_list_forward_iterator(dsal_list_node_handle_t start);
inline void *dsal_list_backward_iterator(dsal_list_node_handle_t start);

#ifdef __cplusplus
}
#endif

#endif