#ifndef _HASHUTILS_H
#define _HASHUTILS_H

#include <tr1/functional>

struct stringHash : public std::unary_function<const char*, size_t>
{
    size_t operator()(const char* str) const
    { 
        size_t hash = 0;
        while (*str != '\0')
            hash += hash * 42 + *str++;
        return hash;
    }
};

#endif  /* _HASHUTILS_H */

