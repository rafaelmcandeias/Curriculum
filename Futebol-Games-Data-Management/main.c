/**
 * @file main.c
 * @author Rafael Candeias
 * @brief Main loop that program executes
 * @version 0.1
 * @date 2019 Maio 17
 * 
 */

#include "lib.h"

int main() {
    char parameters[INPUT];
    char command = getchar();
    int line_number = 0;

    start();

    while (command != STOP) {
        getchar();
        switch (command) {
            /* command: a */
            case ADD_GAME:
                scanf("%3073[^\n]%*c", parameters);
                #ifdef DEBUG
                printf("INPUT: %c %s\n", command, parameters);
                #endif
                add_game(parameters, ++line_number);
                break;

            /* command: l */
            case ALL_GAMES:
                #ifdef DEBUG
                printf("INPUT: %c\n", command);
                #endif
                print_all_games(++line_number);
                break;

            /* command: p */
            case SEARCH_GAME:
                scanf("%1022[^\n]%*c", parameters);
                #ifdef DEBUG
                printf("INPUT: %c %s\n", command, parameters);
                #endif
                search_game(parameters, ++line_number);
                break;

            /* command: r */
            case REMOVE_GAME:
                scanf("%1022[^\n]%*c", parameters);
                #ifdef DEBUG
                printf("INPUT: %c %s\n", command, parameters);
                #endif
                remove_game(parameters, ++line_number);
                break;

            /* command: s */
            case CHANGE_GAME_SCORE:
                scanf("%1022[^\n]%*c", parameters);
                #ifdef DEBUG
                printf("INPUT: %c %s\n", command, parameters);
                #endif
                change_game_score(parameters, ++line_number);
                break;

            /* command: A */
            case ADD_TEAM:
                scanf("%1022[^\n]%*c", parameters);
                #ifdef DEBUG
                printf("INPUT: %c %s\n", command, parameters);
                #endif
                add_team(parameters, ++line_number);
                break;

            /* command: P */
            case SEARCH_TEAM:
                scanf("%1022[^\n]%*c", parameters);
                #ifdef DEBUG
                printf("INPUT: %c %s\n", command, parameters);
                #endif
                search_team(parameters, ++line_number);
                break;

            /* command: g */
            case WINNERS_ORDERED:
                #ifdef DEBUG
                printf("INPUT: %c\n", command);
                #endif
                print_winners_ordered(++line_number);
                break;

            /* command: P */
            /*#ifdef DEBUG
            case PRINT:
                print_all();
                break;
            #endif
            */
        }
        command = getchar();
    }
    end();
    return 0;
}