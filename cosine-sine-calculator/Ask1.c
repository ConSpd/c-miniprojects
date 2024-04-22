#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int checkSimilarity(double,double);
double degToRad(double);
double myCos(double);
double mySin(double);
void menu();


int main(int argc,char** argv){
	menu();
	return 0;
}

void menu(){
	double angle,rad,sine,cosine;
	system("clear");
	printf("Enter angle in degrees: ");
	scanf("%lf",&angle);

	rad = degToRad(angle);
	sine = mySin(rad);
	cosine = myCos(rad);
	
	printf("Sin = %lf, Cos = %lf\n",sine,cosine);
	double cSin,cCos;
	cSin = sin(rad);
	cCos = cos(rad);

	if(checkSimilarity(sine,cSin))
		printf("My function sine   is identical to C's sine function: %lf\n",cSin);
	else
		printf("My function sine   is NOT identical to C's sine function: %lf\n",cSin);

	if(checkSimilarity(cosine,cCos))
		printf("My function cosine is identical to C's cosine function: %lf\n",cCos);
	else
		printf("My function cosine is NOT identical to C's cosine function: %lf\n",cCos);
	
}


double mySin(double rad){
	double old_k,new_k,sin_res,res;
	int factorial = 1;
	int turn = 1;
	sin_res = new_k = rad;
	do{
		old_k = new_k;
		new_k = old_k * ((rad*rad)/ ((factorial+1)*(factorial+2)));
		factorial += 2;
		if(turn){
			sin_res = sin_res - new_k;
			turn = 0;
		}else{
			sin_res = sin_res + new_k;
			turn = 1;
		}
		res = old_k-new_k;
		if(res<0)
			res *= -1;
	}while(res>0.000001);
return sin_res;
}


double myCos(double rad){
	double old_k,new_k,cos_res,res;
	int factorial = 0;
	int turn = 1;
	cos_res = new_k = 1;
	do{
		old_k = new_k;
		new_k = old_k * ((rad*rad)/ ((factorial+1)*(factorial+2)));
		factorial += 2;
		if(turn){
			cos_res = cos_res - new_k;
			turn = 0;
		}else{
			cos_res = cos_res + new_k;
			turn = 1;
		}
		res = old_k-new_k;
		if(res<0)
			res *= -1;
	}while(res>0.000001);
return cos_res;
}


double degToRad(double angle){
	double rad;
	while(angle>=360)
		angle -= 360;
	rad = (angle*3.14159)/180;
	return rad;
}


int checkSimilarity(double deg1,double deg2){
	double differ;
	differ = deg1 - deg2;
	if(differ<0)
		differ*=-1;
	if(differ>0.0000001)
		return 0;
	else
		return 1;
}
