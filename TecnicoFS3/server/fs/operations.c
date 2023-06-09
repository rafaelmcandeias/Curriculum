#include "operations.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>




/* Given a path, fills pointers with strings for the parent path and child
 * file name
 * Input:
 *  - path: the path to split. ATENTION: the function may alter this parameter
 *  - parent: reference to a char*, to store parent path
 *  - child: reference to a char*, to store child file name
 */
void split_parent_child_from_path(char * path, char ** parent, char ** child) {

	int n_slashes = 0, last_slash_location = 0;
	int len = strlen(path);

	// deal with trailing slash ( a/x vs a/x/ )
	if (path[len-1] == '/') {
		path[len-1] = '\0';
	}

	for (int i=0; i < len; ++i) {
		if (path[i] == '/' && path[i+1] != '\0') {
			last_slash_location = i;
			n_slashes++;
		}
	}

	if (n_slashes == 0) { // root directory
		*parent = "";
		*child = path;
		return;
	}

	path[last_slash_location] = '\0';
	*parent = path;
	*child = path + last_slash_location + 1;
}


/*
 * Initializes tecnicofs and creates root node.
 */
void init_fs() {
	inode_table_init();
	/* create root inode */
	int root = inode_create(T_DIRECTORY);
	
	if (root != FS_ROOT) {
		printf("failed to create node for tecnicofs root\n");
		exit(EXIT_FAILURE);
	}
}


/*
 * Destroy tecnicofs and inode table.
 */
void destroy_fs() {
	inode_table_destroy();
}


/*
 * Checks if content of directory is not empty.
 * Input:
 *  - entries: entries of directory
 * Returns: SUCCESS or FAIL
 */

int is_dir_empty(DirEntry *dirEntries) {
	if (dirEntries == NULL) {
		return FAIL;
	}
	for (int i = 0; i < MAX_DIR_ENTRIES; i++) {
		if (dirEntries[i].inumber != FREE_INODE) {
			return FAIL;
		}
	}
	return SUCCESS;
}


/*
 * Looks for node in directory entry from name.
 * Input:
 *  - name: path of node
 *  - entries: entries of directory
 * Returns:
 *  - inumber: found node's inumber
 *  - FAIL: if not found
 */
int lookup_sub_node(char *name, DirEntry *entries) {
	if (entries == NULL) {
		return FAIL;
	}
	for (int i = 0; i < MAX_DIR_ENTRIES; i++) {
        if (entries[i].inumber != FREE_INODE && strcmp(entries[i].name, name) == 0) {
			int out = entries[i].inumber;
            return out;
        }
    }
	return FAIL;
}


/*
 * Creates a new node given a path.
 * Input:
 *  - name: path of node
 *  - nodeType: type of node
 * Returns: SUCCESS or FAIL
 */
int create(char *name, type nodeType){
	int parent_inumber, child_inumber;
	char *parent_name, *child_name, name_copy[MAX_FILE_NAME];
	int lock_list[DEPTH];
	int last_index = -1;

	/* use for copy */
	type pType;
	union Data pdata;
	strcpy(name_copy, name);
	split_parent_child_from_path(name_copy, &parent_name, &child_name);

	//one two
	parent_inumber = procura(parent_name, lock_list, &last_index);
	if (parent_inumber == FAIL) {
		printf("failed to create %s, invalid parent dir %s\n",
		        name, parent_name);
		remove_locks(lock_list, last_index);
		return FAIL;
	}

	//buscar a informacao parent - /one/two
	inode_get(parent_inumber, &pType, &pdata);
	if(pType != T_DIRECTORY) {
		printf("failed to create %s, parent %s is not a dir\n",
		        name, parent_name);
		remove_locks(lock_list, last_index);
		return FAIL;
	}

	if (lookup_sub_node(child_name, pdata.dirEntries) != FAIL) {
		printf("failed to create %s, already exists in dir %s\n",
		       child_name, parent_name);
		remove_locks(lock_list, last_index);
		return TECNICOFS_ERROR_FILE_ALREADY_EXISTS;
	}

	/* create node and add entry to folder that contains new node */
	child_inumber = inode_create(nodeType);
	if (child_inumber == FAIL) {
		printf("failed to create %s in  %s, couldn't allocate inode\n",
		        child_name, parent_name);
		remove_locks(lock_list, last_index);
		return FAIL;
	}

	if (dir_add_entry(parent_inumber, child_inumber, child_name) == FAIL) {
		printf("could not add entry %s in dir %s\n",
		       child_name, parent_name);
		printf("Failed here \n\n\n"); 
		
		remove_locks(lock_list, last_index);
		return FAIL;
	}

	remove_locks(lock_list, last_index);

	return SUCCESS;
}


/*
 * Deletes a node given a path.
 * Input:
 *  - name: path of node
 * Returns: SUCCESS or FAIL
 */
int delete(char *name){

	int parent_inumber, child_inumber;
	char *parent_name, *child_name, name_copy[MAX_FILE_NAME];
	/* use for copy */
	type pType, cType;
	union Data pdata, cdata;

	int lock_list[DEPTH];
	int last_index = -1;

	strcpy(name_copy, name);
	split_parent_child_from_path(name_copy, &parent_name, &child_name);

	parent_inumber = procura(parent_name, lock_list, &last_index);

	if (parent_inumber == FAIL) {
		printf("failed to delete %s, invalid parent dir %s\n",
		        child_name, parent_name);
		remove_locks(lock_list, last_index);
		return FAIL;
	}

	inode_get(parent_inumber, &pType, &pdata);

	if(pType != T_DIRECTORY) {
		printf("failed to delete %s, parent %s is not a dir\n",
		        child_name, parent_name);
		remove_locks(lock_list, last_index);
		return FAIL;
	}

	child_inumber = lookup_sub_node(child_name, pdata.dirEntries);

	if (child_inumber == FAIL) {
		printf("could not delete %s, does not exist in dir %s\n",
		       name, parent_name);
		remove_locks(lock_list, last_index);
		return FAIL;
	}

	inode_get(child_inumber, &cType, &cdata);


	if (cType == T_DIRECTORY && is_dir_empty(cdata.dirEntries) == FAIL) {
		printf("could not delete %s: is a directory and not empty\n",
		       name);
		remove_locks(lock_list, last_index);
		return FAIL;
	}

	/* remove entry from folder that contained deleted node */
	if (dir_reset_entry(parent_inumber, child_inumber) == FAIL) {
		printf("failed to delete %s from dir %s\n",
		       child_name, parent_name);
		remove_locks(lock_list, last_index);
		return FAIL;
	}

	if (inode_delete(child_inumber) == FAIL) {
		printf("could not delete inode number %d from dir %s\n",
		       child_inumber, parent_name);
		remove_locks(lock_list, last_index);
		return FAIL;
	}

	remove_locks(lock_list, last_index);

	return SUCCESS;
}

/*
 * Lookup for a given path.
 * Input:
 *  - name: path of node
 * Returns:
 *  inumber: identifier of the i-node, if found
 *     FAIL: otherwise
 */
int lookup(char *name) {
	char full_path[MAX_FILE_NAME];
	char delim[] = "/";
	char *saveptr;
	strcpy(full_path, name);
	/* start at root node */
	int current_inumber = FS_ROOT;
	int lock_list[DEPTH];
	int last_index = -1;

	/* use for copy */
	type nType;
	union Data data;
	/* get root inode data */
	inode_get(current_inumber, &nType, &data);
	/* read locks root inode */
	lock_trinco(current_inumber, 'r', lock_list, &last_index);

	/* gets path from argument */
	char *path = strtok_r(full_path, delim, &saveptr);

	/* read locks for every file or directory in full_path */
	while (path != NULL && (current_inumber = lookup_sub_node(path, data.dirEntries)) != FAIL) {
		inode_get(current_inumber, &nType, &data);
		lock_trinco(current_inumber, 'r', lock_list, &last_index);
		path = strtok_r(NULL, delim, &saveptr);
	}
	remove_locks(lock_list, last_index);
	return current_inumber;
}


/*
 * Lookup for a given path.
 * Input:
 *  - name: path of node
 * Returns:
 *  inumber: identifier of the i-node, if found
 *     FAIL: otherwise
 */
int procura(char *name, int lock_list[], int *last_index) {
	char full_path[MAX_FILE_NAME];
	char delim[] = "/";
	char *saveptr;
	strcpy(full_path, name);
	/* start at root node */
	int current_inumber = FS_ROOT;

	/* use for copy */
	type nType;
	union Data data;
	/* get root inode data */
	inode_get(current_inumber, &nType, &data);
	char *path = strtok_r(full_path, delim, &saveptr);

	// caso nao haja argumento, ou seja, escreve-se na root
	if (!path) {
		/* write lock da root */
		lock_trinco(current_inumber, 'w', lock_list, last_index);
	}
	/* search for all sub nodes */
	else {
		/* read lock da root */
		lock_trinco(current_inumber, 'r', lock_list, last_index);
		/* enquanto houver path e existir nas diretorias do seu pai */
		while (path != NULL && (current_inumber = lookup_sub_node(path, data.dirEntries)) != FAIL) {
			strcpy(name, path);
			path = strtok_r(NULL, delim, &saveptr);
			/* caso seja o ultimo pai do full_path*/
			if (path == NULL){
				inode_get(current_inumber, &nType, &data);
				/* write lock do ultimo ficheiro do full_path */
				lock_trinco(current_inumber, 'w', lock_list, last_index);
			}
			/* caso ainda nao tenhamos chegado ao fim do full_path */
			else{
				inode_get(current_inumber, &nType, &data);
				/* read lock da diretoria associada ao current_inumber */
				lock_trinco(current_inumber, 'r', lock_list, last_index);
			}
		}
	}
	return current_inumber;
}

/*
 * Prints tecnicofs tree.
 * Input:
 *  - fp: pointer to output file
 */
void print_tecnicofs_tree(char *fname){
	FILE *fp;
	if ((fp = fopen(fname, "w")) == NULL){
		perror("Error: can't open outputFile");
		exit(EXIT_FAILURE);
	}

	inode_print_tree(fp, FS_ROOT, "");

	if (fclose(fp) != 0){
		perror("Error: can't close outputFile");
		exit(EXIT_FAILURE);
	}
}


int move(char *full_path, char *new_full_path){
	// exemplo de argumentos: .../dA/f1 .../dB/f2
	// guardar o inumber de f1 e o seu nome
	int parent_inumber, child_inumber, new_parent_inumber;
	char *parent_name, *child_name, *new_parent_name, *new_child_name;
	char full_path_copy[MAX_FILE_NAME], new_full_path_copy[MAX_FILE_NAME];
	int lock_list[DEPTH];
	int last_index = -1;
	type pType;
	union Data pdata;

	strcpy(full_path_copy, full_path);
	// separa o primeiro argumento em pai e filho; pai = .../dA, filho = f1
	split_parent_child_from_path(full_path_copy, &parent_name, &child_name);
	
	// guarda o inumber do pai atual e faz lock dos inumbers dos respetivos pais
	// e write lock do ultimo pai; read lock(.../), write lock(dA) 
	parent_inumber = procura(parent_name, lock_list, &last_index);
	inode_get(parent_inumber, &pType, &pdata);
	
	//guarda o inumber do filho e faz o seu write lock
	child_inumber = lookup_sub_node(child_name, pdata.dirEntries);
	lock_trinco(child_inumber, 'w', lock_list, &last_index);
	
	// remover o f1 das dirEntries do dA, mas NAO remover da inode_table
	if (dir_reset_entry(parent_inumber, child_inumber) == FAIL) {
		printf("failed to delete %s from dir %s\n", child_name, parent_name);
		remove_locks(lock_list, last_index);
		return FAIL;
	}

	// faz unlock de todos os locks, excepto do filho
	last_index--;
	remove_locks(lock_list, last_index);
	// atualiza a lock list, dizendo que o filho ainda necessita de um unlock
	last_index = 0;
	lock_list[last_index] = child_inumber;

	strcpy(new_full_path_copy, new_full_path);
	// separa o segundo argumento em novo_pai e novo_filho; novo_pai = .../dB, novo_filho = f2
	split_parent_child_from_path(new_full_path_copy, &new_parent_name, &new_child_name);
	
	// guarda o inumber, type e data do novo_pai
	// faz read lock de todos os pais excepto do ultimo, ao qual faz write lock
	// read lock(.../), write lock(dB)
	new_parent_inumber = procura(new_parent_name, lock_list, &last_index);
	inode_get(new_parent_inumber, &pType, &pdata);

	// verifica se o novo_pai e um diretorio
	if(pType != T_DIRECTORY) {
		printf("failed to move %s from parent %s to parent %s as it's not a dir\n", child_name, parent_name, new_parent_name);
		remove_locks(lock_list, last_index);
		return FAIL;
	}
	
	//adiciona o filho, com o novo nome, na data do novo_pai
	if (dir_add_entry(new_parent_inumber, child_inumber, new_child_name) == FAIL) {
		printf("could not add entry %s as %s in dir %s\n", child_name, new_child_name, new_parent_name);
		remove_locks(lock_list, last_index);
		return FAIL;
	}

	// faz unlock de todo o que esta locked
	remove_locks(lock_list, last_index);

	return SUCCESS;
}
