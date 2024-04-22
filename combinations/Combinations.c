#include <stdio.h>
#include <stdlib.h>

void init_numbers(int*,int,int*,int*,int*,int*);
void sort_array(int*,int);
int unique_number(int,int*);
void print_combinations(int*,int,int,int,int,int,int);
void locate_combinations(int,int*,int,int,int*,int,int,int*,int*,int**);
int is_valid(int*,int,int*,int*);

int main(int argc,char** argv){
	int N,X1,X2,Y1,Y2,S;
	int* numbers;
	do{
		printf("Enter amount of numbers [6-49]: ");
		scanf("%d",&N);
	}while((N>49) || (N<6));
	numbers = (int*)malloc(N*sizeof(int));
	init_numbers(numbers,N,&X1,&X2,&Y1,&Y2);
	
	sort_array(numbers,N);
	
	printf("Enter combinations [Default = 6]: ");
	scanf("%d",&S);
	if(S>N || S<1){
		printf("Incorrect number of combinations\nValue is set to default.\n");
		S = 6;
	}
	printf("*\n*\n*");
	print_combinations(numbers,N,X1,X2,Y1,Y2,S);
	
	free(numbers);
	return 0;
}


void init_numbers(int* numbers,int N,int* X1,int* X2,int* Y1,int* Y2){
	int* spare_numbers = (int*)malloc(49*sizeof(int));
	
	for(int i=0;i<49;i++)
		*(spare_numbers+i) = i+1;
	
	printf("----------------- Insert  numbers -----------------\n");
	for(int i=0;i<N;i++){
		do{
			printf("Enter number %d [1-49]: ",i+1);
			scanf("%d",(numbers+i));
		}while(!unique_number(*(numbers+i),spare_numbers) || *(numbers+i) == 0); 
	}
	// Βάζω την δεύτερη συνθήκη γιατί στο spare_numbers ότι αριθμός χρησιμοποιείται παίρνει την τιμή 0
	
	printf("---------- Select amount of even numbers ----------\n");
	do{
		printf("Enter lower value [0-6]: ");
		scanf("%d",X1);
		printf("Enter upper value [%d-6]: ",*X1);
		scanf("%d",X2);
	}while((*X1 > *X2) || ((*X1+*X2)<0) || ((*X1+*X2) > 12));
	
	printf("------------------ Select limits ------------------\n");
	
	do{
		printf("Enter lower limit [21-279]: ");
		scanf("%d",Y1);
		printf("Enter upper limit [%d-279]: ",*Y1);
		scanf("%d",Y2);
	}while((*Y1 > *Y2) || ((*Y1+*Y2)<42) || ((*Y1+*Y2) > 558));
	
	free(spare_numbers);
}

void sort_array(int* numbers,int N){
	int temp;
	for(int i=0;i<N;i++)
		for(int j=i;j<N;j++){
			if(*(numbers+i) > *(numbers+j)){
					temp = *(numbers+j);
					*(numbers+j) = *(numbers+i);
					*(numbers+i) = temp;
			}
		}
}

int unique_number(int number,int* spare_numbers){
	for(int i=0;i<49;i++)
		if(number == *(spare_numbers+i)){
			*(spare_numbers+i) = 0;
			return 1;
		}
	return 0;
}

void print_combinations(int* numbers,int N,int X1,int X2,int Y1,int Y2,int S){
	int* history = (int*)malloc(S*sizeof(int));
	
	// Βάζουμε σε έναν πίνακα τις τιμές X1,X2,Y1,Y2
	int* limitations = (int*)malloc(4*sizeof(int));
	*(limitations+0) = X1;
	*(limitations+1) = X2;
	*(limitations+2) = Y1;
	*(limitations+3) = Y2;
	
	/* 
	 * O Πίνακας που θα έχει τα στατιστικά συνδιασμών που τυπώθηκαν & δεν τυπώθηκαν
	 * stats[0] = Πλήθος συνδιασμών των Ν αριθμών ανά 6
	 * stats[1] = Πλήθος συνδιασμών που δεν πληρούσαν τον πρώτο όρο
	 * stats[2] = Πλήθος συνδιασμών που πληρούσαν τον πρώτο αλλά όχι τον δεύτερο
	 * stats[3] = Πλήθος συνδιασμών που τυπώθηκαν
	 */
	int* stats = (int*)malloc(4*sizeof(int));
	for(int i=0;i<4;i++)
		*(stats+i) = 0;
	
	
	// Οι αριθμοί που διάλεξε ο χρήστης.
	int** selected_numbers = (int**)malloc(N*sizeof(int*));
	for(int i=0;i<N;i++)
		*(selected_numbers+i) = (int*)malloc(2*sizeof(int));
	for(int i=0;i<N;i++){
		*(*(selected_numbers+i)) = *(numbers+i);
		*(*(selected_numbers+i)+1) = 0;
	}	
	locate_combinations(0,numbers,N,S,history,0,0,limitations,stats,selected_numbers);
	
	printf("\n*\n*\n*\n");
	printf("Total combinations of %d numbers per %d sets: %d\n",N,S,*(stats+0));
	printf("Combinations with wrong amount of even numbers: %d\n",*(stats+1));
	printf("Combinations with correct evens but wrong total: %d\n",*(stats+2));
	printf("Successful combinations: %d\n",*(stats+3));
	printf("*\n*\n*\n");
	for(int i=0;i<N;i++)
		printf("\'%d\' repeats: %d times\n",*(*(selected_numbers+i)),*(*(selected_numbers+i)+1));

	for(int i=0;i<N;i++)
		free(*(selected_numbers+i));
	free(selected_numbers);
	free(stats);
	free(limitations);
	free(history);
}

void locate_combinations(int base,int* numbers,int N,int S,int* history,int history_length,int id,int* limitations,int* stats,int** selected_numbers){
	if(S==1){
		// Στο tmp_arr αποθηκεύεται ο προσωρινός αριθμός
		int* tmp_arr = (int*)malloc((history_length+1)*sizeof(int));
		for(int j=base;j<N;j++){
			for(int i=0;i<history_length;i++)
					*(tmp_arr+i) = *(history+i);
			*(tmp_arr+history_length) = *(numbers+j);
			
			// Το history_length+1 μας δίνει επίσης τον αριθμό επιλογών του χρήστη
			if(is_valid(tmp_arr,history_length+1,limitations,stats)){
				printf("\n");	
				for(int i=0;i<N;i++){ 
					for(int j=0;j<=history_length;j++){
						if(*(*(selected_numbers+i)) == *(tmp_arr+j))
							(*(*(selected_numbers+i)+1)) += 1;
						
						// Αν το στοιχείο που εξετάζεται είναι μεγαλύτερο του στοιχείου selected_numbers κάνε break
						// γιατί ο πίνακας είναι ταξινομημένος
						if(*(*(selected_numbers+i)) < *(tmp_arr+j)) 
							break;
					}
				}
				for(int i=0;i<=history_length;i++)
					printf("%d ",*(tmp_arr+i));
			}
		}
	free(tmp_arr);	
	}else{
		history_length++;
		for(int i=base;i<=N-S;i++){
			*(history+id) = *(numbers+i);
			locate_combinations(i+1,numbers,N,S-1,history,history_length,id+1,limitations,stats,selected_numbers);
		}
	}
}

int is_valid(int* tmp_arr,int length,int* limitations,int* stats){
	int sum,even,flag,wrong_evens,wrong_sum,approved;
	wrong_evens = wrong_sum = sum = even = 0;
	approved = 1;
	
	// Μετράμε άρτιους & άθροισμα 
	for(int i=0;i<length;i++){
		if(*(tmp_arr+i)%2 == 0)
			even++;
		sum+= *(tmp_arr+i);
	}
	if((even<*(limitations)) || (even>*(limitations+1))){
		*(stats+1)+=1;
		approved = 0;
		wrong_evens = 1;
	}

	if((sum<*(limitations+2)) || (sum>*(limitations+3))){
		wrong_sum = 1;
		approved = 0;
	}
	
	// Περνάει τον πρώτο έλεγχο αλλά όχι τον δεύτερο
	if(!wrong_evens && wrong_sum)
		*(stats+2)+=1;
	
	if(approved)
		*(stats+3)+=1;
	
	*(stats)+=1;
	return approved;
}

















