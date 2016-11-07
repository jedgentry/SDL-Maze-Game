#ifndef MAP_H
#define MAP_H

/**
	CLASS WILL NEED RESTRUCTURING BASED ON MAZE OUTPUT.
*/

#include <vector>

#include "Block.h"

using namespace std;

class Map
{
public:
	Map();
	void Update();
	void Add(Block*);
	void Shutdown();
private:
	vector<Block*> blockVector;
	int blocks;
};

#endif