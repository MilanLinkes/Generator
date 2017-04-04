#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>

void write(char name[50]){

}

int main(int argc, char** argv){
	FILE *fw;
	char name[50];
	char n;
	
	scanf("Enter the file name: %s", &name[0]);
	scanf("\nEnter the number of sequences: %c", &n);
	
	if((fw = fopen(name, "w")) == NULL){
	return 1;
}
	
	return 0;
}
