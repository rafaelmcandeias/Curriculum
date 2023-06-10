#include <stdio.h>
#include <stdlib.h>

int ex(int b, int e){
	int result = 1;
	while (e != 0) {
        result *= b;
        --e;
    }
    return result;
}

int main(){
	int i, e = 0, nt = 0, np = 0, q = 0;
	long t = 0;
	printf("T = ");
	scanf("%ld", &t);
	printf("#T = ");
	scanf("%d", &nt);
	printf("#P = ");
	scanf("%d", &np);
	printf("q = ");
	scanf("%d", &q);
	e = ex(10, np);
	for(i = nt-np+1; i > 0; i--){
		printf("t%d = %ld\n", i, (t%e)%q);
		t /= 10;
	}
	return 0;
}