#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	unsigned char *d;
	float *p[20];
}POSTUPNOST;

int main(int argc, char* argv[]){
	unsigned char c;
	int identity, file_size, file_pointer, i, j, pocet_float = 0, n=0;
	
	  if(argc!=2){
	   	printf("Zadal si nespravny pocet argumentov\n");
	   	return 0;
	}
	
	identity = open(argv[1],  O_RDONLY | O_BINARY , S_IWUSR);
	
	if(identity >= 0){
	} 
	else{
		printf("Subor sa neotvoril. Skus to znova\n");
		return 0;
	}
	
	file_size = lseek(identity, 0, SEEK_END);
	file_pointer = lseek(identity, 0, SEEK_SET);

	do{
	read(identity,&c,sizeof(unsigned char));
	file_pointer = lseek(identity,(int)c*(sizeof(float)), SEEK_CUR);
	n++;
	
	} while(file_size != file_pointer);
	lseek(identity, 0, SEEK_SET);
	
	printf("\nPocet postupnosti: %d\n", n);
	
	POSTUPNOST A[n];
	float avg[n], avg_1 = 0;
	
	for(i=0;i<n;i++){
	
		A[i].d= (unsigned char *)malloc (sizeof(unsigned char));
		read(identity,A[i].d,sizeof(unsigned char));
		
		for(j=0;j<(int)*A[i].d;j++){
			A[i].p[j]= (float*)malloc (sizeof(float));
				read(identity,A[i].p[j],sizeof(float));
			avg_1 += *A[i].p[j];
		}
		avg[i] = avg_1/(*A[i].d);
		avg_1=0;
		printf("%d. avg.: %f\n",i+1, avg[i]);
	}
	
		for(i=0;i<n;i++){
		avg_1 += avg[i];
		}
	
	avg_1 = avg_1/n;
	printf("Total avg.: %f\n\n",avg_1);
	
	for(i=0;i<n;i++){
		for(j=0;j<(int)*A[i].d;j++){
			printf(" %f ",*A[i].p[j]);
		}
		printf(" \n");
	}
	
	close(identity);
}
