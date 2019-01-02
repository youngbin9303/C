/*			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */

/*
Young Bin Jo
659575499
MP5
This MP uses srand to make a number to guess. After making the number to guess, we input 4 digits that we guess. If the number matches the position of four digits,
it increments perfect_matches. If the guessed number exist in four digits but doesn't matches position, it increments misplaced_matches. This repeats until we guess
an exact number. After wrong guess, guess_number is incremented. One issue I faced was that I did not consider same number used in a sequence. This brought me to increment
misplaced_matches more than it should be. As a solution, I gave two variables for each solution. One will be used to check whether number matches to perfect_matches condition.
Another one which is called counter will be used to check whether non-perfect_matches number is used in misplaced_matches condition. If this value is incremented, it won't be counted
again in future even if it appears in different position. For example if the seed is 12321, solution is 7 3 7 7. If input is 2 7 7 7, there are two perfect matches. However, second digit
7 is in w position. Therefore solution_w is 0 and counter_w is 0 during code of perfect_matches. However, when it goes to misplaced_matches, it increments misplaced_matches. If the input is 2 7 1 4 and I didn't setup misplaced_matches, it will bring 3 misplaced_matches because 7 in second digit counts toward first third and fourth digit. However, in my code, 7 works
only on first digit and it is ignored for third and fourth digit
*/

#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int
set_seed (const char seed_str[])
{
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//    We declare
//    int seed;
//    char post[2];
	int seed;
	char post[2];
//    The sscanf statement below reads the integer into seed. 
//    sscanf (seed_str, "%d%1s", &seed, post)
	
    if (sscanf (seed_str, "%d%1s", &seed, post) == 1)
    {
		srand(seed);
		return 1;
	}
	else
	{
		printf("set_seed: invalid seed\n");
		return 0; 
	}					
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below
 
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 0 and 7)
 *          *two -- the second solution value (between 0 and 7)
 *          *three -- the third solution value (between 0 and 7)
 *          *four -- the fourth solution value (between 0 and 7)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
    //your code here
    //Assign random number from 0 to 7 for *one *two *three and *four
    *one = rand()%8;	
    
    *two = rand()%8;
    
    *three = rand()%8;
    
    *four = rand()%8;
    
    //record the solution in the static solution variables initally declared beginning of the code
    solution1 = *one;
    solution2 = *two;
    solution3 = *three;
    solution4 = *four;
    
    //set guess_number to 1
    guess_number = 1;
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 0-7). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 0 and 7)
 *          *two -- the second guess value (between 0 and 7)
 *          *three -- the third guess value (between 0 and 7)
 *          *four -- the fourth color value (between 0 and 7)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 0 and 7), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int 
make_guess (const char guess_str[], int* one, int* two, int* three, int* four)
{
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four integers from guess_str into the integers and read anything else present into post
	
	char post[2];
	int w, x, y, z;		
	// Declare perfect_matches and misplaced_matches in global variables
	int perfect_matches = 0;	
	int misplaced_matches = 0;
	// solution variables are used to check whether it matches perfectly or not
	int solution_w = 0;
	int solution_x= 0;
	int solution_y= 0;
	int solution_z= 0;
	// counter variables are used to check whether non-perfect_match number is used misplaced_matches 
	int counter_w= 0;
	int counter_x= 0;
	int counter_y= 0;
	int counter_z= 0;

	if(sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post) == 4)
	{
		if(w < 8 && w >= 0 && x < 8 && x >= 0 && y < 8 && y >= 0 && z < 8 && z >= 0)
		{
			*one = w;
			*two = x;
			*three = y;
			*four = z;
	
			// For guessing part, I initially checked perfect_matches and after checked misplaced_matches		
			// Check whether each solution matches with assigned position.
			// I used two variables for each check point. solution_w,x,y,z indicates whether it is perfect matches or not. counter_w,x,y,z is used to check whether the solution is used in misplaced_matches.
			if(w == solution1)
			{
				perfect_matches++;
				solution_w = 1;
				counter_w = 1;
			}
			if(x == solution2)
			{
				perfect_matches++;
				solution_x = 1;
				counter_x = 1;
			}
			if(y == solution3)
			{
				perfect_matches++;
				solution_y = 1;
				counter_y = 1;
			}
			if(z == solution4)
			{
				perfect_matches++;
				solution_z = 1;
				counter_z = 1;
			}
			// If each solution doesn't match with assigned position, check whether the number is in different position.
			// If it is in different position increment misplaced_matches.
			// below statement tells if w is in solution2 position and w doesn't perfectly match in solution 1 and number w is not used in x position, increment misplaced_matches and counter_x
			
			// check whether answer w is in different position
			if (w == solution2 && solution_w != 1 && counter_x != 1)
			{
				misplaced_matches++;
				counter_x = 1;
			}
			else if (w == solution3 && solution_w != 1 && counter_y != 1)
			{
				misplaced_matches++;
				counter_y = 1;
			}
			else if (w == solution4 && solution_w != 1 && counter_z != 1)
			{
				misplaced_matches++;
				counter_z = 1;
			}
			// check whether answer x is in different position
			if (x == solution1 && solution_x != 1 && counter_w != 1)
			{
				misplaced_matches++;
				counter_w = 1;
			}
			else if (x == solution3 && solution_x != 1 && counter_y != 1)
			{
				misplaced_matches++;
				counter_y = 1;
			}
			else if (x == solution4 && solution_x != 1 && counter_z != 1)
			{
				misplaced_matches++;
				counter_z = 1;
			}
			// check whether answer y is in different position
			if (y == solution1 && solution_y != 1 && counter_w != 1)
			{
				misplaced_matches++;
				counter_w = 1;
			}
			else if (y == solution2 && solution_y != 1 && counter_x != 1)
			{
				misplaced_matches++;
				counter_x = 1;
			}
			else if (y == solution4 && solution_y != 1 && counter_z != 1)
			{
				misplaced_matches++;
				counter_z = 1;
			}
			// check whether answer z is in different position
			if (z == solution1 && solution_z != 1 && counter_w != 1)
			{
				misplaced_matches++;
				counter_w = 1;
			}
			else if (z == solution2 && solution_z != 1 && counter_x != 1)
			{
				misplaced_matches++;
				counter_x = 1;
			}
			else if (z == solution3 && solution_z != 1 && counter_y != 1)
			{
				misplaced_matches++;
				counter_y = 1;
			}
			// Print the message of my guess
			printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect_matches, misplaced_matches);
			guess_number++;
		}
		// If input is out of range 0 to 7 print error msg
		else
		{
			printf("make_guess: invalid guess\n");
			return 0;
		}	
	}	
	else
	{
		// If sscanf gives wrong value print error msg
		printf("make_guess: invalid guess\n");
		return 0;
	}
	return 1; 
}
	

//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 0-7. If so, it is a valid guess
//  Otherwise, it is invalid.  
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed




