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

/* data to store all the students*/
student **class;
int N;
int M;


/**
 * @brief funtion that verifies the input
 * and creates the graph
 * Time: O(N) or O(M); Space: O(N^2)
 * 
 * @return int 
 */
int parse_create(void) {
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
        
        /* check grade*/
        if (scanf("%d", &class[line_count]->grade) != 1) {
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
        st1--;
        st2--;
        class[st1]->friends[class[st1]->head++] = st2;
    }
    
    return SUCCESS;
}


#ifdef DEBUG
void print_graph(void) {
    int si;
    int fi;
    printf("1\n");
    for (si = 0; si < N; si++) {
        printf("Student %d (grade = %d): ", si+1, class[si]->grade);
        for (fi = 0; fi < class[si]->head; fi++) {
            printf("%d ", class[si]->friends[fi]+1);
        }
        printf("\n");
    }
}
#endif


/**
 * @brief function to calculate the grades of the class
 * 
 */
void calculate_grades(void) {
    
}
