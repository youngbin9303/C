#include "sliding.h"
/*  Slide all values of array up
*/
void slide_up(int* my_array, int rows, int cols){

	int i, j;
	for(i = 0; i < cols; i++)
	{
		for(j = 1; j < rows; j++) //first spot doesn't need to be moved as it's already at the top
		{
			if(my_array[j*cols + i] != -1)
			{
				int k = 0;
				while(k < j)
				{
					if(my_array[k*cols + i] == -1)
					{
						break;
					}
					k++;
				}
				if(k < j) //move stuff
				{
					my_array[k*cols + i] = my_array[j*cols + i];
					my_array[j*cols + i] = -1; //clear it
				}
			}
		}
	}
	return;
}
