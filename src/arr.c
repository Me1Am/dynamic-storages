#include <stdlib.h>

#include "arr.h"

size_t maxs(size_t a, size_t b) { return (a > b) ? a : b; }

/// Calls arr_init_length with a length of 1
void* arr_init(void* arr, size_t element_size) {
    return arr_init_length(arr, element_size, 1);
}

/// Inititalize the array with the given length
void* arr_init_length(void* arr, size_t element_size, size_t length) {
    arr = malloc(sizeof(array_header) + (element_size * length));

    if(arr == NULL)
        return NULL;

    void* arr_ptr = ((uint8_t*)arr) + sizeof(array_header);

    *(array_header*)arr = (array_header) {
        .length = 0,
        .capacity = length,
    };

    return arr_ptr;
}

void* array_set_capacity(void* arr, size_t element_size, size_t capacity) {
    if(capacity < array_capacity(arr))
        return arr;

    // Attempt to grow exponentially, else set absolute capacity
    const size_t new_capacity = maxs(array_capacity(arr) * 2, capacity);
    void* temp = realloc(get_array_header(arr), sizeof(array_header) + (element_size * new_capacity));
    temp = ((uint8_t*)temp) + sizeof(array_header);

    if(temp == NULL)
        return NULL;

    // Success, update capacity
    get_array_header(temp)->capacity = new_capacity;

    return arr;
}

/// Calls array_set_capacity if add_length + array_length is greater than the capacity
void* array_grow(void* arr, size_t element_size, size_t add_length) {
    const size_t minimum_length = array_length(arr) + add_length; // Desired length

    // Don't need to realloc
    if(minimum_length <= array_capacity(arr))
        return arr;

    // Success, update length
    void* temp array_set_capacity(arr, element_size, minimum_length);
    get_array_header(temp)->length += add_length;

    return temp;
}
