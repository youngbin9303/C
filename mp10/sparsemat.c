/* Young Bin Jo
This mp asked to add mult sparsematrix. For the first part, code is very similar to previous mp where it reads a file and scan the numbers in
input_file. In addition, I am required to count non_zero element by seeking every element in a file. For second part, gv_tuples calculates the
value of given row and col. For add_tuples part, I checked whether matrixA and B had same row and column index to add the matrix. 
For mult_tuples part, I used our previous lab which did matrix multiplication. For save_tuples part, I used file I/O to create and write a file
to record the result. Lastly for destroy_tuples, I cleared memory to remove memory leakage. However, I did not finish set_tuples since I did not
fully understand the task.
*/




#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>


sp_tuples * load_tuples(char* input_file)
{

	FILE *f;

	int i, j;
	int non_zero = 0;
	
	if ((f = fopen(input_file, "r")) == NULL){ // if there is no file to read
			fprintf(stderr, "no file to read"); // Print error msg and return null
			return NULL;
		}

	sp_tuples * tuples = (sp_tuples*)malloc(sizeof(sp_tuples)); //allocate memory for structure of sp_tuples
	tuples -> tuples_head = NULL;

	fscanf(f, "%d %d\n", &(tuples->m), &(tuples->n)); // Two numbers on top are rows and columns of matrix
	
	for(i = 0; i < tuples->m; i++){	
		for(j = 0; j < tuples->n; j++){  
			if(gv_tuples(tuples, i, j) != 0){	// If gv_tuples gives non_zero value, increment non_zero variable
				non_zero++;
			}
		}
	}
	tuples->nz = non_zero;
	fclose(f);
    return tuples;
}

double gv_tuples(sp_tuples * mat_t,int row,int col)

{
	sp_tuples_node * current_node = mat_t->tuples_head;
	while (current_node != NULL){	// Until it reads the end of file
		if (current_node->row == row && current_node->col == col)	
			return current_node->value;	// return the value of a node
		current_node = current_node->next;	// If condition doesn't matches move to next node
	}
	return 0;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
	
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
	FILE *result=fopen(file_name, "w");		//make a file to store the result
		
		
	
	sp_tuples_node *node=mat_t->tuples_head;
	
	fprintf(result,"%d %d\n",mat_t->m,mat_t->n);	// Print row and columns
	while(node!=NULL)
	{
		fprintf(result,"%d %d %lf\n",node->row,node->col,node->value); // Print row col and value.
		node=node->next;
	}
	
	fclose(result);
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){


	if(matA->m == matB->m && matA->n == matB->n){	// If matA and B have same row index and column index
		sp_tuples * matC=(sp_tuples*)malloc(sizeof(sp_tuples));	// Give a memory space fro sp_tuples
		matC->m = matA->m;	// Set the row and column of matC same as maA
		matC->n = matA->n;
		matC->nz = 0;		// initialize non_zero to 0.


	int i, j;
	int non_zero = 0;

	for(i = 0; i < matC->m; i++){ // row
		for(j = 0; j < matC->n; j++){ // col
			if((gv_tuples(matA, i, j) + gv_tuples(matB, i, j)) != 0.00){	// If added value is non_zero
				non_zero++;	// increment non_zero variable
			}
		}
	}
	matC->nz = non_zero;	// Set nonzero to the variable non_zero

	return matC;
	}
	else 			// if m of matA and matB are different or n of matA and matB are different we cant add matrix.
	return NULL;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 

	if(matA->n == matB->m){	// If row of matA and col of matB are equal
		sp_tuples *matC=(sp_tuples*)malloc(sizeof(sp_tuples));
		matC->m=matA->m;
		matC->n=matB->n;
		matC->nz=0;

	int i, j, k;
	double mult_result;
	int non_zero = 0;

	for(k = 0; k < matC->m; k++){
		for(j = 0; j < matC->n; j++){			
			for(i = 0; i < matA->n; i++){
					mult_result += gv_tuples(matA, k, i) * gv_tuples(matA, i, j);	//Follow the previous lab about matrix multiplication			
			}
			if(mult_result != 0.00){
				non_zero++;
			}
		}
	}
	matC->nz = non_zero;
	return matC;
}
	else 			
	return NULL;
}



	
void destroy_tuples(sp_tuples * mat_t){
	
    sp_tuples_node *current_node=mat_t->tuples_head;	
	sp_tuples_node *previous_node;
		while(current_node!=NULL)
		{
			previous_node=current_node;
			current_node=current_node->next;
			free(previous_node); //Free every node by seeking head to last one
		}
		free(mat_t);  //Free sp_tuples memory
}  



