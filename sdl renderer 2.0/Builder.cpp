#include "Builder.h"

Builder::Builder()
{
	outputFile = "currentMaze.txt";
}

void Builder::BuildMaze()
{
	Initialize(Level);
	//Generate the maze by setting the structs and push into
	//the stacks, then push back through to solve.
	GenerateMaze(Level, posX, posY, goalX, goalY);
	//Write out to file.
	Save(Level, posX, posY, goalX, goalY, outputFile);
}

void Builder::Initialize(Cell Level[][MAZE_SIZE])
{
	//Initialize everything to false and set display values.
	for(int i = 0; i < MAZE_SIZE; i++)
	{
		for(int j = 0; j < MAZE_SIZE; j++)
		{
			Level[i][j].display = '*';
			Level[i][j].visited = false;
			Level[i][j].top_wall = true;
			Level[i][j].bot_wall = true;
			Level[i][j].left_wall = true;
			Level[i][j].right_wall = true;
		}
	}
	for(int i = 1; i < MAZE_SIZE - 1; i++)
	{
		for(int j = 1; j < MAZE_SIZE - 1; j++)
		{
			Level[1][j].top_wall = false;
			Level[MAZE_SIZE - 2][j].bot_wall = false;
			Level[i][1].left_wall = false;
			Level[i][MAZE_SIZE - 2].right_wall = false;
		}
	}
}

void Builder::GenerateMaze(Cell Level[][MAZE_SIZE], int &posX, int &posY, int &goalX, int &goalY)
{
	srand((unsigned)time(NULL));
	int random;
	int randomX = ((2 * rand()) + 1) % (MAZE_SIZE - 1);
	int randomY = ((2 * rand()) + 1) % (MAZE_SIZE - 1);
	posX = randomX; //Players init x and y
	posY = randomY;
	int visitedCells = 1;
	int totalCells = ((MAZE_SIZE - 1) / 2) * ((MAZE_SIZE - 1) / 2);
	stack<int> back_trackX, back_trackY; //Stack used to trace path back.

	Level[randomY][randomX].display = 'S';
	Level[randomY][randomX].visited = true;

	while(visitedCells < totalCells)
	{
		if(((Level[randomY - 2][randomX].visited == false) && (Level[randomY][randomX].top_wall == true) && (Level[randomY - 2][randomX].bot_wall == true)) ||
			((Level[randomY + 2][randomX].visited == false) && (Level[randomY][randomX].bot_wall == true) && (Level[randomY + 2][randomX].top_wall == true)) ||
			((Level[randomY][randomX - 2].visited == false) && (Level[randomY][randomX].left_wall == true) && (Level[randomY][randomX - 2].right_wall == true)) ||
			((Level[randomY][randomX + 2].visited == false) && (Level[randomY][randomX].right_wall == true) && (Level[randomY][randomX + 2].left_wall == true)))
		{
			random = rand() % 4 + 1;
			if((random == 1) && (randomY > 1))
			{
				if(Level[randomY - 2][randomX].visited == false)
				{
					Level[randomY - 1][randomX].display = ' ';
					Level[randomY - 1][randomX].visited = true;
					Level[randomY][randomX].top_wall = false;

					back_trackX.push(randomX);
					back_trackY.push(randomY);

					randomY -= 2;
					Level[randomY][randomX].visited = true;
					Level[randomY][randomX].display = ' ';
					Level[randomY][randomX].bot_wall = false;
					visitedCells++;
				}
				else
					continue;
		   }

			else if((random == 2) && (randomY < MAZE_SIZE - 2))
			{
				if(Level[randomY + 2][randomX].visited == false)
				{
					Level[randomY + 1][randomX].display = ' ';
					Level[randomY + 1][randomX].visited = true;
					Level[randomY][randomX].bot_wall = false;

					back_trackX.push(randomX);
					back_trackY.push(randomY);

					randomY += 2;
					Level[randomY][randomX].visited = true;
					Level[randomY][randomX].display = ' ';
					Level[randomY][randomX].top_wall = false;
					visitedCells++;
				}
				else
					continue;
			}

			else if((random == 3) && (randomX > 1))
			{
				if(Level[randomY][randomX - 2].visited == false)
				{
					Level[randomY][randomX - 1].display = ' ';
					Level[randomY][randomX - 1].visited = true;
					Level[randomY][randomX].left_wall = false;

					back_trackX.push(randomX);
					back_trackY.push(randomY);

					randomX -= 2;
					Level[randomY][randomX].visited = true;
					Level[randomY][randomX].display = ' ';
					Level[randomY][randomX].right_wall = false;
					visitedCells++;
				}
				else
					continue;
			}

			else if((random == 4) && (randomX < MAZE_SIZE - 2))
			{
				if(Level[randomY][randomX + 2].visited == false)
				{
					Level[randomY][randomX + 1].display = ' ';
					Level[randomY][randomX + 1].visited = true;
					Level[randomY][randomX].right_wall = false;

					back_trackX.push(randomX);
					back_trackY.push(randomY);

					randomX += 2;
					Level[randomY][randomX].visited = true;
					Level[randomY][randomX].display = ' ';
					Level[randomY][randomX].left_wall = false;
					visitedCells++;
				}
				else
					continue;
			}
		}
		else
		{
			randomX = back_trackX.top();
			back_trackX.pop();

			randomY = back_trackY.top();
			back_trackY.pop();
		}
		}
		goalX = rand() % (MAZE_SIZE);
		goalY = rand() % (MAZE_SIZE);
		if(goalX == 0)
			goalX++;
		if(goalY == 0)
			goalY++;
		Level[goalY][goalX].display = 'E';
}

void Builder::Save(Cell Level[][MAZE_SIZE], int &posX, int &posY, int &goalX, int &goalY, char* outputFile)
{
	ofstream output;
	if(outputFile)
	{
		output.open(outputFile);
		for(int i = 0; i < MAZE_SIZE; i++)
		{
			output << endl;
			for(int j = 0; j < MAZE_SIZE; j++)
			{
				output << Level[i][j].display;
			}
		}
		output << endl;
		output << posX << endl;
		output << posY << endl;
		output << goalX << endl;
		output << goalY << endl;
		output.close();
	}
}