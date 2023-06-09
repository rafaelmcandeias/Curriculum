#ifndef FS_H
#define FS_H
#include "state.h"



void init_fs();
void destroy_fs();
int is_dir_empty(DirEntry *dirEntries);
int create(char *name, type nodeType);
int delete(char *name);
int lookup(char *name);
int procura(char *name, int lock_list[], int *last_index);
void print_tecnicofs_tree(char *fname);
int move(char *full_path, char *new_full_path);

#endif /* FS_H */
