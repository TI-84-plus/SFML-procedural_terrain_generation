#ifndef MAP_H
#define MAP_H

#include "Player/player.h"
#include <iostream>

class Map
{

private: 
	player Player;

public:
	player Player_Getter() 
	{
		return Player;
	}

	void GenerateMap() 
	{
		
	}
};

#endif
