#ifndef __DSAL_H
#define __DSAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <string.h>

#define dsal_malloc  malloc
#define dsal_free    free
#define dsal_memcpy  memcpy

#ifdef __cplusplus
}
#endif

#endif
