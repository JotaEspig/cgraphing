#include <stdlib.h>

#include <cgraphing/pair.h>

#define INITIAL_PAIR_LIST_CAPACITY 10

cg_pair_list_t *cg_new_pair_list()
{
    cg_pair_list_t *l = (cg_pair_list_t *)malloc(sizeof(cg_pair_list_t));
    l->capacity = INITIAL_PAIR_LIST_CAPACITY;
    l->size = 0;
    l->values = (cg_pair_t *)calloc(l->capacity, sizeof(cg_pair_t));
    return l;
}

cg_pair_list_t *cg_pair_list_append(cg_pair_list_t *l, cg_pair_t pair)
{
    if (l->capacity == l->size)
    {
        size_t new_capacity = l->capacity * 2;
        cg_pair_t *new_ptr =
            (cg_pair_t *)realloc(l->values, new_capacity * sizeof(cg_pair_t));
        if (new_ptr == NULL)
            return NULL;
        
        l->capacity = new_capacity;
        l->values = new_ptr;
    }

    l->values[l->size++] = pair;
    return l;
}

void cg_pair_list_destroy(cg_pair_list_t *l)
{
    free(l->values);
    free(l);
}
