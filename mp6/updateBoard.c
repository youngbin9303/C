
/*
MP6
Young Bin Jo
This mp counts the number of alive neighbor cells and change the current cell based on the number of cells. For first part, I checked the number of neighbor cells 
using boundary check. If the left right top or bottom neighbor cell is out of boundary, I ignored it. If not, I check whether neighbor cell is alive or not. If it is alive, I
incremented neighbor. Given instruction said 0 shows dead cell, 1 shows alive cell. However, I used 2 and 3. 2 represents dead cell which changes to alive cell in next step
because it has 3 alive neighbors. 3 represents alive cell which changes to dead cell in next step due to over or underpopulated. It was required to use 2 and 3 because when I am
updating the board, it uses original version of the gameboard, not the modified version. For second part, I used loops to update the board for every cell. However, if dead cell
changes to alive cell, I used 2 not 1 and 3 not 0 for alive cell changing to dead cell. After running whole loop, I used another loop to change 2 to 1 and 3 to 0 which finally
update the board. For last part, I declared variable a which is used to check whether cell changes or not. If a is bigger than 0, it means board changed which returns 0.
*/


/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
int neighbor = 0;
// This part checks the number of alive neighbor cells. 1 means alive cell. 3 means an alive cell which will change to dead cell during next step.
// If specific neighbor cell is out of boundaries, it is ignored.

	if (col - 1 >= 0 && ((board[(col - 1) + row*boardColSize] == 1)||(board[(col - 1) + row*boardColSize] == 3)))
		neighbor++;
	if (col + 1 < boardColSize && ((board[(col + 1) + row*boardColSize] == 1)||(board[(col + 1) + row*boardColSize] == 3)))
		neighbor++;
	if (row - 1 >= 0 && ((board[col + (row - 1)*boardColSize] == 1)||(board[col + (row - 1)*boardColSize] == 3)))
		neighbor++;
	if (row + 1 < boardRowSize && ((board[col + (row + 1)*boardColSize] == 1)||(board[col + (row + 1)*boardColSize] == 3)))
		neighbor++;
	if (col - 1 >= 0 && row - 1 >= 0 && ((board[(col - 1) + (row - 1)*boardColSize] == 1)||(board[(col - 1) + (row - 1)*boardColSize] == 3)))
		neighbor++;
	if (col + 1 < boardColSize && row - 1 >= 0 && ((board[(col + 1) + (row - 1)*boardColSize] == 1)||(board[(col + 1) + (row - 1)*boardColSize] == 3)))
		neighbor++;
	if (col - 1 >= 0 && row + 1 < boardRowSize && ((board[(col - 1) + (row + 1)*boardColSize] == 1)||(board[(col - 1) + (row + 1)*boardColSize] == 3)))
		neighbor++;
	if (col + 1 < boardColSize && row + 1 < boardRowSize && ((board[(col + 1) + (row + 1)*boardColSize] == 1)||(board[(col + 1) + (row + 1)*boardColSize] == 3)))
		neighbor++;
	else{ 
		neighbor = neighbor;
	}

	return neighbor;
}	

/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
int i=0;
int j=0;

// This part, I used two for loops to check all cells in the board whether it changes or not. 
// If it changes I used either 2 or 3 for loops and after loops are done, I changed 2 to 1 and 3 to 0

	for(i=0;i<boardRowSize;i++){
		for(j=0;j<boardColSize;j++){

	if (board[i*boardColSize + j] == 1 && (countLiveNeighbor(board, boardRowSize, boardColSize, i, j)) == 2){
		board[i*boardColSize + j] = 1;
	}
	if (board[i*boardColSize + j] == 1 && (countLiveNeighbor(board, boardRowSize, boardColSize, i, j)) == 3){
		board[i*boardColSize + j] = 1;
	}
	if (board[i*boardColSize + j] == 0 && (countLiveNeighbor(board, boardRowSize, boardColSize, i, j)) == 3){
		board[i*boardColSize + j] = 2;
		
	}
	if (board[i*boardColSize + j] == 0 && (countLiveNeighbor(board, boardRowSize, boardColSize, i, j)) != 3){
		board[i*boardColSize + j] = 0;
	}
	if (board[i*boardColSize + j] == 1 && (countLiveNeighbor(board, boardRowSize, boardColSize, i, j)) != 2 && (countLiveNeighbor(board, boardRowSize, boardColSize, i, j)) != 3 ){
		board[i*boardColSize + j] = 3;
	}

	}
}
	for(i=0; i<boardRowSize*boardColSize;i++){
	
	if(board[i]==2){
		board[i]=1;

	}
	if(board[i]==3){
		board[i]=0;
	}

}
}
/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
// if 2 dead->live if 3 live -> dead
int aliveStable(int* board, int boardRowSize, int boardColSize){
int i=0;
int j=0;
int a=0;

// This part I did samething as part2. However, I declared another variable a which will indicate whether board changes or not. I incremented a whenever cell changes next step.
// After loops, when a is bigger than zero, I returned 0 to show that board changes next step. If a is not bigger than zero, it means board didn't change for next step. 
// Therefore I returned 1.


	for(i=0;i<boardRowSize;i++){
		for(j=0;j<boardColSize;j++){

	if (board[i*boardColSize + j] == 1 && (countLiveNeighbor(board, boardRowSize, boardColSize, i, j)) == 2){
		a = a;
	}
	if (board[i*boardColSize + j] == 1 && (countLiveNeighbor(board, boardRowSize, boardColSize, i, j)) == 3){
		a = a;
	}
	if (board[i*boardColSize + j] == 0 && (countLiveNeighbor(board, boardRowSize, boardColSize, i, j)) == 3){
		a++;
		
	}
	if (board[i*boardColSize + j] == 0 && (countLiveNeighbor(board, boardRowSize, boardColSize, i, j)) != 3){
		a = a;
	}
	if (board[i*boardColSize + j] == 1 && (countLiveNeighbor(board, boardRowSize, boardColSize, i, j)) != 2 && (countLiveNeighbor(board, boardRowSize, boardColSize, i, j)) != 3 ){
		a++;
	}

	}
}
	if (a>0){
	return 0;
	}
	else
	return 1;
}
