///////////////////////////////////////////////////////////////
//
//             Ethan-John Rasmussen
//             CSCE 211, HW2 Pt 2.
//             March 9th, 2018.
//
///////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


const int HEIGHT = 40;
const int WIDTH = 40;
void fillBorders(char maze[][WIDTH]);
void printMaze(char maze[][WIDTH]);
void createMaze(char maze[][WIDTH], int upperCornerY, int upperCornerX, int areaHeight, int areaWidth);

// This function displays the maze, I have made it so it prints two characters for every X and SPACE to make the maze more square like.
// It's unlikely the ascii squares will work with visual studio and they will just show up as spaces. So I left some windows code in here to work with visual studio.
void printMaze(char maze[][WIDTH])
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			// Simple version.
			//cout << maze[y][x];
			
			// XCode code, unlikely to work with visual studio
			// This prints black squares
			// if (maze[y][x] == 'X')
			//	cout << "██";
			//else
			//	cout << "  ";
			
			// Windows code
			if (maze[y][x] == 'X')
				cout << "[]";
			else 
				cout << "  ";
			
		}
		cout << endl;
	}
}

// This function fills the borders of the two dimensional array with X's.
void fillBorders(char maze[][WIDTH])
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if ((j == 0) || (j == WIDTH - 1))
			{
				maze[i][j] = 'X';
			}
			else if ((i == 0) || (i == HEIGHT - 1))
			{
				maze[i][j] = 'X';
			}
			else
			{
				maze[i][j] = ' ';
			}
		}
	}
}
// This function takes the area of a two dimensional array and splits it in two at some arbritrary line, then it recursively calls itself on the two resulting areas until the base case is met.
// This function uses some functionality that works on mac but does not work properly on visual studio on windows. Please take note of comments.
void createMaze(char maze[][WIDTH], int upperCornerY, int upperCornerX, int areaHeight, int areaWidth)
{
	// Base case for recursion, if the area is 2 width or smaller then return.
	if ((areaWidth <= 2) || (areaHeight <= 2))
	{
		return;
	}
	//  If the height of the rectangle is greater than or equal to the width, create a horizontal line.
	if (areaHeight >= areaWidth)
	{
		// Range of y values to choose from is the width - 2 because we dont want to create parallel lines right next to eachother.
		int rangeY = areaHeight - 2;
		int wallY = upperCornerY + ((rand() % rangeY) + 1);

		// For loop to draw the horizontal line
		for (int x = upperCornerX; x < upperCornerX + areaWidth; x++)
		{
			maze[wallY][x] = 'X';
		}

		// Check for openings at the ends of the line just drawn, if there are any make an opening next to them.
		if (maze[wallY][upperCornerX - 1] == ' ')
		{
			maze[wallY][upperCornerX] = ' ';
		}
		if (maze[wallY][upperCornerX + areaWidth] == ' ')
		{
			maze[wallY][upperCornerX + areaWidth - 1] = ' ';
		}
		
		// Randomly create a hole in the wall.
		int randX = upperCornerX + (rand() % areaWidth);
		maze[wallY][randX] = ' ';

		// Uncomment the printMaze function calls to see the process of the maze being created, good visualization of recursion. Easier to debug issues.
		//printMaze(maze);
		//system("clear"); // Works on mac, needs to be modified to system("cls") for windows.
		//cout << endl << endl << endl;
		
		// Recursively call the area above the line.
		createMaze(maze, upperCornerY, upperCornerX, wallY - upperCornerY, areaWidth);
		// Recursively call the area below the line.
		createMaze(maze, wallY + 1, upperCornerX, upperCornerY + areaHeight - wallY - 1, areaWidth);
		
		// After the recursive calls have returned this function too must return.
		return;
	}
	// Else create a verical line.
	else
	{
		// Range of x values to choose from is the width - 2 because we dont want to create parallel lines right next to eachother.
		int rangeX = areaWidth - 2;
		int wallX = upperCornerX + ((rand() % rangeX) + 1);

		// For loop to draw the vertical line
		for (int y = upperCornerY; y < upperCornerY + areaHeight; y++)
		{
			maze[y][wallX] = 'X';
		}

		// Check for openings at the ends of the line just drawn, if there are any make an opening next to them.
		if (maze[upperCornerY - 1][wallX] == ' ')
		{
			maze[upperCornerY][wallX] = ' ';
		}
		if (maze[upperCornerY + areaHeight][wallX] == ' ')
		{
			maze[upperCornerY + areaHeight - 1][wallX] = ' ';
		}
		
		// Randomly create a hole in the wall.
		int randY = upperCornerY + (rand() % areaHeight);
		maze[randY][wallX] = ' ';
		
		//printMaze(maze);
		//system("clear");
		//cout << endl << endl << endl;
		// Recursively call the area to the left of the line.
		createMaze(maze, upperCornerY, upperCornerX, areaHeight, wallX - upperCornerX);
		// Recursively call the area to the right of the line.
		createMaze(maze, upperCornerY, wallX + 1, areaHeight, upperCornerX + areaWidth - wallX - 1);
		
		// After the recursive calls have returned this function too must return.
		return;
	}
}
int main()
{
	srand(time(NULL));
	char maze[HEIGHT][WIDTH];
	fillBorders(maze);
	createMaze(maze, 1, 1, HEIGHT - 2, WIDTH - 2);
	printMaze(maze);
	system("pause");
}