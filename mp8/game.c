
/*
MP8
Young Bin Jo
This mp slides the adjacent cells which have same values. w indicates adjacent cells to combine and move up, s indicates move down, a indicates move left, d indicates move right 
Initially I made a game board with -1 for every cell which shows they are empty. For get cell part, I checked the boundaries of adjacent cells. If it is out of boundaries I returned NULL. If not
I returned specific point of cell. For sliding part, I followed the algorithm given in wiki page. w and s had different conditions. For the legal part, I followed the given algorithm. If there is a 
empty cell, return 1 or adjacent cells with same value. Otherwise return 0. The variable last_combined_row is used to check whether target cell is empty or not. In algorithm we seek for an non-empty cell
and combine with adjacent cell if they are equal
One issue that I faced was where to start a search point of a target. For w I started to search from top to bottom. For s I started to search
from bottom to top. This led me to initialized target variable as 0 for w and m-1 (bottom) for s. This works same as a and d
*/

#include "game.h"


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct

	mygame->rows = rows;
	mygame->cols = cols;
	mygame->score = 0;
	int m, n;
	for(m = 0; m < rows; m++){
		for(n = 0; n < cols; n++){
		mygame->cells[m*cols + n] = -1; //initialize all values to -1
		}
	}
    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
	(*_cur_game_ptr)->rows=new_rows;
	(*_cur_game_ptr)->cols=new_cols;
	(*_cur_game_ptr)->score=0;
	int m, n;
	for(m = 0; m < new_rows; m++){
		for(n = 0; n < new_cols; n++){
		(*_cur_game_ptr)->cells[m*new_cols + n] = -1; //initialize all values to -1
		}
	}

	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
	int cols;
	cols = cur_game->cols;
	cell *pointer;
	
	if(row < 0 || row > cur_game->rows+1 || col < 0 || col > cur_game->cols+1) // If it is out of boundaries it returns null
	{
		return NULL;
	}
	else
	{
		pointer = &(cur_game->cells[row*cols + col]); //return a pointer to the corresponding cell on the game
		return pointer;
	}


}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{	

	int m, rows;
	rows = cur_game -> rows;
	int n, cols;
	cols = cur_game -> cols;
	int valid_move;

	for(n = 0; n < cols; n++)
	{
		int last_combined = -1; //Reset last_combined_row

		for(m = 0; m < rows; m++) //For each of the M elements within this column
		{
			if(cur_game->cells[m*cols + n] != -1) //If the current row value is not empty
			{
				int target = 0;
				
				while(target < m)
				{
					if(cur_game->cells[target*cols + n] == -1)
					{
						break; //Find the first available target row (the smallest row value (in the current column) that is empty and is less than current row number
					}
					target++;
				}

				if(target < m) //Assuming target row is less than current row number
				{
					cur_game->cells[target*cols + n] = cur_game->cells[m*cols + n]; // Copy current row value into target row
					cur_game->cells[m*cols + n] = -1; //Clear current row contents
					valid_move = 1; //indicator that valid movement made
				}

				if(target-1 != last_combined) //If the row above target row is not equal to last_combined_row
				{
					if(cur_game->cells[(target-1)*cols + n] == cur_game->cells[target*cols + n]) //If the value in the row above target row is equal to target row value
					{
						cur_game->cells[(target-1)*cols + n] = cur_game->cells[(target-1)*cols + n] + cur_game->cells[target*cols + n]; //Row above target row value is assigned the sum
						cur_game->cells[target*cols + n] = -1; //Target row value is assigned as empty
						cur_game->score = cur_game->score + cur_game->cells[(target-1)*cols + n]; //last_combined_row is assigned as Row above target row
						last_combined = target-1;
						valid_move = 1; //indicator that valid movement made
					} 
				} 
			}
		}
	}

	if(valid_move == 1)
	{
		return 1; //Otherwise, return 1
	}
	else
	{
		return 0; //an invalid move and return 0
	}
}

int move_s(game * cur_game) //slide down
{
	int m, rows;
	rows = cur_game -> rows;
	int n, cols;
	cols = cur_game -> cols;
	int valid_move;

	for(n = 0; n < cols; n++)
	{

		int last_combined = -1;

		for(m = rows-1; m >= 0; m--) 
		{
			if(cur_game->cells[m*cols + n] != -1)
			{
				int target = rows-1;
				
				while(target > m)
				{
					if(cur_game->cells[target*cols + n] == -1)
					{
						break;
					}
					target--;
				}

				if(target > m)
				{
					cur_game->cells[target*cols + n] = cur_game->cells[m*cols + n];
					cur_game->cells[m*cols + n] = -1;
					valid_move = 1;
				}

				if(target+1 != last_combined)
				{
					if(cur_game->cells[(target+1)*cols + n] == cur_game->cells[target*cols + n])
					{
						cur_game->cells[(target+1)*cols + n] = cur_game->cells[(target+1)*cols + n] + cur_game->cells[target*cols + n];
						cur_game->cells[target*cols + n] = -1;
						cur_game->score = cur_game->score + cur_game->cells[(target+1)*cols + n];
						last_combined = target+1;
						valid_move = 1; 
					} 
				} 
			}
		}
	}

	if(valid_move == 1)
	{
	return 1;
	}
	else
	{
	return 0;
	}
}

int move_a(game * cur_game) //slide left
{
	int m, rows;
	rows = cur_game -> rows;
	int n, cols;
	cols = cur_game -> cols;
	int valid_move;


	for(m = 0; m < rows; m++)
	{

		int last_combined = -1; 

		for(n = 0; n < cols; n++) 
		{
			if(cur_game->cells[m*cols + n] != -1)
			{
				int target = 0;
				
				while(target < n)
				{
					if(cur_game->cells[m*cols + target] == -1)
					{
						break;
					}
					target++;
				}

				if(target < n) 
				{
					cur_game->cells[m*cols + target] = cur_game->cells[m*cols + n]; 
					cur_game->cells[m*cols + n] = -1; 
					valid_move = 1;
				}

				if(target-1 != last_combined) 
				{
					if(cur_game->cells[m*cols + (target-1)] == cur_game->cells[m*cols + target]) 
					{
						cur_game->cells[m*cols + (target-1)] = cur_game->cells[m*cols + (target-1)] + cur_game->cells[m*cols + target];
						cur_game->cells[m*cols + target] = -1;
						cur_game->score = cur_game->score + cur_game->cells[m*cols + (target-1)];
						last_combined = target-1;
						valid_move = 1;
					} 
				} 
			}
		}
	}

	if(valid_move == 1)
	{
	return 1;
	}
	else
	{
	return 0;
	}
}

int move_d(game * cur_game) //slide to the right
{
	int m, rows;
	rows = cur_game -> rows;
	int n, cols;
	cols = cur_game -> cols;
	int valid_move;

	for(m = 0; m < rows; m++)
	{

		int last_combined = -1; 

		for(n = cols-1; n >= 0; n--) 
		{
			if(cur_game->cells[m*cols + n] != -1)
			{
				int target = cols-1;
				
				while(target > n)
				{
					if(cur_game->cells[m*cols + target] == -1)
					{
						break;
					}
					target--;
				}

				if(target > n)
				{
					cur_game->cells[m*cols + target] = cur_game->cells[m*cols + n];
					cur_game->cells[m*cols + n] = -1; 
					valid_move = 1;
				}

				if(target+1 != last_combined)
				{
					if(cur_game->cells[m*cols + (target+1)] == cur_game->cells[m*cols + target])
					{
						cur_game->cells[m*cols + (target+1)] = cur_game->cells[m*cols + (target+1)] + cur_game->cells[m*cols + target];
						cur_game->cells[m*cols + target] = -1;
						cur_game->score = cur_game->score + cur_game->cells[m*cols + (target+1)];
						last_combined = target+1;
						valid_move = 1; 
					} 
				} 
			}
		}
	}

	if(valid_move == 1)
	{
	return 1;
	}
	else
	{
	return 0;
	}
}

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
// For this part, I initially checked the boundaries of neighbor cells and if it passes, I checked whether adjacent cells have same values or not
	int m, rows;
	int n, cols;
	rows = cur_game -> rows;
	cols = cur_game -> cols;

	for (m = 0; m < rows; m++){
		for (n = 0; n < cols; n++){

		if (cur_game->cells[m*cols + n] == -1){
		return 1; //returning 1 if any empty spaces remain
		}
		if (n-1 >= 0){
			if (cur_game->cells[m*cols+n] == cur_game->cells[m*cols + (n-1)]){
				return 1; //any 2 adjacent tiles have the same value
			}
		}
		if (n+1 < cols){
			if (cur_game->cells[m*cols+n] == cur_game->cells[m*cols + (n+1)]){
				return 1;
			}
		}
		if (m-1 >= 0){
			if (cur_game->cells[m*cols+n] == cur_game->cells[(m-1)*cols+n]){
			return 1;
			}
		}
		if (m+1 < rows){
			if (cur_game->cells[m*cols+n] == cur_game->cells[(m+1)*cols+n]){
			return 1;
			}
		}
	   }
	}
return 0; //Otherwise return 0
}

/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
