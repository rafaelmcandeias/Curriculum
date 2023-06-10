/**
 * @file lib.h
 * @author Rafael Candeias
 * @brief 
 * @version 0.1
 * @date 2023-06-10
 * 
 * @copyright Copyright (c) 2023
 * File with all auxiliarity function names, data types and macros
 */

#include <stdio.h>
#include <stdlib.h>

/* Macros */
#define SUCCESS 0;
#define FAILURE 1;

/* Data types */
typedef struct students {
    int grade;
    /* keeps all ids of student friends*/
    int *friends;
    /* size of friends vector*/
    int head; 
} student;

/* Functions */
int parse_create(void);
#ifdef DEBUG
void print_graph(void);
#endif
void calculate_grades(void);
