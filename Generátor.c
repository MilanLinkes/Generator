#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

void plnka(int identita, int n){
	float rand_float;
	int i,j, rand_int;
	
	for(i=0; i<n; i++){
		rand_int=rand()%11 + 10;
		write(identita, &rand_int, 1);
		for(j=0;j<rand_int; j++){
			rand_float = rand()/(float)(RAND_MAX)*11+10;
			write(identita, &rand_float, 4);	
		}
	}
}

int main(int argc, char* argv[]){
    int identity, pisanie, n;
    
   	n=atoi(argv[2]);
	srand(time(0));
    
    if(argc!=3){
	   	printf("Zadal si prilis vela argumentov");
	   	return 0;
	}
	
	identity = open(argv[1],  O_WRONLY | O_BINARY | O_CREAT, S_IWUSR);

	plnka(identity,n);
      
    return 0;
}
