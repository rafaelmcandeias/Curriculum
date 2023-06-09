#include <stdio.h>
#include <stdlib.h>
#include "locks.h"

/*variavel que guarda o trinco mutex*/
pthread_mutex_t mutex_trinco;
/*variavel que guarda o trinco rwlock*/
pthread_rwlock_t rw_trinco;
/*utilizacao da sync flag inicializada na main*/
extern int _sync_flag;


/*funcao que inicializa o trinco*/
void init_trinco(){
	/*caso a flag seja nosync*/
	if(_sync_flag == 0){
		return;
	}
	
	/*caso a flag seja mutex*/
	if(_sync_flag == 1){
		/*inicializa o trinco mutex*/
		if(pthread_mutex_init(&mutex_trinco, NULL) != 0){
			perror("Error: can't initialize mutex_lock");
			exit(EXIT_FAILURE);
		}
	}
	
	/*caso a flag seja rwlock*/
	else if(_sync_flag == 2){
		/*inicializa o trinco rwlock*/
		if(pthread_rwlock_init(&rw_trinco, NULL) != 0){
			perror("Error: can't initialize rw_lock");
			exit(EXIT_FAILURE);
		}
	}

	/*devolve erro se flag incorreta*/
	else{
		perror("Error: invalid sync flag");
		exit(EXIT_FAILURE);
	}

}


/*funcao que destroi o trinco*/
void destroy(){
	/*caso a flag seja nosync*/
	if(_sync_flag == 0){
		return;
	}

	/*caso a flag seja mutex*/
	if(_sync_flag == 1){
		/*destroi o trinco mutex*/
		if(pthread_mutex_destroy(&mutex_trinco) != 0){
			perror("Error: can't destroy mutex_lock");
			exit(EXIT_FAILURE);
		}
	}

	/*caso a flag seja rwlock*/
	else if(_sync_flag == 2){
		/*destroi o trinco rwlock*/
		if(pthread_rwlock_destroy(&rw_trinco) != 0){
			perror("Error: can't destroy rw_lock");
			exit(EXIT_FAILURE);
		}
	}
	/*devolve erro se flag incorreta*/
	else{
		perror("Error: invalid sync flag");
		exit(EXIT_FAILURE);
	}
}


/*lock o trinco mutex*/
void mutex_lock(){
	/*caso a flag seja nosync*/
	if(_sync_flag == 0){
		return;
	}
	
	/*bloqueia o trinco mutex*/
	if(pthread_mutex_lock(&mutex_trinco) != 0){
		perror("Error: can't lock mutex_lock");
		exit(EXIT_FAILURE);
	}
}


/*desbloqueia o trinco mutex*/
void mutex_unlock(){
	/*caso a flag seja nosync*/
	if(_sync_flag == 0){
		return;
	}
	
	/*desbloqueia o trinco mutex*/
	if(pthread_mutex_unlock(&mutex_trinco) != 0){
		perror("Error: can't lock mutex_lock");
		exit(EXIT_FAILURE);
	}
}


//will contain the line number
void lock(int flag, int debug){
	/*caso a flag seja nosync*/
	if(_sync_flag == 0){
		return;
	}

	/*caso a sync flag seja mutex*/
	if(_sync_flag == 1){
		/*bloqueia o trinco mutex*/
		if(pthread_mutex_lock(&mutex_trinco) != 0){
			perror("Error: can't lock mutex_lock");
			exit(EXIT_FAILURE);
		}
	}

	/*caso a sync flag seja rwlock*/
	else if(_sync_flag == 2){
		
		/*caso seja um rwlock write*/
		if(flag == 'w'){
			/*bloqueia o trinco rwlock write*/
			if(pthread_rwlock_wrlock(&rw_trinco) != 0){
				perror("Error: can't lock wr_lock");
				exit(EXIT_FAILURE);
			}
			return;
		}

		/*caso seja um rwlock read*/
		else if(flag == 'r'){
			/*bloqueia o trinco rwlock read*/
			if(pthread_rwlock_rdlock(&rw_trinco) != 0){
				perror("Error: can't lock wr_lock");
				exit(EXIT_FAILURE);
			}
			return;
		}

		/*caso nao seja nem read nem write -> falg incorreta*/
		else{
			perror("Error: wrong flag in lock function");
			exit(EXIT_FAILURE);
		}
	}

	/*devolve erro se sync flag incorreta*/
	else{
		perror("Error: invalid sync flag");
		exit(EXIT_FAILURE);
	}
}


/*funcao que desbloqueia o trinco*/
void unlock(int debug){
	/*caso a flag seja nosync*/
	if(_sync_flag == 0){
		return;
	}

	/*caso a flag seja mutex*/
	if(_sync_flag == 1){
		/*desbloqeuia o trinco mutex*/
		if(pthread_mutex_unlock(&mutex_trinco) != 0){
			perror("Error: can't unlock mutex_lock");
			exit(EXIT_FAILURE);
		}
	}

	/*caso a flag seja rwlock*/
	else if(_sync_flag == 2){
		/*desbloqeuia o trinco rwlock*/
		if(pthread_rwlock_unlock(&rw_trinco) != 0){
			perror("Error: can't unlock rd_lock");
			exit(EXIT_FAILURE);
		}
	}

	/*caso a sync flag esteja incorreta*/
	else{
		perror("Error: wrong flag in lock function");
		exit(EXIT_FAILURE);
	}
}