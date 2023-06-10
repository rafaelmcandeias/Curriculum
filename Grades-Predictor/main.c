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

int vertices;
int edges;

int main(int argc, char const *argv[]) {
    if (argc != 0 || argv != NULL) {
        return EXIT_FAILURE;
    }

    /* check if input is correct and creates a graph with the info read*/
    if (parse_create()) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
