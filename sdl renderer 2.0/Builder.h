#ifndef BUILDER_H
#define BUILDER_H

#include <iostream>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#include <stack>
#include <fstream>
#include <sstream>
using namespace std;

const int MAZE_SIZE = 49;

struct Cell
{
	bool visited;
	bool top_wall;
	bool bot_wall;
	bool left_wall;
	bool right_wall;
	char display;
};

class Builder
{
public:
	Builder();
	void BuildMaze();
	int GetStartX(){return posX;};
	int GetStartY(){return posY;};
	int GetGoalX(){return goalX;};
	int GetGoalY(){return goalY;};
private:
	void Initialize(Cell Level[][MAZE_SIZE]);
	void GenerateMaze(Cell Level[][MAZE_SIZE], int&, int&, int&, int&);
	void Save(Cell Level[][MAZE_SIZE], int &posX, int &posY, int &goalX, int &goalY, char* outputFile);
private:
	Cell Level[MAZE_SIZE][MAZE_SIZE];
	int posX;
	int posY;
	int goalX;
	int goalY;
	char* outputFile;
};

#endif