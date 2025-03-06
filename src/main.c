#include <stdio.h>

#include "arr.h"



int main(int argc, char** argv) {
    int* int_arr = NULL;
    int_arr = arr_init(int_arr, sizeof(int));

    printf(
        "Length: %d\nCapacity: %d\n",
        array_length(int_arr),
        array_capacity(int_arr)
    );

    return 0;
}
