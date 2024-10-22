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
    /* variable to keep track of last index with friend */
    int last_friend_index;
    /* variable to know that student has been visited by dfs */
    int flag_visited;
} student;

/* Functions */
int parse_create(void);
#ifdef DEBUG
void print_graph(void);
#endif
int highest_grade(student* s);
void calculate_grades(void);
void final_result(void);
