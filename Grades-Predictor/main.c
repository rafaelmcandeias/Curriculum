/**
 * @file main.c
 * @author Rafael Candeias
 * @brief 
 * @version 0.1
 * @date 2023-06-10
 * 
 * @copyright Copyright (c) 2023
 * 
 * File with the main function
 */

#include "lib.h"


int main(void) {

    /* check if input is correct and creates a graph with the info read*/
    if (parse_create()) {
        return EXIT_FAILURE;
    }

    #ifdef DEBUG
    print_graph();
    #endif

    calculate_grades();

    return EXIT_SUCCESS;
}
