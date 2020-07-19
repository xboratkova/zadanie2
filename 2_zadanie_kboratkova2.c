
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
	unsigned int rows;
	unsigned int cols;
	float *elem;
}MAT;

#define ELEM(A,r,c) (A->elem[(A->cols)*c+r])

char mat_LU_decompose(MAT *a, MAT *l, MAT *u) {
	int i,j,k;
	for(i = 0; i < a->cols; i++){
		for(j = 0; j < a->rows; j++){
			if(j < i)
				ELEM(l,j,i) = 0;
			else {
				ELEM(l,j,i) = ELEM(a,j,i);
				for(k = 0; k < i; k++){
					ELEM(l,j,i) = ELEM(l,j,i) - ELEM(l,j,k) * ELEM(u,k,i);
				}
			}
		}
		for(j = 0; j < a->rows; j++){
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
	
void nasobenie(MAT *l, MAT *u, MAT *nasobok){
	int i,j,k;
	for(i = 0; i < l->rows; i++){
		for(j = 0; j < l->cols; j++){
			for(k = 0; k < l->rows; k++){
				ELEM(nasobok, i, j) += ELEM(l, i, k)*ELEM(u, k ,j);
			}
		}
	}
}

int skuska(MAT *a, MAT *nasobok){
	int i,j;
	for(i = 0; i < a->rows; i++){
		for(j = 0; j < a->cols; j++){
			if(ELEM(a,i,j) - ELEM(nasobok,i,j) > 0.0001){
				return 0;
			}
		}
	}
	return 1;
}
	
void mat_unit(MAT *mat){
	int i,j;
	for(i=0; i< mat->rows; i++){
		for(j=0; j< mat->cols; j++){
			if(i==j) ELEM(mat, i, j)=1;
			else ELEM(mat, i ,j)=0;
		}
	}
}
void mat_random(MAT *mat){
	int i,j;
	
	
	for(i=0; i< mat->cols; i++){
		for(j=0; j< mat->rows; j++){
			ELEM(mat, i, j)= -1+(1-(-1))*((float)rand()/(float)(RAND_MAX));
		}
	}
}

void mat_print(MAT *mat){
	int i, j;
	
	for(i=0; i< mat->rows; i++){
		for(j=0; j< mat->cols; j++){
			if(ELEM(mat,i,j)<0) printf(" %.2f", ELEM(mat, i, j));
			else printf("  %.2f", ELEM(mat, i, j));
		}
		printf("\n");
	}
}

MAT *mat_create_with_type(int n){
	MAT *mat = malloc(sizeof(MAT));
	
	if(mat == NULL) return NULL;
	
	mat->rows = n;
	mat->cols = n;
	
	if((mat->elem = malloc(sizeof(float)*n*n)) == NULL){
		free(mat);
		return NULL;
		
	}
return mat;
}

void mat_destroy(MAT *mat){
	free(mat);
	free(mat->elem);
}

	int main(){
		MAT *a, *l, *u;
		
		int i,j,n;
		
		srand(time(NULL));
		
		printf("Zadajte velkost matice nxn:");
		scanf("%d", &n);
		
		
		a = mat_create_with_type(n);
		l = mat_create_with_type(n);
	    u = mat_create_with_type(n);
		
		mat_random(a);
			
		printf("Matica A:\n");
		mat_print(a);
		
		mat_LU_decompose(a, l, u);
			
		printf("Matica L:\n");
		mat_print(l);
		
		printf("Matica U:\n");
		mat_print(u);
		
		MAT *nasobok;
		nasobok = mat_create_with_type(n);
		
		nasobenie(l, u, nasobok);
		
		printf("Nasobenie L a U:\n");
		mat_print(nasobok);
		
		if((skuska(a, nasobok)) == 1)
			printf("Nasobok LU je zhodny s maticou A\n");
		else 
			printf("Nasbok LU nie je zhodny s maticou A, niekde nastala chyba\n");
			
	mat_destroy(a);
	mat_destroy(l);
	mat_destroy(u);
	mat_destroy(nasobok);
	
	return 0;
	}
	

