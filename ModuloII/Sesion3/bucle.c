#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int count = strtol(argv[1],0,10);
	int j = count*1000000;
	int n=0;

	printf("%d\n", j);

	for (int i = 0; i < j; ++i){
		n = n+1;
	}

	printf("%d\n", n);

	return 0;
}