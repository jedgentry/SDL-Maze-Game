#include "Map.h"

Map::Map()
{
	blocks = 0;
}

void Map::Update()
{
	for(unsigned int i = 0; i < blockVector.size(); i++)
	{
		blockVector[i]->Update();
	}
}

void Map::Add(Block* b)
{
	blockVector.push_back(b);
	blocks++;
}

void Map::Shutdown()
{
	for(unsigned int i = 0; i < blockVector.size(); i++)
	{
		blockVector[i]->Shutdown();
	}
	blocks = 0;
}