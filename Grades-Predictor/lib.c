/**
 * @file lib.c
 * @author Rafael Candeias
 * @brief
 * @version 0.1
 * @date 2023-06-10
 *
 * @copyright Copyright (c) 2023
 * File with all auxiliarity function's implementations
 */

#include "lib.h"

student **class;

int parse_create() {
    int N;
    int M;
    int line_count;
    int st1;
    int st2;

    /* get the first two values */
    if (scanf("%d, %d", &N, &M) != 2 || N <= 0 || M <= 0) {
        printf("First two values are incorrect\n");
        return FAILURE;
    }

    /* mem for all students*/
    class = malloc(sizeof(student*) * N);

    /* original grades for all*/
    for (line_count = 0; line_count < N; line_count++) {
        /* create object*/
        class[line_count] = malloc(sizeof(student));
        class[line_count]->head = 0;
        class[line_count]->friends = malloc(sizeof(int) * N);
        /* check if grade is correct*/
        if (scanf("%d", &class[line_count]->grade) != 1 || class[line_count]->grade < 0) {
            printf("Grade for line %d is incorrect\n", line_count);
            return FAILURE;
        }
    }

    /* take care of friendships*/
    for (line_count = 0; line_count < M; line_count++) {
        /* check if connection is correct*/
        if (scanf("%d %d", &st1, &st2) != 2 || st1 < 0 || st2 < 0 || st1 > N || st2 > N) {
            printf("Connection in line %d is incorrect\n", line_count);
            return FAILURE;
        }
        class[st1]->friends[class[st1]->head++] = st2;
    }
    
    return SUCCESS;
}
