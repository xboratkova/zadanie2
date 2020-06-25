#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
	unsigned int rows;
	unsigned int cols;
	float *elem;
}MAT;

#define ELEM(A,r,c) (A.elem[(A.cols)*r+c])

char LUdecomposition(MAT a, MAT l, MAT u, int n) {
	int i,j,k;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			if(j < i)
				ELEM(l,j,i) = 0;
			else {
				ELEM(l,j,i) = ELEM(a,j,i);
				for(k = 0; k < i; k++){
					ELEM(l,j,i) = ELEM(l,j,i) - ELEM(l,j,k) * ELEM(u,k,i);
				}
			}
		}
		for(j = 0; j < n; j++){
			if(j < i) 
				ELEM(u,i,j) = 0;
			else if (j == i)
					ELEM(u,i,j) = 1;
				else{
					ELEM(u,i,j) = ELEM(a,i,j) / ELEM(l,i,i);
					for(k = 0; k < i; k++){
						ELEM(u,i,j) = ELEM(u,i,j) - ((ELEM(l,i,k) * ELEM(u,k,j) / ELEM(l,i,i)));
					}
					
				}
				
			}
		}
	}
	
	int main(){
		MAT a, l, u;
		
		int i,j,n,s;
		
		printf("Zadajte velkost matice nxn:");
		scanf("%d", &n);
		
		int pole[n*n], pole1[n*n], pole2[n*n];
		
		a.cols = n;
		u.cols = n;
		l.cols = n;
		
		a.rows = n;
		u.rows = n;
		l.rows = n;
		
		a.elem = pole;
		u.elem = pole1;
		l.elem = pole2;
		
		printf("Zadajte, aka ma byt najvyssia mozna hodnota prkov v matici:");
		scanf("%d", &s);
		
		srand((unsigned int)time(NULL));
		
		for(i = 0; i < n; i++){
			for(j = 0; j < n; j++){
				ELEM(a,i,j) = ((float)rand()/(float)(RAND_MAX))*s;
			}
		}
		LUdecomposition(a, l, u, n);
			
		printf("Matica A:\n");
		for(i = 0; i < n; i++){
			for(j = 0; j < n; j++){
				printf("%.2f  ", ELEM(a,i,j));
			}
			printf("\n");
		}
			
		printf("Matica L:\n");
		for(i = 0; i < n; i++){
			for(j = 0; j < n; j++){
				printf("%.2f  ", ELEM(l,i,j));
			}
			printf("\n");
		}
		printf("Matica U:\n");
		for(i = 0; i < n; i++){
			for(j = 0; j < n; j++){
				printf("%.2f  ", ELEM(u,i,j));
			}
			printf("\n");
		}
	}
	

