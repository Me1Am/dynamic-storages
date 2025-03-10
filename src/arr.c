#include <stdlib.h>

#include "arr.h"



/// Inititalize the array with the given capacity
void* arr_init_cap(void* arr, size_t element_size, size_t capacity) {
    arr = malloc(sizeof(array_header) + (element_size * capacity));

    if(arr == NULL)
        return NULL;

    void* arr_ptr = ((uint8_t*)arr) + sizeof(array_header);

    *(array_header*)arr = (array_header) {
        .length = 0,
        .capacity = capacity,
    };

    return arr_ptr;
}

/// Realloc exactly enough memory for `capacity`
/// The array pointer will be invalidated on success, just like realloc
void* array_set_capacity(void* arr, size_t element_size, size_t capacity) {
    if(capacity < arr_cap(arr))
        return arr;

    // Attempt to grow exponentially, else set absolute capacity
    void* temp = realloc(get_array_header(arr), sizeof(array_header) + (element_size * capacity));
    temp = ((uint8_t*)temp) + sizeof(array_header);

    if(temp == NULL)
        return NULL;

    // Success, update capacity
    get_array_header(temp)->capacity = capacity;

    return temp;
}

/// Calls array_set_capacity if `add_length` + array_length is greater than the capacity
///  Does nothing if minimum length is less than the capacity
///  Uninitialized slots will remain uninitialized
void* array_grow(void* arr, size_t element_size, size_t add_length) {
    size_t minimum_length = arr_len(arr) + add_length; // Desired length

    // Don't need to realloc
    if(minimum_length <= arr_cap(arr)) {
        get_array_header(arr)->length += add_length;
        return arr;
    }

    // Will attempt to use exponential growth
    if(minimum_length < arr_cap(arr) * 2)
        minimum_length = arr_cap(arr) * 2;

    void* temp = array_set_capacity(arr, element_size, minimum_length);
    get_array_header(temp)->length += add_length;

    return temp;
}
