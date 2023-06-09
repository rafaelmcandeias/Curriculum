#include <stdio.h>
#include <stdlib.h>
#include "locks.h"


/*funcao que inicializa o trinco*/
void init_trinco(pthread_rwlock_t trinco){	
	/*inicializa o trinco*/
	if(pthread_rwlock_init(&trinco, NULL) != 0){
		perror("Error: can't initialize mutex_lock");
		exit(EXIT_FAILURE);
	}
}


/*funcao que destroi o trinco*/
void destroy(pthread_rwlock_t trinco){
	/*destroi o trinco rwlock*/
	if(pthread_rwlock_destroy(&trinco) != 0){
		perror("Error: can't destroy rw_lock");
		exit(EXIT_FAILURE);
	}
}



void lock(pthread_rwlock_t trinco, int flag){
	if(flag == 'w'){
		/*bloqueia o trinco rwlock write*/
		if(pthread_rwlock_wrlock(&trinco) != 0){
			perror("Error: can't lock wr_lock");
			exit(EXIT_FAILURE);
		}
	}

	/*caso seja um rwlock read*/
	else if(flag == 'r'){
		/*bloqueia o trinco rwlock read*/
		if(pthread_rwlock_rdlock(&trinco) != 0){
			perror("Error: can't lock wr_lock");
			exit(EXIT_FAILURE);
		}
	}

	/*caso flag incorreta*/
	else{
		perror("Error: incorrect flag in function lock");
		exit(EXIT_FAILURE);
	}
}


/*funcao que desbloqueia o trinco*/
void unlock(pthread_rwlock_t trinco){
	/*desbloqeuia o trinco rwlock*/
	if(pthread_rwlock_unlock(&trinco) != 0){
		perror("Error: can't unlock rd_lock");
		exit(EXIT_FAILURE);
	}
}