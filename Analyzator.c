#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	unsigned char c;
	int identity, file_size, file_pointer, i, j, n=0;

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

	float *pole_floatov[n][20];
	unsigned char *pole_charov[n];
	float avg[n], avg_1 = 0;
	
	for(i=0;i<n;i++){
	
		pole_charov[i]= (unsigned char *)malloc (sizeof(unsigned char));
		read(identity,pole_charov[i],sizeof(unsigned char));
		
		for(j=0;j<(int)*pole_charov[i];j++){
			pole_floatov[i][j]= (float*)malloc (sizeof(float));
				read(identity,pole_floatov[i][j],sizeof(float));
			avg_1 += *pole_floatov[i][j];
		}
		avg[i] = avg_1/(*pole_charov[i]);
		avg_1=0;
		printf("Priemer %d. postup. : %f\n",i+1, avg[i]);
	}
		for(i=0;i<n;i++){
		avg_1 += avg[i];
		}
	
	avg_1 = avg_1/n;
	printf("Priemer priemerov postup. : %f\n\n",avg_1);
	
	for(i=0;i<n;i++){
		for(j=0;j<(int)*pole_charov[i];j++){
			printf("%f ",*pole_floatov[i][j]);
		}
		printf(" \n");
	}

		free(pole_charov);
		free(pole_floatov);
		
	close(identity);
}
