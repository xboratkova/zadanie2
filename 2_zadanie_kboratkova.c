#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
	unsigned int rows;
	unsigned int cols;
	float *elem;
}MAT;

#define ELEM(A,r,c) (A->elem[(A->cols)*c+r])

char mat_LU_decompose(MAT *a, MAT *l, MAT *u, int n) {
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
	
void nasobenie(MAT *l, MAT *u, MAT *nasobok, int n){
	int i,j,k;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			for(k = 0; k < n; k++){
				ELEM(nasobok, i, j) += ELEM(l, i, k)*ELEM(u, k ,j);
			}
		}
	}
}

int skuska(MAT *a, MAT *nasobok, int n){
	int i,j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			if(ELEM(a,i,j) != ELEM(nasobok,i,j)){
				return 0;
			}
		}
	}
	return 1;
}
	
void mat_unit(MAT *mat, int n){
	int i,j;
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			if(i==j) ELEM(mat, i, j)=1;
			else ELEM(mat, i ,j)=0;
		}
	}
}
void mat_random(MAT *mat, int n){
	int i,j;
	
	
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			ELEM(mat, i, j)= -1+(1-(-1))*((float)rand()/(float)(RAND_MAX));
		}
	}
}

void mat_print(MAT *mat, int n){
	int i, j;
	
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			if(ELEM(mat,i,j)<0) printf(" %.2f", ELEM(mat, i, j));
			else printf("  %.2f", ELEM(mat, i, j));
		}
		printf("\n");
	}
}
	int main(){
		MAT a, l, u;
		
		int i,j,n;
		
		srand(time(NULL));
		
		printf("Zadajte velkost matice nxn:");
		scanf("%d", &n);
		
		float pole[n*n], pole1[n*n], pole2[n*n];
		
		a.cols = n;
		u.cols = n;
		l.cols = n;
		
		a.rows = n;
		u.rows = n;
		l.rows = n;
		
		a.elem = pole;
		u.elem = pole1;
		l.elem = pole2;
		
		
		mat_random(&a,n);
			
		printf("Matica A:\n");
		mat_print(&a, n);
		
		mat_LU_decompose(&a, &l, &u, n);
			
		printf("Matica L:\n");
		mat_print(&l,n);
		
		printf("Matica U:\n");
		mat_print(&u,n);
		
		MAT nasobok;
		nasobok.cols = n;
		nasobok.rows = n;
		float pole3[n*n];
		nasobok.elem = pole3;
		
		nasobenie(&l, &u, &nasobok, n);
		
		printf("Nasobenie L a U:\n");
		mat_print(&nasobok, n);
		
		if(skuska(&a, &nasobok, n)==1)
			printf("Nasobok LU je zhodny s maticou A\n");
		else 
			printf("Nasbok LU nie je zhodny s maticou A, niekde nastala chyba\n");
			

	}
	

