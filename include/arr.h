#ifndef ARR_H
#define ARR_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>



#ifndef NONNULL
    #define NONNULL __attribute__((nonnull))
#endif



/**
 *  Array modifiers
 */
/// Initialize the array
#define arr_init(a) arr_init_cap(a, sizeof(*(a)), 4)
/// Delete all elements in the array
#define arr_clr(a) (get_array_header(a) = (array_header) { 0 })
/// Free the array
#define arr_free(a) (free(stbds_header(a)), (a) = NULL)

/**
 *  Header operations
 */
/// Returns a pointer to the array header
#define get_array_header(a) ((array_header*)((uint8_t*)(a) - sizeof(array_header)))
/// Returns the number of elements that the array has allocated space for
#define arr_cap(a) (get_array_header(a)->capacity)
/// Returns the length of the array
#define arr_len(a) (get_array_header(a)->length)
/// If the array has a length of 0
#define arr_empty(a) (arr_len(a) == 0)

/**
 *  Length and capacity modifiers
 */
/// Grow the array for the given number of elements if needed
#define array_maybe_grow(a, n) ((arr_len(a) + n > arr_cap(a)) ? ((a) = array_grow(a, sizeof(*(a)), n)),0 : (get_array_header(a)->length += n))
/// Sets the capacity of the array, returns a new pointer on success
#define arr_setcap(a, c) (array_set_capacity((a), sizeof(*(a)), c))
#define arr_reserve_exact(a, c) arr_setcap(a, c)
/// Increase the length of the array without initializing the new elements
#define arr_setlen(a, l) (array_maybe_grow((a), sizeof(*(a)), l))

/**
 *  Element modifiers and accessors
 */
/// Safe accessor with bounds checking
#define arr_at(a, i) ((i < arr_len(a)) ? a[i] : 0)
/// Insert an element in the array at the given element
#define arr_ins(a, i, e) ( \
    array_maybe_grow(a, 1), \
    memmove(&(a)[i + 1], &(a)[i], (arr_len(a) - (i) - 1) * sizeof(*(a))), \
    (a)[i] = (e) \
)
/// Push the given element to the back, will reallocate if necessary
#define arr_push(a, e) (array_maybe_grow(a, 1), (a)[arr_len(a)-1] = (e))
/// Removes the last element and returns it
#define arr_pop(a) ( \
    get_array_header(a)->length--, \
    (a)[arr_len(a)] \
)
/// Delete the element at the given index
#define arr_del(a, i) arr_delr(a, i, 1)
/// Delete n number of elements starting at index i
#define arr_delr(a, i, n) ( \
    memmove(&(a)[i], &(a)[(i)+(n)], sizeof(*(a)) * (arr_len(a) - (i) - (n))), \
    get_array_header(a)->length -= (n) \
)
/// Delete the given element and swap it with the last
#define arr_dels(a, i) (a[i] = a[arr_len(a) - 1], arr_pop(a))



typedef struct {
    size_t capacity;
    size_t length;
} array_header;


/// Inititalize the array with the given capacity
void* arr_init_cap(void* arr, size_t element_size, size_t capacity) NONNULL;

/// Increase the array's length by the given amount
void* array_grow(void* arr, size_t element_size, size_t add_length) NONNULL;

/// Set the array's capacity, `arr` will be invalidated upon successful reallocation
void* array_set_capacity(void* arr, size_t element_size, size_t capacity) NONNULL;

#endif
