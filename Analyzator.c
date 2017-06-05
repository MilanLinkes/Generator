#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	unsigned char c;
	int identity, file_size, file_pointer, i, j, n = 0, *pole_charov;
	unsigned char pocet_v_post;
	float **pole_floatov, *avg, avg_1 = 0, hodnota;

	if (argc != 2) {
		printf("Zadal si nespravny pocet argumentov\n");
		return 0;
	}

	identity = open(argv[1], O_RDONLY | O_BINARY, S_IWUSR);

	if (identity < 0) {
		printf("Subor sa neotvoril. Skus to znova\n");
		return 0;
	}

	file_size = lseek(identity, 0, SEEK_END);
	file_pointer = lseek(identity, 0, SEEK_SET);

	do {
		if(read(identity, &c, sizeof(unsigned char))==-1){
			printf("Subor sa nepodarilo precitat\n");
			return 0;	
		}
		
		file_pointer = lseek(identity, (int)c*(sizeof(float)), SEEK_CUR);
		n++;

	} while (file_size != file_pointer);

	lseek(identity, 0, SEEK_SET);
	printf("\nPocet postupnosti: %d\n", n);

	pole_floatov = malloc(n*sizeof(float*));
	pole_charov = malloc(n*sizeof(int));
    avg = malloc(n*sizeof(float));
    
	if (pole_floatov== NULL) {
		printf("Nezdarena allokacia pamate.\n");
		return 0;
	}
		
	if (pole_charov == NULL) {
		printf("Nezdarena allokacia pamate.\n");
		return 0;
	}
		
	if (avg == NULL) {
		printf("Nezdarena allokacia pamate.\n");
		return 0;
	}
	
	for (i = 0; i < n; i++) {
		if (read(identity, &pocet_v_post, sizeof(unsigned char))==-1){
			printf("Subor sa nepodarilo precitat\n");
			return 0;
		}
		
		pole_charov[i]=pocet_v_post;
		pole_floatov[i] = malloc(pole_charov[i]*sizeof(float));

		if (pole_floatov[i]== NULL) {
			printf("Nezdarena allokacia pamate.\n");
			return 0;
		}
		
		for (j = 0;j<pole_charov[i];j++) {
				if(read(identity, &hodnota, sizeof(float))==-1){
					printf("Subor sa nepodarilo precitat\n");
					return 0;
				}
				
				pole_floatov[i][j]=hodnota;
				avg_1 += pole_floatov[i][j];
			}

		avg[i] = avg_1 / (pole_charov[i]);
		avg_1 = 0;
		printf("Priemer %d. postup. : %f\n", i + 1, avg[i]);
	}

	for (i = 0; i < n; i++) {
		avg_1 += avg[i];
	}

	avg_1 = avg_1 / n;
	printf("Priemer priemerov postup. : %f\n\n", avg_1);

	for (i = 0;i<n;i++) {

		for (j = 0; j < (int)pole_charov[i]; j++) {
			printf("%f ", pole_floatov[i][j]);
		}
		printf(" \n");
	}
	
	for(i=0; i<n; i++){
		free(pole_floatov[i]);
	}
	free(*pole_floatov);
	free(pole_charov);
	
	if (close(identity) == -1) {
		printf("Subor sa nepodarilo zavriet.\n");
		return 0;
	}
}
