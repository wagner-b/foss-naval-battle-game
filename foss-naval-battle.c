/*
*	FOSS naval battle game
*	Copyright (C) 2022 Wagner Bertholdo Bughausen
*	<https://github.com/wagner-b>, <wagb2b2@gmail.com>
*
*	This program is free software: you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*
*	This program is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*	GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License
*	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIM 8

int matrix[DIM][DIM];

int main();
void showHelp();
void fillWithZeros();
int selectDifficulty();
int checkFreeBlocksRight(int row, int column);
int checkFreeBlocksDown(int row, int column);
int fillFreeBlocksRight(int row, int column);
int fillFreeBlocksDown(int row, int column);
int fillFreeBlocks(int row, int column);
void placeShips(int difficulty);
void printGrid(int showAllShips);
int invalidUserInput(int x, int y);
void shoot();
int checkPlayerVictory();
void gameLogic();
int menu();
void showLicense();


int main()
{
	srand(time(0));

	while(menu());

	return 0;
}


void showHelp()
{
	printf("\n\n\t");
	printf(" Welcome to FOSS naval battle game! \n");
	printf(" Your goal in this game is to hit every ship in an 8x8 grid. \n");
	printf(" The amount of ammo and ships vary with the difficulty you choose. \n");
	printf(" The computer places the ships for you randomly in the grid. \n");
	printf(" The size of each ship varies, but is always at least 2 blocks long. \n");
	printf(" Ships may be in vertical or horizontal position. \n");
	printf(" It isn't mandatory to exist an empty block between two ships. \n");
	printf(" Each turn, you choose a row and a column of the grid to shoot. \n");
	printf(" From top to bottom are rows 1 to 8. \n");
	printf(" And from left to right are columns 1 to 8. \n");
	printf(" If you shoot an empty block, you'll see the symbol ~ appear. \n");
	printf(" If you shoot a ship, you'll see the symbol X appear. \n");
	printf(" The game ends when you hit every ship, or run out of ammo. \n");
	printf(" The symbol @ represents the ship(s) you failed to hit in the end. \n");
	printf(" Thanks for playing! \n");
}


void fillWithZeros()
{
	int row, column;

	for(row = 0; row < DIM; row++)
	{
		for(column = 0; column < DIM; column++)
			matrix[row][column] = 0;
	}

}


int selectDifficulty()
{
	int diff;

	printf("\nGame difficulty options: \n");
	printf(" 1 - Easy (60 shots, fewer ships) \n");
	printf(" 2 - Normal (52 shots) \n");
	printf(" 3 - Hard (48 shots, more ships) \n");
	printf("Select a difficulty [1 - 3]: ");
	scanf(" %d", &diff);

	if(diff < 1 || diff > 3)
	{
		printf("Invalid input! \n");
		printf("Difficulty will be set to normal \n");
		diff = 2;
	}

	return diff;
}


int checkFreeBlocksRight(int row, int column)
{
	int i, freeBl = 0;

	if(matrix[row][column] != 0)
		return 0;

	for(i = 1; i < DIM; i++)
	{
		if(column + i < DIM)
		{
			if(matrix[row][column + i] == 0 && freeBl < 4)
				freeBl++;
			else
				break;
		}
	}

	return freeBl;
}


int checkFreeBlocksDown(int row, int column)
{
	int i, freeBl = 0;

	if(matrix[row][column] != 0)
		return 0;

	for(i = 1; i < DIM; i++)
	{
		if(row + i < DIM)
		{
			if(matrix[row + i][column] == 0 && freeBl < 4)
				freeBl++;
			else
				break;
		}
	}

	return freeBl;
}


int fillFreeBlocksRight(int row, int column)
{
	int freeBlocks, i;

	if(!checkFreeBlocksRight(row, column))
		return 0;

	freeBlocks = checkFreeBlocksRight(row, column);
	freeBlocks = freeBlocks - (rand() % freeBlocks);

	matrix[row][column] = 10;
	for(i = 1; i <= freeBlocks; i++)
		matrix[row][column + i] = 10;

	return 1;
}


int fillFreeBlocksDown(int row, int column)
{
	int freeBlocks, i;

	if(!checkFreeBlocksDown(row, column))
		return 0;

	freeBlocks = checkFreeBlocksDown(row, column);
	freeBlocks = freeBlocks - (rand() % freeBlocks);

	matrix[row][column] = 10;
	for(i = 1; i <= freeBlocks; i++)
		matrix[row + i][column] = 10;

	return 1;
}


int fillFreeBlocks(int row, int column)
{
	int i = rand() % 2;

	switch(i)
	{
		case 0:
			if(!fillFreeBlocksRight(row, column))
				return 0;

			break;

		case 1:
			if(!fillFreeBlocksDown(row, column))
				return 0;
	}

	return 1;
}


void placeShips(int difficulty)
{
	int row, column, ships = 0;
	int maxShips = difficulty * 3;

	while(ships < maxShips)
	{
		row = rand() % DIM;
		column = rand() % DIM;

		if(fillFreeBlocks(row, column))
			ships++;
	}
}


void printGrid(int showAllShips)
{
	int i, row, column;

	printf("\n");

	for(i = 1; i < 18; i++)
	{
		for(column = 0; column < DIM; column++)
		{
			if(column == 0)
				printf("  |");

			if(i % 2 != 0)
				printf("-----");
			else
			{
				row = (i / 2) - 1;

				if(matrix[row][column] == 1)
					printf("  X  ");
				else if(matrix[row][column] == -1)
					printf("  ~  ");
				else if(matrix[row][column] == 10 && showAllShips)
					printf("  @  ");
				else
					printf("     ");
			}
			printf("|");
		}
		printf("\n");
	}
	printf("\n");
}


int invalidUserInput(int x, int y)
{
	if(x > 0 && x < 9 && y > 0 && y < 9)
		return 0;
	else
	{
		printGrid(0);
		printf("Invalid input! \n");
		return 1;
	}
}


void shoot()
{
	int userX, userY;
	do
	{
		printf("Select a row [1 - 8]: ");
		scanf(" %d", &userX);
		printf("Select a column [1 - 8]: ");
		scanf(" %d", &userY);
	}
	while(invalidUserInput(userX, userY));
	userX--; userY--;

	if(matrix[userX][userY] == 0)
	{
		matrix[userX][userY] = -1;
		printGrid(0);
		printf("You've missed this shot! \n");
	}
	else if(matrix[userX][userY] == 10)
	{
		matrix[userX][userY] = 1;
		printGrid(0);
		printf("You've managed to hit a ship! \n");
	}
	else
	{
		printGrid(0);
		printf("You've wasted a shot! \n");
	}
}


int checkPlayerVictory()
{
	int row, column;

	for(row = 0; row < DIM; row++)
	{
		for(column = 0; column < DIM; column++)
		{
			if(matrix[row][column] == 10)
				return 0;
		}
	}

	printf("Congratulations!! You sank every ship!! \n");
	return 1;
}


void gameLogic()
{
	int difficulty = selectDifficulty();
	int maxShots = 36 + (48 / (difficulty + 1));
	int shots;

	fillWithZeros();
	placeShips(difficulty);
	printGrid(0);

	for(shots = 1; shots <= maxShots; shots++)
	{
		shoot();
		printf("%d shots left \n", maxShots - shots);

		if(checkPlayerVictory())
			return;
	}

	printGrid(1);
	printf("Sorry, you're out of ammo and failed to sink all ships! \n");
}


int menu()
{
	int opt;
	printf("\n Menu: \n");
	printf(" 1 - Play \n");
	printf(" 2 - Show help / tutorial \n");
	printf(" 3 - Show license notice \n");
	printf(" 0 - Exit \n");
	printf("Choose an option [0 - 3]: ");
	scanf(" %d", &opt);

	switch(opt)
	{
		case 0:
			return 0;
		case 1:
			gameLogic();
			break;
		case 2:
			showHelp();
			break;
		case 3:
			showLicense();
			break;
		default:
			printf("Invalid option, please try again. \n");
	}

	return 1;
}


void showLicense()
{
	printf("\n\n FOSS naval battle game \n");
	printf(" Copyright (C) 2022 Wagner Bertholdo Burghausen \n");
	printf(" <https://github.com/wagner-b>, <wagb2b2@gmail.com> \n\n");
	printf(" This program is free software: you can redistribute it and/or modify \n");
	printf(" it under the terms of the GNU General Public License as published by \n");
	printf(" the Free Software Foundation, either version 3 of the License, or \n");
	printf(" (at your option) any later version. \n\n");
	printf(" This program is distributed in the hope that it will be useful, \n");
	printf(" but WITHOUT ANY WARRANTY; without even the implied warranty of \n");
	printf(" MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the \n");
	printf(" GNU General Public License for more details. \n\n");
	printf(" You should have received a copy of the GNU General Public License \n");
	printf(" along with this program. If not, see <https://www.gnu.org/licenses/>. \n");
}
