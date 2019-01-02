//Function for generating three d6 rolls

#include <stdlib.h>
#include "dice.h"

// For rand()%6 it only gives values from 0 to 5 but we want values from 1 to 6 so I added 1 to rand()%6
void roll_three(int* one, int* two, int* three){

	*one = rand()%6 + 1;
	*two = rand()%6 + 1;
	*three = rand()%6 + 1;

}
