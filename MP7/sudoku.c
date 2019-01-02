/* Young Bin Jo
   
This mp solves 9*9 sudoku. For first part, I used for loop to check whether each row has correct value or not. If it has a correct value
I returned 1 for true. It did same work for second part. For third part, I divided 9*9 sudoku into 3*3. If I use two for loops from 0 to 8 for
row and col, it will count 9*9 sudoku. However, I used quotient (/) to set 0 to 2 as row_index and col_index 0 and used for loops from 0 to 2 
to count 3*3 sudoku section. for 3 to 5 quotient will give row_index and col_indext 1. I used sudoku[3*row_index + offset][3*col_index + offset]
to check next section of 3*3 sudoku. For last part, I used pseduo code in wiki to check whether sudoku is solved or not
*/




#include "sudoku.h"

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}

//-------------------------------------------------------------------------------------------------
// Start coding your MP here.
// ------------------------------------------------------------------------------------------------

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
	int j;
	for (j = 0; j < 9; j++)  // Check whether every element in a row has a value or not
	{ 
		if (sudoku[i][j] == val)
		return 1;
  	}
return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
	int i;
	for (i = 0; i < 9; i++)  // Check whether every element in a col has a value or not
	{
		if (sudoku[i][j] == val)
		return 1;
	}
return 0;


  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  assert(j>=0 && j<9);
  // BEG TODO
	int row_index = (i/3);   // This part will divide 9*9 sudoku into 3*3 section since i from 0 to 2 will give 0 and 3 to 5 will give 1
	int col_index = (j/3); // and 6 to 8 will give 2

	int row_offset, col_offset;
	
	for(row_offset = 0; row_offset < 3; row_offset++)
	{
		for(col_offset = 0; col_offset < 3; col_offset++)
		{
			if(sudoku[3*row_index + row_offset][3*col_index + col_offset] == val)
			{
				return 1;
			}
		}
	}
	return 0;

  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {
  if(is_val_in_row(val, i, sudoku)) return 0;
  if(is_val_in_col(val, j, sudoku)) return 0;
  if(is_val_in_3x3_zone(val, i, j, sudoku)) return 0;
  return 1;
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
	int x, y, i, j;
	int filled=1;


// Run all cells in sudoku map to check whether it is filled or not
// If it is filled return 1
	for (x = 0; x < 9; x++)
	{ 	 
		for(y = 0; y < 9; y++)
		{
			if (sudoku[x][y] == 0)  //sudoku[x][y] is empty
			{
				filled = 0; 	
				i = x;		
				j = y;
	  		}
		}
	}  

	if (filled != 0){
	return 1; // return true if all cells are assigned by number
}

// If there is an empty cell, find out which cell is empty 
	else{ 
	for (x = 0; x < 9; x++)
	{ 	 
		for(y = 0; y < 9; y++)
		{
			if (sudoku[x][y] == 0)  //sudoku[x][y] is empty
			{
				filled = 0; 	
				i = x;		
				j = y;
	  		}
		}
	}  

}
  int num;

  for (num = 1; num <= 9; num++){
	if (is_val_valid(num, i, j, sudoku)==1){	//if is_val_valid returns 1, certain cell can be filled with num
		sudoku[i][j] = num;	
		if (solve_sudoku(sudoku)){
			return 1;
		}
		sudoku[i][j] = 0; 
	}
  }
  return 0;
  // END TODO.
}



