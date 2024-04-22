#include <stdio.h>

void TowersOfHanoi(int,char,char,char);

int main(int argc,char** argv){
	int N;
	printf("Enter number N: ");
	scanf("%d",&N);
	TowersOfHanoi(N,'A','C','B');
}

void TowersOfHanoi(int N,char source,char dest,char aux){
if(N == 1){
	printf("%d goes from %c to %c\n",N,source,dest);
	return;
}
TowersOfHanoi(N-1,source,aux,dest);
printf("%d goes from %c to %c\n",N,source,dest);
TowersOfHanoi(N-1,aux,dest,source);
}

