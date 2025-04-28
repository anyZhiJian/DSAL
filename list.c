#include "list.h"

dsal_list_handle_t dsal_list_create_list(size_t data_size)
{
    dsal_list_handle_t list = (dsal_list_handle_t)dsal_malloc(sizeof(dsal_list_t));
    if (list)
    {
        list->head = NULL;
        list->tail = NULL;
        list->data_size = data_size;
        list->length = 0;
        return list;
    }
    return NULL;
}

void dsal_list_delete_list(dsal_list_handle_t list)
{
    if (!list) return;
    dsal_list_node_handle_t temp = list->head;
    while (list->head)
    {
        list->head = temp->next;
        dsal_list_delete_node(temp);
    }
    dsal_free(list);
}

dsal_list_node_handle_t dsal_list_create_node(size_t data_size)
{
    dsal_list_node_handle_t node = (dsal_list_node_handle_t)dsal_malloc(sizeof(dsal_list_node_t));
    if (node)
    {
        node->data = dsal_malloc(data_size);
        if (node->data)
        {
            node->next = NULL;
            node->last = NULL;
            return node;
        }
        else
            dsal_free(node);
    }
    return NULL;
}

void dsal_list_delete_node(dsal_list_node_handle_t node)
{
    if (!node) return;
    dsal_free(node->data);
    dsal_free(node);
}

void dsal_list_insert_at_head(dsal_list_handle_t list, dsal_list_node_handle_t node)
{
    if (!list || !node) return;
    dsal_list_node_handle_t head = list->head;
    node->next = head;
    node->last = NULL;
    if (head)
        head->last = node;
    else
        list->tail = node;
    list->head = node;
    ++list->length;
}

void dsal_list_insert_at_tail(dsal_list_handle_t list, dsal_list_node_handle_t node)
{
    if (!list || !node) return;
    dsal_list_node_handle_t tail = list->tail;
    node->next = NULL;
    node->last = tail;
    if (tail)
        tail->next = node;
    else
        list->head = node;
    list->tail = node;
    ++list->length;
}

void dsal_list_insert_at_index(dsal_list_handle_t list, int index, dsal_list_node_handle_t node)
{
    if (!list || !node) return;
    if (index == 0 || index < -list->length)
        dsal_list_insert_at_head(list, node);
    else if (index == -1 || index >= list->length)
        dsal_list_insert_at_tail(list, node);
    else
    {
        int i;
        dsal_list_node_handle_t temp;
        if (index < 0) index = list->length + index + 1;
        if (index <= list->length / 2)
        {
            temp = list->head;
            for (i = 0; i < index - 1; ++i)
                temp = temp->next;
        }
        else
        {
            temp = list->tail;
            for (i = 0; i < list->length - index; ++i)
                temp = temp->last;
        }
        node->last = temp;
        node->next = temp->next;
        node->next->last = node;
        temp->next = node;
        ++list->length;
    }
}

void dsal_list_remove_at_head(dsal_list_handle_t list, dsal_list_node_handle_t* removed_node)
{
    if (!list) return;
    dsal_list_node_handle_t temp = list->head;
    if (temp)
    {
        list->head = temp->next;
        if (!temp->next)
            list->tail = NULL;
        temp->last = NULL;
        temp->next = NULL;
        --list->length;
    }
    if (removed_node)
        *removed_node = temp;
    else if (temp)
        dsal_list_delete_node(temp);
}

void dsal_list_remove_at_tail(dsal_list_handle_t list, dsal_list_node_handle_t* removed_node)
{
    if (!list) return;
    dsal_list_node_handle_t temp = list->tail;
    if (temp)
    {
        list->tail = temp->last;
        if (!temp->last)
            list->head = NULL;
        temp->last = NULL;
        temp->next = NULL;
        --list->length;
    }
    if (removed_node)
        *removed_node = temp;
    else if (temp)
        dsal_list_delete_node(temp);
}

void dsal_list_remove_at_index(dsal_list_handle_t list, int index, dsal_list_node_handle_t* removed_node)
{
    if (!list) return;
    if (index == 0 || index <= -list->length)
        dsal_list_remove_at_head(list, removed_node);
    else if (index == -1 || index >= list->length - 1)
        dsal_list_remove_at_tail(list, removed_node);
    else
    {
        int i;
        dsal_list_node_handle_t temp;
        if (index < 0) index = list->length + index;
        if (index < list->length / 2)
        {
            temp = list->head->next;
            for (i = 1; i < index; ++i)
                temp = temp->next;
        }
        else
        {
            temp = list->tail->last;
            for (i = 1; i < (list->length - 1) - index; ++i)
                temp = temp->last;
        }
        temp->next->last = temp->last;
        temp->last->next = temp->next;
        temp->next = NULL;
        temp->last = NULL;
        if (removed_node)
            *removed_node = temp;
        else
            dsal_list_delete_node(temp);
        --list->length;
    }
}

dsal_list_node_handle_t dsal_list_add(dsal_list_handle_t list, int index, void* data)
{
    if (!list) return NULL;
    dsal_list_node_handle_t node = dsal_list_create_node(list->data_size);
    if (node)
    {
        if (data)
            dsal_memcpy(node->data, data, list->data_size);
        dsal_list_insert_at_index(list, index, node);
        return node;
    }
    return NULL;
}

void dsal_list_delete(dsal_list_handle_t list, int index)
{
    if (!list) return;
    dsal_list_remove_at_index(list, index, NULL);
}

dsal_list_node_handle_t dsal_list_get(dsal_list_handle_t list, int index)
{
    if (!list) return NULL;
    if (index == 0 || index <= -list->length)
        return list->head->data;
    else if (index == -1 || index >= list->length - 1)
        return list->tail->data;
    else
    {
        int i;
        dsal_list_node_handle_t temp;
        if (index < 0) index = list->length + index;
        if (index < list->length / 2)
        {
            temp = list->head->next;
            for (i = 1; i < index; ++i)
                temp = temp->next;
        }
        else
        {
            temp = list->tail->last;
            for (i = 1; i < (list->length - 1) - index; ++i)
                temp = temp->last;
        }
        return temp;
    }
}

inline void *dsal_list_forward_iterator(dsal_list_node_handle_t start)
{
    void *data = start->data;
    start = start->next;
    return data;
}

inline void *dsal_list_backward_iterator(dsal_list_node_handle_t start)
{
    void *data = start->data;
    start = start->last;
    return data;
}