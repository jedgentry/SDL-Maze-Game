#ifndef GENERATE_H
#define GENERATE_H

#include "Texture.h"
#include "Builder.h"

#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <sstream>

using namespace std;

//Maze size in X coordinates.
const int MAZE_SIZE_X = 49;
//Maze size in Y coordinates.
const int MAZE_SIZE_Y = 49;
//Size of each block in pixels.
const int BLOCK_SIZE = 16;

//Structure of each block in a maze.
struct Block
{
	//Texture of the block (black or white)
	Texture* blockTexture;
	//If you can move to this space.
	bool moveable;
	//x location
	int x;
	//y location
	int y;
	//If object will be rendered.
	bool rendered;
};

class Generate
{
public:
	//Default Constructor.
	Generate(){};
	//Generate - Normal constructor.
	//@param int - width of screen in pixels.
	//@param int - height of screen in pixels.
	//@param string - directory of the programs executable.
	Generate(int screenWidth, int screenHeight, string generateDirectory);
	//Initialize - Initializes the generate class functions.
	//@return bool - true if successful.
	bool Initialize();
	void MakeNewMaze();
	//Update - updates the generate class object.
	//@param SDL_Surface* - pointer to the screen.
	void Update(SDL_Surface* screen);
	//Shutdown - shutsdown the generate class.
	void Shutdown();
	int GetSteps();
	void ResetVisibility();
	//GenerateMaze - generates a maze.
	//@return - true if maze generation is successful.
	void ClearMaze();
	//GenerateMazeExternal - Makes a new maze, automatically overwriting previous file.
	//@return - true if maze generation is successful.
	bool GenerateMazeExternal();
	//GetStartX - returns the starting X.
	//@return int - x value of the starting x in pixels.
	int GetStartX() {return startX * BLOCK_SIZE;};
	//GetStartY - returns the starting Y in pixels.
	//@return int - value of Y coordinate in pixels.
	int GetStartY() {return startY * BLOCK_SIZE;};
	//GetEndX - endX in pixels.
	//@return int - endX in pixels.
	int GetEndX() {return endX * BLOCK_SIZE;};
	//GetEndY - endY in pixels.
	//@return int - value of Y end in pixels.
	int GetEndY() {return endY * BLOCK_SIZE;};
	//GetEndY - endY in array.
	//@return int - endY in array
	int GetEndYArray() {return endY;};
	int GetEndXArray() {return endX;};
	int GetStartXArray() {return startX;};
	int GetStartYArray() {return startY;};
		//Converted structs in memory.
	Block* mazeBlocks[MAZE_SIZE_X][MAZE_SIZE_Y];

		//Builder Object for generating maze.
	Builder* builder;
private:
	//bool for generating next maze while playing.
	bool mazeGenerated;
	//Value of the screen's width.
	int screenWidth;
	//Value of the screen's height.
	int screenHeight;
	//Starting X location in pixels.
	int startX;
	//Starting Y location in pixels.
	int startY;
	//Goal location X in pixels.
	int endX;
	//Goal location Y in pixels.
	int endY;
	//Raw file in memory.
	vector<string> fileVector;
	//Location of programs main executable
	string generateDirectory;


	bool mazeCleared;
private:
	//InitializeStructs - Fills the array full of Block Structs.
	void InitializeStructs();
	//SmartRender - log(n) rendering after main rendering is complete.
	void SmartRender();
	//ParseFileIntoMemory - puts the text file into a vector full of strings
	//and sets the X and Y values for the start and end positions.
	bool ParseFileIntoMemory();
	//LoadStructTextures - Fills the structs with their apporpriate textures.
	void LoadStructTextures();
	//IntialRender - O(n^2) rendering - fills screen with blocks to render.
	void InitialRender();

	//FOR TESTING PURPOSES
	void Debug();

};

#endif