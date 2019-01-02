/* Function matrix_multiply
 * matrixA, matrixB, and matrix C are matrices represented as
 * one-dimensional arrays in row-major order. This function must
 * preform matrix multiplication so that C=A*B. 
 * INPUT: matrixA, a one dimensional array of size m*k
 *        matrixB, a one dimensional double array of size k*n
 * OUTPUT: matrixC, a one dimensional double array of size m*n
 */
void matrix_multiply(double *matrixA,double *matrixB,double *matrixC,int m,int k,int n)
{
	//YOUR CODE HERE
		
	int a, b, c;

	for(a = 0; a < m; a++)
	{
		for(b = 0; b < n; b++)
		{
			for(c = 0; c < k; c++) 
			{
				matrixC[a*n + b] += matrixA[a*k + c]*matrixB[c*n + b];
			}
	
		}
	
	}
}


