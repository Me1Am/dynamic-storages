#ifndef ARR_H
#define ARR_H

#include <stdint.h>
#include <stddef.h>



#ifndef NONNULL
    #define NONNULL __attribute__((nonnull))
#endif


/// Returns a pointer to the array header
#define get_array_header(a) ((array_header*)((uint8_t*)(a) - sizeof(array_header)))
/// Returns the length of the array
#define array_length(a) ((a) ? get_array_header(a)->length : 0)
/// Returns the total allocated space of the array
#define array_capacity(a) ((a) ? get_array_header(a)->capacity : 0)


/// Grow the array for the given number of elements if needed
#define array_maybe_grow(a, n)  ((array_length(a) + n > array_capacity(a)) ? array_grow(a, sizeof(*(a)) : 0)
/// Push the given element to the back
#define array_push(a, v) (array_maybe_grow(a, 1), (a)[get_array_header(a)->length++] = (v))

// Aliases
#define arr_setcap(a, c) (array_set_capacity((a), sizeof(*(a)), c))
#define arr_setlen(a, l) (array_grow((a), sizeof(*(a)), c))

typedef struct {
    size_t capacity;
    size_t length;
} array_header;



/// Inititalize the array
void* arr_init(void* arr, size_t element_size) NONNULL;

/// Inititalize the array with the given length
void* arr_init_length(void* arr, size_t element_size, size_t length) NONNULL;

/// Push an element to the back of the element
void arr_push(void* arr, void* element);

/// Increase the array's length by the given amount
/// Consider using the macro array_set_len
void* array_grow(void* arr, size_t element_size, size_t add_length) NONNULL;

/// Set the array's capacity
void* array_set_capacity(void* arr, size_t element_size, size_t capacity) NONNULL;

#endif
