#ifndef UTILITIES_H
#define UTILITIES_H

#include <assert.h>
#include <stdio.h>
#include <string.h>

#define ASSERT(condition, msg)                                           \
    if (!(condition))                                                    \
    {                                                                    \
        printf("ASSERT FAILED IN %s:%d: %s\n", __FILE__, __LINE__, msg); \
        assert(condition);                                               \
    }

#endif // UTILITIES_H