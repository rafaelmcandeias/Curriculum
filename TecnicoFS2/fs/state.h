#ifndef INODES_H
#define INODES_H

#include <stdio.h>
#include <stdlib.h>
#include "../tecnicofs-api-constants.h"
#include "locks.h"

/* FS root inode number */
#define FS_ROOT 0

#define FREE_INODE -1
#define INODE_TABLE_SIZE 50
#define MAX_DIR_ENTRIES 20

#define SUCCESS 0
#define FAIL -1

#define DELAY 0
/*
 * Contains the name of the entry and respective i-number
 */
typedef struct dirEntry {
	char name[MAX_FILE_NAME];
	int inumber;
} DirEntry;

/*
 * Data is either text (file) or entries (DirEntry)
 */
union Data {
	char *fileContents; /* for files */
	DirEntry *dirEntries; /* for directories */
};

/*
 * I-node definition
 */
typedef struct inode_t {    
	type nodeType;
	union Data data;
	pthread_rwlock_t trinco;
} inode_t;


void insert_delay(int cycles);
void inode_table_init();
void inode_table_destroy();
int inode_create(type nType);
int inode_delete(int inumber);
int inode_get(int inumber, type *nType, union Data *data);
int inode_set_file(int inumber, char *fileContents, int len);
int dir_reset_entry(int inumber, int sub_inumber);
int dir_add_entry(int inumber, int sub_inumber, char *sub_name);
void inode_print_tree(FILE *fp, int inumber, char *name);

void remove_locks(int *lock_list, int last_index);

void unlock_trinco(int inumber);
void lock_trinco(int inumber, int flag, int *lock_list, int *last_index);


#endif /* INODES_H */
