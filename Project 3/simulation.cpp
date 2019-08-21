#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>

#include "world_type.h"
#include "simulation.h"
using namespace std;


/*================ROUND PLAY & SIMULATING=================*/
void round_play(int cr_i, world_t &theWorld, int if_verb)
{
	unsigned int &counter = theWorld.creatures[cr_i].programID;
	bool stop_round = false;
	while (stop_round != true)
	{
		if (if_verb)
		{
			cout << "Instruction " << (counter+1) << ": " << 
				opName[theWorld.creatures[cr_i].species -> program[counter].op];
			if (theWorld.creatures[cr_i].species -> program[counter].op > 3)
				cout << " " << theWorld.creatures[cr_i].species -> program[counter].address +1 << endl;
			else
				cout << endl;
		}

		switch (theWorld.creatures[cr_i].species -> program[counter].op)
		{
			case 0:
			{
				hop(cr_i, theWorld);
				stop_round = true;
				counter ++;
				break;

			}
			case 1:
			{
				left(cr_i, theWorld);
				stop_round = true;
				counter ++;
				break;
			}
			case 2:
			{
				right(cr_i, theWorld);
				stop_round = true;
				counter ++;
				break;
			}
			case 3:
			{
				infect(cr_i, theWorld);
				stop_round = true;
				counter ++;
				break;
			}
			case 4:
			{
				if (ifempty(cr_i, theWorld))
					go(theWorld.creatures[cr_i].species -> program[counter].address, cr_i, theWorld);
				else
					counter ++;
				break;
			}
			case 5:
			{
				if (ifenemy(cr_i, theWorld))
					go(theWorld.creatures[cr_i].species -> program[counter].address, cr_i, theWorld);
				else
					counter ++;
				break;
			}
			case 6:
			{
				if (ifsame(cr_i, theWorld))
					go(theWorld.creatures[cr_i].species -> program[counter].address, cr_i, theWorld);
				else
					counter ++;
				break;
			}
			case 7:
			{
				if (ifwall(cr_i, theWorld))
					go(theWorld.creatures[cr_i].species -> program[counter].address, cr_i, theWorld);
				else
					counter ++;
				break;
			}
			case 8:
			{
				go(theWorld.creatures[cr_i].species -> program[counter].address, cr_i, theWorld);
				break;
			}
		}
	}
	if (if_verb == 0)
		cout << " " << opName[theWorld.creatures[cr_i].species -> program[counter -1].op] << endl;
}

void simu_output(const world_t &world)
{
	for (int i = 0; i < int(world.grid.height); i ++)
	{
		for (int j = 0; j < int(world.grid.width); j ++)
		{
			if (world.grid.squares[i][j] == NULL)
				cout << "____ " ;
			else
				cout << world.grid.squares[i][j] -> species -> name[0]
					<< world.grid.squares[i][j] -> species -> name[1] << "_" << 
					directShortName[world.grid.squares[i][j] -> direction] << " ";
		}
		cout << endl;
	}
}

//********************INSTRUCTIONS****************************//
bool ifsame(int cr_i, world_t &theWorld)
{
	if (!ifempty(cr_i, theWorld) and !ifwall(cr_i, theWorld))
		return !ifenemy(cr_i, theWorld);
	else
		return false;
}

bool ifenemy(int cr_i, world_t &theWorld)
{
	if (!ifempty(cr_i, theWorld) and !ifwall(cr_i, theWorld))
	{	
		point_t face_loc = front_loc(cr_i, theWorld);
		if (theWorld.creatures[cr_i].species -> name == theWorld.grid.squares[face_loc.r][face_loc.c] -> species -> name)
			return false;
		else
			return true;
	}
	else
		return false;
}

bool ifempty(int cr_i, world_t &theWorld)
{
	point_t face_loc = front_loc(cr_i, theWorld);

	if (ifwall(cr_i, theWorld) == false and theWorld.grid.squares[face_loc.r][face_loc.c] == NULL)
		return true;
	else
		return false;
}

bool ifwall(int cr_i, world_t &theWorld)
{
	point_t face_loc = front_loc(cr_i, theWorld);
	unsigned int height = theWorld.grid.height;
	unsigned int width = theWorld.grid.width;
	if (face_loc.r < 0 or face_loc.r >= int(height) or face_loc.c < 0 or face_loc.c >= int(width))
		return true;
	else
		return false;
}


point_t front_loc(int cr_i, world_t &theWorld)
{
	point_t face_loc;
	int dir = theWorld.creatures[cr_i].direction;
	int origin_row = theWorld.creatures[cr_i].location.r;
	int origin_col = theWorld.creatures[cr_i].location.c;
	switch (dir)
	{
		case 0:
		{
			face_loc.r = origin_row;
			face_loc.c = origin_col +1;
			break;
		}
		case 1:
		{
			face_loc.r = origin_row +1;
			face_loc.c = origin_col;
			break;
		}
		case 2:
		{
			face_loc.r = origin_row;
			face_loc.c = origin_col -1;
			break;
		}
		case 3:
		{
			face_loc.r = origin_row -1;
			face_loc.c = origin_col;
		}
	}
	return face_loc;
}

void hop(int cr_i, world_t &theWorld)
{
	if (ifempty(cr_i, theWorld))
	{
		point_t cr_i_loc = theWorld.creatures[cr_i].location;
		point_t face_loc = front_loc(cr_i, theWorld);
		theWorld.creatures[cr_i].location = face_loc;
		theWorld.grid.squares[cr_i_loc.r][cr_i_loc.c] = NULL;
		theWorld.grid.squares[face_loc.r][face_loc.c] = &theWorld.creatures[cr_i];
	}
}


void infect(int cr_i, world_t &theWorld)
{
	if (ifenemy(cr_i, theWorld))
	{
		point_t face_loc = front_loc(cr_i, theWorld);
		theWorld.grid.squares[face_loc.r][face_loc.c] -> species = theWorld.creatures[cr_i].species;
		theWorld.grid.squares[face_loc.r][face_loc.c] -> programID = 0;
	}
} 

void left(int cr_i, world_t &theWorld)
{
	if (theWorld.creatures[cr_i].direction == EAST)
		theWorld.creatures[cr_i].direction = NORTH;
	else if (theWorld.creatures[cr_i].direction == SOUTH)
		theWorld.creatures[cr_i].direction = EAST;
	else if (theWorld.creatures[cr_i].direction == WEST)
		theWorld.creatures[cr_i].direction = SOUTH;
	else
		theWorld.creatures[cr_i].direction = WEST;
}

void right(int cr_i, world_t &theWorld)
{
	if (theWorld.creatures[cr_i].direction == 0)
		theWorld.creatures[cr_i].direction = SOUTH;
	else if (theWorld.creatures[cr_i].direction == 1)
		theWorld.creatures[cr_i].direction = WEST;
	else if (theWorld.creatures[cr_i].direction == 2)
		theWorld.creatures[cr_i].direction = NORTH;
	else
		theWorld.creatures[cr_i].direction = EAST;
}

void go(unsigned int n, int cr_i, world_t &theWorld)
{
	theWorld.creatures[cr_i].programID = n;
}

/*==================Instructions=END======================*/
