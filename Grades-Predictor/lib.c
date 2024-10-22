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
 * Time: O(max(N, M))
 * Space: O(N^2)
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
        /* We assume each student will have at most half the clas as friends */
        class[line_count]->friends = malloc(sizeof(int) * N/2);
        class[line_count]->last_friend_index = -1;
        class[line_count]->flag_visited = 0;

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
        class[st1]->last_friend_index++;
        class[st1]->friends[class[st1]->last_friend_index] = st2;
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
        for (fi = 0; fi <= class[si]->last_friend_index; fi++) {
            printf("%d ", class[si]->friends[fi]+1);
        }
        printf("\n");
    }
}
#endif


int highest_grade(student* s) {
    int i, friends_grade;

    if (s->flag_visited == 1) {
        return s->grade;
    }

    s->flag_visited = 1;
    for (i = 0; i <= s->last_friend_index; i++) {
        friends_grade = highest_grade(class[s->friends[i]]);
        s->grade = s->grade > friends_grade ? s->grade : friends_grade;
    }

    return s->grade;
}


/**
 * @brief function to calculate the grades of the class
 * We apply the DFS algortihm per student.
 * Time: O((E+V)*N)
 * Space: O(N)
 */
void calculate_grades(void) {
    int sp, i, friends_grade;
    
    for (sp = 0; sp < N; sp++) {
        /* mark student as visited */
        class[sp]->flag_visited = 1;

        for (i = 0; i <= class[sp]->last_friend_index; i++) {
            friends_grade = highest_grade(class[class[sp]->friends[i]]);
            class[sp]->grade = class[sp]->grade > friends_grade ? class[sp]->grade : friends_grade;
        }
    }
}

/**
 * @brief Function that prints the predicted grade per student
 * Time: O(N)
 * Space: O(1)
 */
void final_result(void) {
    int sti;
    for (sti = 0; sti < N; sti++) {
        printf("%d\n", class[sti]->grade);
    }
}
