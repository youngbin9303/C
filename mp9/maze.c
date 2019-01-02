/* Young Bin Jo
This mp uses recursion to check the shortest distance from starting point to ending point. It checks 4 neighbor points (left right up and down).
For the first part, I used file I/O to open a maze file and check the width and height of the maze. After checking the size of the maze,
I used malloc to allocate memory address for every cell and the data of the cell. I used for loops to fill the maze and find the starting point
and ending point. I stored the index of starting point and ending point in struct. For second part, I cleared the data in the cell and cleared
cell and cleared the maze in order to remove and memory leakage. For third part, I just used for loops to create the maze and give character
to every cell in the maze.
For solveMazeManhattanDFS I initially followed the algorithm given in wiki page. Some added some parts from algorithm. I realized that I have
to use for loops to check every possible manhattan distance since it has 4 possible starting points (left right up and down). Also I setted
used manhattan distance to 100 after checking the condition since this can bring two starting points if manhattan distance for left and right are
same. By setting used distance to 100, it can prevent having two starting points in one maze. For the given example, maze3.txt had the largest
width and height which are 51. However, I setted manhattan distance modified as 10000 since other maze  could have bigger row and column number.
*/



#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
	FILE *f;

	int i, j, k;

	if ((f = fopen(fileName, "r")) == NULL){ // if there is no file to read
			fprintf(stderr, "no file to read"); // Print error msg and return null
			return NULL;
		}
	maze_t * maze = malloc(sizeof(maze_t)); //memory allocation for maze

	fscanf(f, "%d %d\n", &(maze->width), &(maze->height)); //first integer of the file is maze-width and second integer of the file is maze-height
 
	maze->cells = (char**)malloc(maze->height*sizeof(char*)); //allocate memory for height
	
	for(k = 0; k < maze->height; k++)
	{
	maze->cells[k] = (char*)malloc(maze->width*sizeof(char)); //For every element in height allocate memory for rows
	}
 
	char maze_wall;
	 
	for (i = 0; i < maze->height; i++)
	{
        	for (j = 0; j < maze->width + 1; j++)
           	{
			maze_wall = fgetc(f);

			if(maze_wall != '\n')	// Unless it is new line (end of column)
			{	
				maze->cells[i][j] = maze_wall; //fill in the cells

				if(maze->cells[i][j] == 'S') //If the certain cell is starting point store the i and j of the point as startRow and startColumn
				{
					maze->startRow = i; 
					maze->startColumn = j;
				}
				if(maze->cells[i][j] == 'E') //If the certain cell is ending point store the i and j of the point as startRow and startColumn
				{
					maze->endRow = i;
					maze->endColumn = j;
				}
			}
		}
	}	 	
	

	fclose(f);	
	
	return maze;
}	

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
	int i;
	for (i=0; i < maze->height; i++){
	free(maze->cells[i]);	// Free every data in cell
	}
	free(maze->cells);	// Free cell itself
		
	free(maze);		// Free maze
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
	int m, n;
		for (m = 0; m < maze->height; m++){
			for (n = 0; n < maze->width; n++){
				 printf("%c", maze->cells[m][n]);	//For every cell in maze, fill character
			}
			printf("\n");
		}
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search and a manhattan distance heuristic
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeManhattanDFS(maze_t * maze, int col, int row)
{

	int i;
	int man_heu_1 = abs(row - maze->endRow) + abs((col - 1) - maze->endColumn);
	int man_heu_2 = abs(row - maze->endRow) + abs((col + 1) - maze->endColumn);
	int man_heu_3 = abs((row - 1) - maze->endRow) + abs(col - maze->endColumn);
	int man_heu_4 = abs((row + 1) - maze->endRow) + abs(col - maze->endColumn);
	int man_heu_modified = 10000; // This will be used to prevent two manhattan distance being equal which will prevent a maze having two starting point. 



	if (col < 0 || col > maze->width || row < 0 || row > maze->height) // If (col, row) outside bounds of the maze return false
		return 0;
	if (maze->cells[row][col] == '%' || maze->cells[row][col] == '~' || maze->cells[row][col] == '.') // if (col, row) is not an empty cell return false
		return 0;
	if (maze->cells[row][col] == 'E') // if (col, row) is the end of the maze return true
		return 1;
	maze->cells[row][col] = '.'; // set (col, row) as part of the solution path in the maze
	
	for(i = 0; i < 4; i++) // We need to run loop 4 times to check every distance since there are 4 possible lengths 
	{
		if(man_heu_1 <= man_heu_2 && man_heu_1 <= man_heu_3 && man_heu_1 <= man_heu_4)  

		{
			if(solveMazeManhattanDFS(maze, (col - 1), row) == 1) //if (solveMaze(left of (col, row) ) == true) return true
			{
				maze->cells[maze->startRow][maze->startColumn] = 'S'; // and set that point as a starting point
				return 1;
			}
			man_heu_1 = man_heu_modified; // Remove possiblity of two manhattan distances having same length which will bring only one starting point
		}
		if(man_heu_2 <= man_heu_1 && man_heu_2 <= man_heu_3 && man_heu_2 <= man_heu_4)	//
		{		
			if(solveMazeManhattanDFS(maze, (col + 1), row) == 1) //if (solveMaze(right of (col, row) ) == true) return true

			{
				maze->cells[maze->startRow][maze->startColumn] = 'S';
				return 1;
			}
			man_heu_2 = man_heu_modified;	
		}
		if(man_heu_3 <= man_heu_1 && man_heu_3 <= man_heu_2 && man_heu_3 <= man_heu_4)
		{		
			if(solveMazeManhattanDFS(maze, col, (row - 1)) == 1) //if (solveMaze(up of (col, row) ) == true) return true

			{
				maze->cells[maze->startRow][maze->startColumn] = 'S';
				return 1;
			}
			man_heu_3 = man_heu_modified;			
		}
		if(man_heu_4 <= man_heu_1 && man_heu_4 <= man_heu_2 && man_heu_4 <= man_heu_3)
		{			
			if(solveMazeManhattanDFS(maze, col, (row + 1)) == 1) //if (solveMaze(down of (col, row) ) == true) return true

			{
				maze->cells[maze->startRow][maze->startColumn] = 'S';				
				return 1;
			}
			man_heu_4 = man_heu_modified;
		}
	}		 
	
	maze->cells[row][col] = '~'; //unmark (col, row) as part of solution and mark as visited

	return 0; //return false

}
