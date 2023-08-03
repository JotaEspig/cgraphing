#ifndef PAIR_H
#define PAIR_H

#include <stddef.h>

typedef struct cg_pair_t
{
    float x;
    float y;
} cg_pair_t;

typedef struct cg_pair_list_t
{
    cg_pair_t *values;
    size_t size;
    size_t capacity;
} cg_pair_list_t;

cg_pair_list_t *cg_new_pair_list();
cg_pair_list_t *cg_pair_list_append(cg_pair_list_t *l, cg_pair_t pair);
void cg_pair_list_destroy(cg_pair_list_t *l);

#endif // PAIR_H
