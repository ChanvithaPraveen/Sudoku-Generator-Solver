#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>
using namespace std;

//declare 2D array to track a copy of the generated puzzle
int backup_sudoku_array[9][9];
//declare temporary array make the code easy 
int temporary_sudoku_array[9][9];


/*
Function name : copy_array
Description : function for copying content from one array to another
Input parameters: array1[9][9] - hold the array to which copying is done
				  array2[9][9] - hold the array from which copying is done
return type: none
*/
void copy_array(int array_one[9][9], int array_two[9][9]) 
{
	for (int i = 0;i < 9;i++) 
	{
		for (int j = 0;j < 9;j++) 
		{
			array_one[i][j] = array_two[i][j];
		}
	}
}

void fill_box(int array[][9], int row, int col);
using namespace std;

/*
Function name : generate_random_number
Description : function for generating a random number
Input parameters: none
return type: integer random number
*/
int generate_random_number()
{
	srand(time(0));
	return (rand() % 9 + 1);
}


/*
Function name : remove_numbers
Description : function for removing some randome numbers according to the hardness
Input parameters: array[9][9] - array
				  remove_number_count - hardness level
return type: none
*/
void remove_numbers(int array[9][9], int remove_number_count)
{
	for (int i = 0; i < 9; i++)
	{
		int count = remove_number_count;
		while (count != 0)
		{
			int j = generate_random_number();
			if (array[i][j] != 0)
			{
				array[i][j] = 0;
				count--;
			}
		}
	}	
}


/*
Function name : display_puzzle
Description : function for display the puzzle content
Input parameters: array[9][9] - two dimensional array
return type: none
*/
void display_puzzle(int array[9][9]) 
{
	for (int i = 0;i < 9;i++) {

		cout << "| ";
		for (int j = 0;j < 9;j++) 
		{
			cout << array[i][j];
			cout << " | ";
		}
		cout << endl;
	}
}


/*
Function name : validity_in_row
Description : function for validating a given number that can be
			  placed in a row or not
Input parameters : array[][9] - two dimensional array
				   i - row index
				   number - number to check
return type: boolean
*/
bool validity_in_row(int array[][9], int i, int num) 
{
	for (int j = 0; j < 9;j++) 
	{
		if (array[i][j] == num)
			return false;
	}
	return true;
}


/*
Function name : validity_in_column
Description : function for validating a given number that can be
			  placed in a column or not
Input parameters : array[][9] - two dimensional array
				   j - row index
				   number - number to check
return type: boolean
*/
bool validity_in_column(int array[][9], int j, int num)
{
	for (int i = 0; i < 9;i++) 
	{
		if (array[i][j] == num)
			return false;
	}
	return true;
}


/*
Function name : validity_in_box
Description : function for validating a given number that can be 
			  placed in a 3 x 3 sub matrix or not
Input parameters : array[][9] - pointer to hold the two dimensional array
				   row_start - starting row index of the sub matrix
				   col_start - starting column index of the sub matrix
				   number - number to check
return type: boolean
*/
bool validity_in_box(int array[][9], int row_start, int col_start, int number) 
{
	//check validity in 3 X 3 sub matrix
	for (int i = 0;i < 3;i++) 
	{
		for (int j = 0;j < 3;j++) 
		{
			if ((array[row_start + i][col_start + j] == number)) 
			{
				return false;
			}
		}
	}
	return true;
}


/*
Function name : validity_in_cell
Description : function for validiting of a given number can be placed in a
			  given cell or not
Input parameters:
				array[][9] - two dimensional array
				i - row index
				j - column index
				num -  number to check
return type: boolean
*/
bool validity_in_cell(int array[][9], int i, int j, int num) {
	return (validity_in_row(array, i, num) &&
			validity_in_column(array, j, num) &&
			validity_in_box(array, i - i % 3, j - j % 3, num));
}


/*
Function name : fill_box
Description : function for fill a given 3 x 3 sub matrix with values
Input parameters:
				array[][9] - two dimensional array
				row - starting row index of sub matrix
				col -  starting column index of sub matrix
return type: none
*/
void fill_box(int array[][9], int row, int col)
{
	int num;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			do
			{
				num = generate_random_number();
			} 
			while (!validity_in_box(array, row, col, num));

			array[row + i][col + j] = num;
		}
	}
}


/*
Function name : fill_diagonal_boxes
Description : function for fill the sub arrays in main diagonal with values
Input parameters: array[][9] - pointer to hold the two dimensional array
return type: none
*/
void fill_diagonal_boxes(int array[][9]) 
{
	for (int i = 0;i < 9;i = i + 3)
	{
		fill_box(array, i, i);
	}		
}


/*
Function name : fill_remaining_cells
Description : function for fill all unfilled rest cells with values
Input parameters:
				array[][9] - two dimensional array
				i - row index
				j -  column index
return : boolean
*/
bool fill_remaining_cells(int array[][9], int i, int j) 
{
	if (j >= 9 && i < 9 - 1)
	{
		i = i + 1;
		j = 0;
	}

	if (i >= 9 && j >= 9)
		return true;

	if (i < 3)
	{
		if (j < 3)
			j = 3;
	}

	else if (i < 9 - 3)
	{
		if (j == (int)(i / 3) * 3)
			j = j + 3;
	}

	else
	{
		if (j == 9 - 3)
		{
			i = i + 1;
			j = 0;
			if (i >= 9)
				return true;
		}
	}

	for (int num = 1;num <= 9;num++) 
	{
		if (validity_in_cell(array, i, j, num)) 
		{
			array[i][j] = num;
			if (fill_remaining_cells(array, i, j + 1))
				return true;

			array[i][j] = 0;
		}
	}
	return false;
}


/*
Function name : solve_sudoko
Description : function for fill all unfilled rest cells with values
Input parameters:
				array[][9] - two dimensional array
				row - the row
				column - the column
return type: boolean
*/
bool solve_sudoko(int array[][9], int row, int col)
{
	/* Check if we have reached the 8th row and 9th column(0 indexed matrix),
	   we are returning true to avoid further backtracking*/
	if (row == 9 - 1 && col == 9)
		return true;

	/*Check if column value becomes 9, we move to next row and column start from 0*/
	if (col == 9) 
	{
		row++;
		col = 0;
	}

	/*Check if the current position of the grid already contains value >0, 
	  we iterate for next column*/
	if (array[row][col] > 0)
		return solve_sudoko(array, row, col + 1);

	for (int num = 1; num <= 9; num++)
	{
		/*Check if it is safe to place the num (1-9) in the given row ,
		  col ->we move to next column*/
		if (validity_in_cell(array, row, col, num))
		{
			/* Assigning the num in the current (row,col) position of the grid
				and assuming our assigned num in the position is correct*/
			array[row][col] = num;
			printf("\nsudoku_puzzle[%d][%d] is replaced by %d\n", row, col, num);
			display_puzzle(array);
			cout << "\n\n";

			// Checking for next possibility with next column
			if (solve_sudoko(array, row, col + 1)) 
			{
				return true;
			}
			else 
			{
				int n;
				cout << "\nThe solution is wrong.\nDo you want to start over the process?\n Otherwise solving process will be started from previous step\nStart over : 0\nPrevious step : Press any other key \nEnter:";
				cin >> n;
				if (n == 0) 
				{
					copy_array(temporary_sudoku_array, backup_sudoku_array);
					solve_sudoko(temporary_sudoku_array, 0, 0);
				}
			}
		}

		/*Removing the assigned num, since our assumption was wrong , and we go for
		  next assumption with diff num value*/

		array[row][col] = 0;
	}
	return false;
}


int main()
{
	int sudoku_puzzle[9][9];
	for (int i = 0;i < 9;i++)
	{
		for (int j = 0;j < 9;j++)
		{
			sudoku_puzzle[i][j] = 0;
		}
	}

	//get hardness level of the puzzle
	int input;
	cout << "**************SUDOKU PUZZLE***************";
	cout << "\n\n1 - Easy\t2 - Medium\t3 - Hard\n";
	cout << "Enter hardness level: ";
	cin >> input;
	cout << "\nPlease wait for generating the puzzle!!!\n\n";

	fill_diagonal_boxes(sudoku_puzzle);
	fill_remaining_cells(sudoku_puzzle, 0, 3);
	remove_numbers(sudoku_puzzle, input + 1);
	copy_array(backup_sudoku_array, sudoku_puzzle);
	display_puzzle(sudoku_puzzle);

	cout << "\n\nIf you want solve the generated puzzle press\n";
	cout << "1-Yes\t2-No\n";

	int x;
	cout << "Enter: ";
	cin >> x;
	if (x == 1) {
		//solve the generated puzzle
		if (solve_sudoko(sudoku_puzzle, 0, 0)) {
			cout << "\n\nFinal Solution Generated:\n";
			display_puzzle(sudoku_puzzle);
		}

		else cout << "No Solutions" << endl;
	}
	else return 0;


	return 0;
}



/*for (i = 0; i < 9; i++)
{
	for (j = i + 1;j < 9;j++)
	{
		if (array[i] == array[j])
		{
			cout << "\n" << array[i];
		}
	}
}
getch();*/

/*
for (i = 0; i < 9; i++)
{
	for (j = 0 ;j < 9;j++)
	{
		cout << " | " << array[j];
	}
	cout << " | " << endl;
}*/