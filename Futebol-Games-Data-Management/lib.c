/**
 * @file lib.c
 * @author Rafael Candeias
 * @brief 
 * @version 0.1
 * @date 2022-04-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "lib.h"

game_t **games;
linked_list_t *list_of_games;
team_t **teams;
int games_counter = 0;
int teams_counter = 0;

/**
 * @brief Initializes the games hash table, teams hash table and linked list of games
 * 
 */
void start(void) {
    int i;
    
    games = (game_t **)malloc(sizeof(game_t *) * HASH_LIMIT);
    for (i = 0; i < HASH_LIMIT; i++) {
        games[i] = NULL;
    }
    
    teams = (team_t **)malloc(sizeof(team_t *) * HASH_LIMIT);
    for (i = 0; i < HASH_LIMIT; i++) {
        teams[i] = NULL;
    }
    
    list_of_games = (linked_list_t *)malloc(sizeof(linked_list_t));
    list_of_games->head = NULL;
    list_of_games->tail = NULL;
}


/**
 * @brief Function used to assign a index trhough a string
 * 
 * @param str 
 * @return unsigned long 
 */
unsigned long hash(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % HASH_LIMIT;
}


/**
 * @brief Frees memory allocated to game pointer
 * @complexity: O(n) if all teams collide at same hash index
 * @param game
 */
void free_game(game_t *remove) {
    game_t *prev, *curr;
    unsigned long h = hash(remove->name);
    
    /* Remove head of index */
    if (strcmp(games[h]->name, remove->name) == 0) {
        remove = games[h];
        games[h] = remove->next;
    }
    else {
        for (curr = games[h]; strcmp(curr->name, remove->name) != 0; curr = curr->next) {
            prev = curr;
        }
        prev->next = curr->next;
    }
    /* Free allocated mem */ 
    free(remove->name);
    free(remove->team1);
    free(remove->team2);
    free(remove);
}


/**
 * @brief Frees memory allocated to team pointer
 * @complexity: O(1)
 * @param team
 */
void free_team(team_t *team) {
    free(team->name);
    free(team);
}


/**
 * @brief frees memory from main data types
 * @complexity: O(n) , n = max(HASH_LIMIT, n_games)
 */
void end(void) {
    node_t *curr;
    team_t *team, *team_remove;
    int i;

    for (i = 0; i < HASH_LIMIT; i++) {
        team = teams[i];
        while (team != NULL) {
            team_remove = team;
            team = team->next;
            free_team(team_remove);
        }
    }

    while (list_of_games->head != NULL) {
        curr = list_of_games->head;
        list_of_games->head = list_of_games->head->next;
        free(curr->game->name);
        free(curr->game->team1);
        free(curr->game->team2);
        free(curr->game);
        free(curr);
    }
    free(list_of_games);
    free(games);
    free(teams);
}


/**
 * @brief Returns game pointer
 * @complexity: O(n) if all games collide at same hash index
 * @param name
 * @return NULL if does not exist
 */
game_t *get_game(char *name) {
    game_t *aux = games[hash(name)];

    while (aux != NULL) {
        if (strcmp(aux->name, name) == 0) {
            return aux;
        }
        aux = aux->next;
    }  
    return NULL;
}


/**
 * @brief Returns team pointer
 * @complexity: O(n) if all teams collide at same hash index
 * @param name
 * @return NULL if does not exist
 */
team_t *get_team(char *name) {
    team_t *aux = teams[hash(name)];

    while (aux != NULL) {
        if (strcmp(aux->name, name) == 0) {
            return aux;
        }
        aux = aux->next;
    }
    return NULL;
}


/**
 * @brief Prints game like NL name team1 team2 score1 score2
 * 
 * @param game 
 * @param line_number 
 */
void print_game(game_t *game, int line_number) {
    printf("%d %s %s %s %d %d\n", line_number, game->name, game->team1, game->team2, game->score[0], game->score[1]);
}


void merge(char **names, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    /* create temp arrays */
    char **L = (char **)malloc(sizeof(char *) * n1);
    char **R = (char **)malloc(sizeof(char *) * n2);
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = names[l + i];
    for (j = 0; j < n2; j++)
        R[j] = names[m + 1 + j];
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0) {
            names[k] = L[i];
            i++;
        }
        else {
            names[k] = R[j];
            j++;
        }
        k++;
    }
  
    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        names[k] = L[i];
        i++;
        k++;
    }
  
    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        names[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}


/**
 * @brief Applies merge sort algorithm to order
 * 
 * @param names array with names of most winners
 * @param l leftest index
 * @param r rightest index
 */
void mergeSort(char **names, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        /* Sort first and second halves */
        mergeSort(names, l, m);
        mergeSort(names, m + 1, r);
  
        merge(names, l, m, r);
    }
}


/**
 * @brief Function to insert game to the hashtable
 * 
 * @param game 
 */
void add_to_games(game_t *game) {
    unsigned long h = hash(game->name);

    /* Head of position in hashtable is null */
    if (games[h] == NULL) {
        games[h] = game;
    }
    else {
        game->next = games[h];
        games[h] = game;
    }
    games_counter++;
}


/**
 * @brief Adds a game pointer to the list of games
 * @complexity: O(1)
 * @param game 
 */
void add_to_list_of_games(game_t *game) {
    if (list_of_games->head == NULL) {
        list_of_games->head = (node_t *) malloc(sizeof(node_t));
        list_of_games->head->game = game;
        list_of_games->head->next = NULL;
        list_of_games->tail = list_of_games->head;
    }
    else {
        list_of_games->tail->next = (node_t *) malloc(sizeof(node_t));
        list_of_games->tail->next->game = game;
        list_of_games->tail = list_of_games->tail->next;
        list_of_games->tail->next = NULL;
    }
}


/**
 * @brief Function to insert team to the hashtable
 * 
 * @param team 
 */
void add_to_teams(team_t *team) {
    unsigned long h = hash(team->name);

    /* Head of position in hashtable is null */
    if (teams[h] == NULL){
        teams[h] = team;
    }
    else {
        team->next = teams[h];
        teams[h] = team;
    }
    teams_counter++;
}


/**
 * @brief Allocs memory to game and puts in hashtable
 * @complexity: O(1)
 * @param parameters name:team1:team2:score1:score2
 * @param line_number input line number to print
 */
void add_game(char *parameters, int line_number) {
    char name[MAX_NAME], team1[MAX_NAME], team2[MAX_NAME];
    int score1, score2;
    game_t *game;

    sscanf(parameters, "%1022[^:]:%1022[^:]:%1022[^:]:%d:%d", name, team1, team2, &score1, &score2);
    
    /* Game has to have a unique name */
    if (get_game(name) != NULL) {
        printf("%d Jogo existente.\n", line_number);
    }
    /* Teams have to exist */
    else if(get_team(team1) == NULL || get_team(team2) == NULL) {
        printf("%d Equipa inexistente.\n", line_number);
    }
    else {
        /* Create game */
        game = (game_t *) malloc(sizeof(game_t));
        game->name = (char *) malloc(sizeof(char) * strlen(name) + 1);
        strcpy(game->name, name);
        game->team1 = (char *) malloc(sizeof(char) * strlen(team1) + 1);
        strcpy(game->team1, team1);
        game->team2 = (char *) malloc(sizeof(char) * strlen(team2) + 1);
        strcpy(game->team2, team2);
        game->score[0] = score1;
        game->score[1] = score2;
        game->next = NULL;

        /* Updates winns if one team won */
        if (score1 > score2) {
            get_team(team1)->wins++;
        }
        else if (score1 < score2) {
            get_team(team2)->wins++;
        }
        
        /* Add game to hashtable games */
        add_to_games(game);

        /* Add game to linked list list_of_games */
        add_to_list_of_games(game);
    }
}


/**
 * @brief Prints all games in order
 * @complexity: O(n), n = #games
 * @param line_number 
 */
void print_all_games(int line_number) {
    node_t *aux;
    for (aux = list_of_games->head; aux != NULL; aux = aux->next) {
        print_game(aux->game, line_number);
    }
}


/**
 * @brief prints info about a game
 * @complexity: O(n) if all games collided in hash
 * @param parameters name
 * @param line_number
 */
void search_game(char *parameters, int line_number) {
    game_t *game;
    
    if ((game = get_game(parameters)) == NULL) {
        printf("%d Jogo inexistente.\n", line_number);
    }
    else {
        print_game(game, line_number);
    }
}


/**
 * @brief Removes a game given it's name
 * @complexity: O(n) if game to remove was the last one inserted
 * @param parameters name
 * @param line_number
 */
void remove_game(char *parameters, int line_number) {
    node_t *prev, *remove = list_of_games->head;
    team_t *team1, *team2;
    int index = 2;

    if (get_game(parameters) == NULL) {
        printf("%d Jogo inexistente.\n", line_number);
    }
    else {
        /* Head of list_of_games is to remove */ 
        if (strcmp(remove->game->name, parameters) == 0) {
            list_of_games->head = remove->next;
        }
        else {
            prev = remove;
            remove = remove->next;
            while (strcmp(remove->game->name, parameters) != 0) {
                prev = remove;
                remove = remove->next;
                index++;
            }
            if (index == games_counter) {
                list_of_games->tail = prev;
            }
            prev->next = remove->next;
        }
        
        /* Removing a game means removing a win if a team won */
        team1 = get_team(remove->game->team1);
        team2 = get_team(remove->game->team2);
        if (remove->game->score[0] > remove->game->score[1]) {
            team1->wins--;
        }
        else if (remove->game->score[0] < remove->game->score[1]) {
            team2->wins--;
        }

        free_game(remove->game);
        free(remove);
        games_counter--;
    }
}


/**
 * @brief changes score of game
 * 
 * @param parameters name:score1:score2
 * @param line_number 
 */
void change_game_score(char *parameters, int line_number) {
    int new1, new2, prev1, prev2;
    char name[MAX_NAME];
    game_t *game;
    team_t * team1, *team2;
    sscanf(parameters, "%1022[^:]:%d:%d", name, &new1, &new2);

    if ((game = get_game(name)) == NULL) {
        printf("%d Jogo inexistente.\n", line_number);
    }
    else {
        team1 = get_team(game->team1);
        team2 = get_team(game->team2);
        prev1 = game->score[0];
        prev2 = game->score[1];
        
        if (prev1 == prev2) {
            if (new1 > new2) {
                team1->wins++;
            }
            else if (new2 > new1) {
                team2->wins++;
            }
        }
        else if (prev1 < prev2) {
            if (new1 == new2) {
                team2->wins--;
            }
            else if (new1 > new2) {
                team1->wins++;
                team2->wins--;
            }
        }
        else {
            if (new1 == new2) {
                team1->wins--;
            }
            else if (new1 < new2) {
                team2->wins++;
                team1->wins--;
            }
        }
        game->score[0] = new1;
        game->score[1] = new2;
    }
}


/**
 * @brief Adds a team to the teams hashtable
 * @comlexity: O(n) if all teams colided in same index hashtable
 * @param parameters name
 * @param line_number 
 */
void add_team(char *parameters, int line_number) {
    team_t *team;

    if (get_team(parameters)) {
        printf("%d Equipa existente.\n", line_number);
    }
    else {
        /* Allocs memory for new team */
        team = (team_t *) malloc(sizeof(team_t));
        team->name = (char *) malloc(sizeof(char) * strlen(parameters) + 1);
        strcpy(team->name, parameters);
        team->wins = 0;
        team->next = NULL;
        
        /* Adds new team to hash */
        add_to_teams(team);
    }
}


/**
 * @brief Searches a team given it's name
 * @comlexity: O(n) if all teams colided in same index hashtable
 * @param parameters name
 * @param line_number
 */
void search_team(char *parameters, int line_number) {
    team_t *team;

    if ((team = get_team(parameters)) == NULL) {
        printf("%d Equipa inexistente.\n", line_number);
    }
    else {
        printf("%d %s %d\n", line_number, team->name, team->wins);
    }
}


/**
 * @brief Prints alfabeticaly all teams with most wins
 * @comlexity: O(n)
 * @param line_number
 */
void print_winners_ordered(int line_number) {
    int i, max = 0, count = 0;
    char **names, **tmp;
    team_t *team;

    /* Teams need to exist */
    if (teams_counter > 0) {
        names = (char **) malloc(sizeof(char *) * teams_counter);

        for (i = 0; i < HASH_LIMIT; i++) {
            if (teams[i] != NULL) {
                
                for (team = teams[i]; team != NULL; team = team->next) {
                    if (team->wins >= max) {
                        if (team->wins > max) {
                            max = team->wins;
                            count = 0;
                        }
                        names[count++] = team->name;
                    }
                }
            }
        }

        /* Reallocates names array to remove extra space */
        tmp = realloc(names, sizeof(char *) * count);
        if (tmp == NULL) {
            free(names);
            perror("realloc error.\n");
        }
        else {
            names = tmp;
        }

        mergeSort(names, 0, count-1);

        printf("%d Melhores %d\n", line_number, max);
        for (i = 0; i < count; i++) {
            printf("%d * %s\n", line_number, names[i]);
        }

        free(names);
    }
}


/*
#ifdef DEBUG
void print_all(void) {

}
#endif
*/
