/**
 * @file lib.h
 * @author Rafael Candeias
 * @brief Header file for auxiliariy functions and data types
 * @version 0.1
 * @date 2019-05-17
 *
 */
#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STOP 'x'
/* 1023*3 + 5 */
#define INPUT 3074
#define MAX_NAME 1023
#define HASH_LIMIT 997
#define ADD_GAME 'a'
#define ALL_GAMES 'l'
#define SEARCH_GAME 'p'
#define REMOVE_GAME 'r'
#define CHANGE_GAME_SCORE 's'
#define ADD_TEAM 'A'
#define SEARCH_TEAM 'P'
#define WINNERS_ORDERED 'g'
#ifdef DEBUG
#define PRINT 'd'
#endif


typedef struct Team {
    char *name;
    int wins;
    struct Team *next;
} team_t;

typedef struct Game {
    char *name, *team1, *team2;
    int score[2];
    struct Game *next;
} game_t;

typedef struct Node {
    struct Node *next;
    game_t *game;
} node_t;

typedef struct LinkedList {
    node_t *head;
    node_t *tail;
} linked_list_t;


void start(void);
unsigned long hash(char *str);
void free_game(game_t *game);
void free_team(team_t *team);
void end(void);
game_t *get_game(char *name);
team_t *get_team(char *name);
void merge(char **names, int l, int m, int r);
void mergeSort(char **names, int l, int r);
void add_to_games(game_t *game);
void add_to_list_of_games(game_t *game);
void add_to_teams(team_t *team);
void add_game(char* parameters, int line_number);
void print_all_games(int line_number);
void search_game(char* parameters, int line_number);
void remove_game(char* parameters, int line_number);
void change_game_score(char* parameters, int line_number);
void add_team(char* parameters, int line_number);
void search_team(char* parameters, int line_number);
void print_winners_ordered(int line_number);
#ifdef DEBUG
void print_all(void);
#endif

#endif
