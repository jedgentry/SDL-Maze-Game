#include "Generate.h"

Generate::Generate(int screenWidth, int screenHeight, string generateDirectory)
{
	this->screenHeight = screenHeight;
	this->screenWidth = screenWidth;
	this->generateDirectory = generateDirectory;
	mazeCleared = true;
	builder = NULL;
	builder = new Builder();
	for(int i = 0; i < MAZE_SIZE_X; i++)
	{
		for(int j = 0; j < MAZE_SIZE_Y; j++)
		{
			mazeBlocks[i][j] = NULL;
		}
	}
}

bool Generate::Initialize()
{
	builder->BuildMaze();
	ParseFileIntoMemory();
	InitializeStructs();
	LoadStructTextures();
	//DEBUG INFO
	//Debug();

	return true;
}

void Generate::ResetVisibility()
{
	for(int i = 0; i < MAZE_SIZE_X; i++)
	{
		for(int j = 0; j < MAZE_SIZE_Y; j++)
		{
			mazeBlocks[i][j]->rendered = false;
		}
	}
}

void Generate::Update(SDL_Surface* screen)
{
	for(int i = 0; i < MAZE_SIZE_X; i++)
	{
		for(int j = 0; j < MAZE_SIZE_Y; j++)
		{
			if(mazeBlocks[i][j]->rendered)
			{
				mazeBlocks[i][j]->blockTexture->Draw(screen, mazeBlocks[i][j]->x, mazeBlocks[i][j]->y);
			}
		}
	}
}

void Generate::MakeNewMaze()
{
	mazeCleared = true;
	Initialize();
}

void Generate::ClearMaze()
{
	for(unsigned int i = 0; i < fileVector.size(); i++)
	{
		fileVector.pop_back();
	}
	//Clear the array.
	for(int i = 0; i < MAZE_SIZE_X; i++)
	{
		for(int j = 0; j < MAZE_SIZE_Y; j++)
		{
			if(mazeBlocks[i][j] != NULL)
			{
				delete mazeBlocks[i][j]->blockTexture;
				delete mazeBlocks[i][j];
				mazeBlocks[i][j] = NULL;
			}
		}
	}

	mazeCleared = true;
}

int Generate::GetSteps()
{
	int steps = 0;
	for(int i = 0; i < MAZE_SIZE; i++)
	{
		for(int j = 0; j < MAZE_SIZE; j++)
		{
			if(!mazeBlocks[i][j]->rendered)
				steps++;
		}
	}
	return steps;
}

bool Generate::GenerateMazeExternal()
{
	string temp = "cd /d ";
	temp += generateDirectory;
	for(unsigned int i = temp.length() - 1; i > 0; i--)
	{
		if(temp[i] != '\\')
		{
			temp = temp.substr(0, i);
		}
		else
		{
			break;
		}
	}
	temp = temp.substr(0, temp.length() - 1);

	for(unsigned int i = 0; i < temp.length(); i++)
	{
		if(temp[i] == '\\')
		{
			temp = temp.substr(0, i) + '\\' + temp.substr(i, temp.length() - 1);
			i++;
		}
	}
	temp = temp + " && PrimsAlgorithm.exe";
	if(system((char*) temp.c_str()) != 0)
	{
		cerr << "Failed to find Prims Algorithm Executable." << endl;
		return false;
	}
	return true;
}

void Generate::InitializeStructs()
{
	for(unsigned int i = 0; i < fileVector.size(); i++)
	{
		for(unsigned int j = 0; j < fileVector[i].length(); j++)
		{
			if(mazeBlocks[i][j] == NULL)
			{
			Block* b = new Block();
			b->moveable = false;
			mazeBlocks[i][j] = b;
			b->x = i * BLOCK_SIZE;
			b->y = j * BLOCK_SIZE;
			b->rendered = false;
			}
		}
	}
}

bool Generate::ParseFileIntoMemory()
{
	if(fileVector.size() > 0)
	{
		while(fileVector.size() != 0)
			fileVector.pop_back();
	}
	string temp = "";
	cout << generateDirectory << endl << endl;
	temp += "currentMaze.txt";
	ifstream fin;
	fin.open(temp);
	temp = "";
	if(fin.bad())
	{
		cerr << "BAD FILE NAME OR FILE LOCATION." << endl;
		return false;
	}
	//Skip first line due to white space
	getline(fin, temp);
	temp = "";
	//Loop through file.
	while(!fin.eof())
	{
		getline(fin, temp);
		fileVector.push_back(temp);
		temp = "";
	}
	stringstream ss;
	//Pop the Useless endline.
	fileVector.pop_back();
	//PUll in and convert the EndY.
	endY = builder->GetGoalY();
	fileVector.pop_back();
	//Pull in and convert the EndX.
	endX = builder->GetGoalX();
	fileVector.pop_back();
	//Pull in and convert the startY.
	startY = builder->GetStartY();
	fileVector.pop_back();
	//Pull in and convert the startX.
	startX = builder->GetStartX(); 
	fileVector.pop_back();

	return true;
}

void Generate::LoadStructTextures()
{
	for(unsigned int i = 0; i < fileVector.size(); i++)
	{
		for(unsigned int j = 0; j < fileVector[i].length(); j++)
		{
			if(fileVector[i].c_str()[j] == '*')
			{
				if(mazeBlocks[i][j]->blockTexture != NULL)
				{
					mazeBlocks[i][j]->blockTexture->Shutdown();
					delete mazeBlocks[i][j]->blockTexture;
					mazeBlocks[i][j]->blockTexture = NULL;
				}
				mazeBlocks[i][j]->blockTexture = new Texture("testSquare.bmp");
				mazeBlocks[i][j]->moveable = false;
			}
			else
			{
				if(mazeBlocks[i][j]->blockTexture != NULL)
				{
					mazeBlocks[i][j]->blockTexture->Shutdown();
					delete mazeBlocks[i][j]->blockTexture;
					mazeBlocks[i][j]->blockTexture = NULL;
				}
				mazeBlocks[i][j]->blockTexture = new Texture("whiteSquare.bmp");
				mazeBlocks[i][j]->moveable = true;
			}
		}
	}

	if(!mazeBlocks[endX][endY]->moveable)
	{
		mazeBlocks[endX][endY]->moveable = true;
		mazeBlocks[endX][endY]->blockTexture->SwapTexture("whiteSquare.bmp");
	}
	if(!mazeBlocks[startX][startY]->moveable)
	{
		mazeBlocks[endX][endY]->moveable = true;
		mazeBlocks[endX][endY]->blockTexture->SwapTexture("whiteSquare.bmp");
	}
}

void Generate::Debug()
{
	ofstream fout;
	fout.open("STRUCTS_DEBUG.txt");

	for(unsigned int i = 0; i < fileVector.size(); i++)
	{
		fout << fileVector[i] << endl;
	}


	for(unsigned int i = 0; i < fileVector.size(); i++)
	{
		for(unsigned int j = 0; j < fileVector[i].length(); j++)
		{
			//Causes crashing currently with Char* issues.
			fout << "BLOCK[" << i << "][" << j << "] Texture: " << (void*)mazeBlocks[i][j]->blockTexture->debugFilename
				<< "\tMoveable?: " << fileVector[i].at(j) << boolalpha << mazeBlocks[i][j]->moveable
				<< endl;
		}
	}
	fout.close();
}

void Generate::Shutdown()
{
	return;
}
