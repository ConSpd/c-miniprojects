#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void start_game(int,int,int);
void fill_spaces(int**,int,int);
void place_bombs(int**,int,int,int);
void draw_markings(int**,int,int);
void check_surroundings(int**,int,int,int,int);
void write_to_file(int**,int,int);
int occupied(int,int*,int);


int main(int argc,char** argv){
	srand(time(NULL));
	int M,N,K;
	do{
		printf("Enter M dimension: ");
		scanf("%d",&M);
		printf("Enter N dimension: ");
		scanf("%d",&N);
	}while((M <= 0) && (N <= 0));
	do{
		printf("Enter number of Bombs: ");
		scanf("%d",&K);
	}while(K > (M*N));
	start_game(M,N,K);
	return 0;
}

void start_game(int M,int N,int bombs){
	int** matrix = (int**)malloc(M*sizeof(int*));
	for(int i=0;i<M;i++)
		matrix[i] = (int*)malloc(N*sizeof(int));
	
	fill_spaces(matrix,M,N);
	place_bombs(matrix,M,N,bombs);
	draw_markings(matrix,M,N);
	
	for(int i=0;i<M;i++){
		for(int j=0;j<N;j++)
			printf("%d\t",matrix[i][j]);
		printf("\n");
	}
	
	write_to_file(matrix,M,N);
	for(int i=0;i<M;i++)
		free(matrix[i]);
	free(matrix);
}

void fill_spaces(int** matrix,int M,int N){
	int total_area = M * N;
	
	// Οι αριθμοί που δεν χρησιμοποιούνται
	int* leftovers = (int*)malloc(total_area*sizeof(int));
	for(int i=0;i<total_area;i++)
		leftovers[i] = i;
	
	for(int i=0;i<M;i++)
		for(int j=0;j<N;j++)
			do{
				matrix[i][j] = (rand() % total_area);
			}while(occupied(matrix[i][j],leftovers,total_area));
	free(leftovers);
}

// Eλέγχει αν η τιμή είναι διαθέσιμη απο τον πίνακα leftovers
// Αν την χρησιμοποιήσει την αντικαθιστά με τιμή -1
int occupied(int value,int* leftovers,int size){
	for(int i=0;i<size;i++)
		if(value == leftovers[i]){
			leftovers[i] = -1;
			return 0;
		}
	return 1;
}

void place_bombs(int** matrix,int M,int N,int bombs){
	for(int i=0;i<M;i++)
		for(int j=0;j<N;j++){
			if(matrix[i][j] >= bombs)
				matrix[i][j] = 0;
			else
				matrix[i][j] = 999;
		}
}

void draw_markings(int** matrix,int M,int N){
	for(int i=0;i<M;i++){
		for(int j=0;j<N;j++){
			if(matrix[i][j] == 999)
				continue;
			check_surroundings(matrix,M,N,i,j);
		}
	}
}

void check_surroundings(int** matrix,int M,int N,int i,int j){
	int flag = 0;
	if(i-1 >= 0)
		if(matrix[i-1][j] == 999)
			flag++;
	if(i+1 < M)
		if(matrix[i+1][j] == 999)
			flag++;
	if(j-1 >= 0)
		if(matrix[i][j-1] == 999)
			flag++;
	if(j+1 < N)
		if(matrix[i][j+1] == 999)
			flag++;
	
	if((j-1 >= 0) && (i-1 >= 0))
		if(matrix[i-1][j-1] == 999)
			flag++;
	if((j+1 < N) && (i-1 >= 0))
		if(matrix[i-1][j+1] == 999)
			flag++;
	if((j-1 >= 0) && (i+1 < M))
		if(matrix[i+1][j-1] == 999)
			flag++;
	if((j+1 < N) && (i+1 < M))
		if(matrix[i+1][j+1] == 999)
			flag++;
	
	matrix[i][j] = flag;
}

void write_to_file(int** matrix,int M,int N){
	FILE* fp;	
	fp = fopen("minesweeper","w");
	if(fp == NULL){
		printf("Couldn't write to file\n");
		exit(1);
	}	
	for(int i=0;i<M;i++){
		for(int j=0;j<N;j++)
			fprintf(fp,"%d\t",matrix[i][j]);
		fprintf(fp,"\n");
	}
	fclose(fp);
}














