#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <string.h>

#define VEC_T(type) struct {size_t n, m; type *a;}
#define VEC_INIT(v) ((v).n = 0, (v).m = 0, (v).a = 0)
#define VEC_DESTROY(v) free((v).a)
#define VEC_I(v, index) ((v).a[(size_t)(index)])
#define VEC_LEN(v) ((v).n)
#define VEC_MAX(v) ((v).m)
#define VEC_ADD(v, x) ({                                                                 \
    typedef typeof(*(v).a) _ItemType_t;                                                  \
    int _error = 0;                                                                      \
    if ((v).n == (v).m) {                                                                \
        size_t _new_m = (v).m ? (v).m << 1 : 2;                                          \
        _ItemType_t *_temp = (_ItemType_t*)realloc((v).a, sizeof(_ItemType_t) * _new_m); \
        if (_temp == NULL) {                                                             \
            _error++;                                                                    \
        } else {                                                                         \
            (v).a = _temp;                                                               \
            (v).m = _new_m;                                                              \
        }                                                                                \
    }                                                                                    \
    if (_error == 0) {                                                                   \
        (v).a[(v).n++] = (x);                                                            \
    }                                                                                    \
    _error;                                                                              \
})
#define VEC_REMOVE(v, index) ({                         \
    size_t _i = (size_t)(index);                        \
    int _error = 0;                                     \
    if (_i >= (v).n) {                                  \
        _error++;                                       \
    } else {                                            \
        if (_i < (v).n - 1) {                           \
            memmove(&(v).a[_i], &(v).a[_i + 1],         \
                    ((v).n - _i - 1) * sizeof(*(v).a)); \
        }                                               \
        (v).n--;                                        \
    }                                                   \
    _error;                                             \
})
#define VEC_RESERVE(v, new_m) ({                                                         \
    typedef typeof(*(v).a) _ItemType_t;                                                  \
    int _error = 0;                                                                      \
    size_t _req_m = (size_t)(new_m);                                                     \
    if (_req_m > (v).m) {                                                                \
        _ItemType_t *_temp = (_ItemType_t*)realloc((v).a, sizeof(_ItemType_t) * _req_m); \
        if (_temp == NULL) {                                                             \
            _error++;                                                                    \
        } else {                                                                         \
            (v).a = _temp;                                                               \
            (v).m = _req_m;                                                              \
        }                                                                                \
    }                                                                                    \
    _error;                                                                              \
})

#endif /* __VECTOR_H__ */
