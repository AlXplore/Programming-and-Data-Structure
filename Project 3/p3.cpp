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


int main(int argc, char* argv[])
{
	if (argc < 4)
	{
		cout << "Error: Missing arguments!\n" << "Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]" << endl;
		return 0;
	}
	int round_set = atoi(argv[3]);
	if (round_set < 0)
	{
		cout << "Error: Number of simulation rounds is negative!" << endl;
		return 0;
	}

	//
	//cout << "round is " << round_set << endl;

	string species_summary_path = argv[1];
	ifstream species_summary;
	species_summary.open(species_summary_path.c_str());
	if (!species_summary)
	{
		cout << "Error: Cannot open file " << species_summary_path << "!" << endl;
		return 0;
	}
	int sp_count = 0;
	string sps_dir;
	getline(species_summary, sps_dir);
	species_t species[MAXSPECIES];
	while (species_summary)
	{
		if (species_summary)
		{
			getline(species_summary, species[sp_count].name);
			sp_count ++;
		}
	}
	sp_count --;

	world_t simworld1;
	simworld1.numSpecies = sp_count;
	if (sp_count > int(MAXSPECIES))
	{
		cout << "Error: Too many species!\nMaximal number of species is "
		<< MAXSPECIES << "." << endl;
		return 0;
	}

// Read program instructions:
	for (int i = 0; i < sp_count; i++)
	{
		ifstream program_instrus;
		string program_instrus_path = sps_dir+"/"+species[i].name;
		string instructions[MAXPROGRAM];
		program_instrus.open(program_instrus_path.c_str());
		int instru_count = 0;
		if (!program_instrus)
		{
			cout << "Error: Cannot open file "<< program_instrus_path << "!" << endl;
			return 0;
		}
		else
		{
			while (getline(program_instrus, instructions[instru_count]) && 
				instructions[instru_count] != "")
			{
				instru_count ++;
				if (instru_count > int(MAXPROGRAM))
				{
					cout << "Error: Too many instructions for species" << species[i].name 
					<< "!\nMaximal number of instructions is " << MAXPROGRAM << "." << endl;
					return 0;
				}
			}
		}

		for (int j = 0; j < instru_count; j ++)
		{
			int instru_recog = 0;
			string program_instruction;
			int address = -1;
			istringstream is(instructions[j]);
			is >> program_instruction >> address;
			for (int k = 0; k < 9; k ++)
			{
				if (program_instruction == opName[k])
				{
					switch (k)
					{
						case 0:
						{species[i].program[j].op = HOP; break;} 
						case 1:
						{species[i].program[j].op = LEFT; break;}
						case 2:
						{species[i].program[j].op = RIGHT; break;}
						case 3:
						{species[i].program[j].op = INFECT; break;}
						case 4:
						{species[i].program[j].op = IFEMPTY;
						 	species[i].program[j].address = address -1; break;}
						case 5:
						{species[i].program[j].op = IFENEMY;
							species[i].program[j].address = address -1; break;}
						case 6:
						{species[i].program[j].op = IFSAME;
							species[i].program[j].address = address -1; break;}
						case 7:
						{species[i].program[j].op = IFWALL;
							species[i].program[j].address = address -1; break;}
						case 8:
						{species[i].program[j].op = GO; 
							species[i].program[j].address = address -1; break;}
					}
					instru_recog = 1;
					break;
				}
			}
			if (instru_recog == 0)
			{
				cout << "Error: Instruction " << program_instruction << " is not recognized!" << endl;
				return 0;
			}
		}
		species[i].programSize = instru_count;
	}
	for (int i = 0; i < sp_count; i ++)
		simworld1.species[i] = species[i];

/*
	cout << "species count = " << sp_count << endl;
	for (int testi = 0; testi < sp_count; testi ++)
		cout << "species name: " << simworld1.species[testi].name << endl;
	for (int testi = 0; testi < sp_count; testi ++)
	{
		cout << "species " << testi << " programSize is " << simworld1.species[testi].programSize << endl;
		for (int testi2 = 0; testi2 < simworld1.species[testi].programSize; testi2 ++)
		{
			cout << "species instruction " << testi2 << " is:" << opName[simworld1.species[testi].program[testi2].op] << endl;
			if (simworld1.species[testi].program[testi2].op > 3)
				cout << "and address is " << simworld1.species[testi].program[testi2].address << endl;
		}

	}
*/

	ifstream world_file;
	string world_file_path = argv[2];
	world_file.open(world_file_path.c_str());
	int cr_count = 0;
	string world_file_lines[55];

	if (!world_file)
	{
		cout << "Error: Cannot open file" << world_file_path << "!" << endl;
		return 0;
	}
	else
	{
		while (getline(world_file, world_file_lines[cr_count]))
			cr_count ++;
	}
	int height_get, width_get;
	height_get = atoi(world_file_lines[0].c_str());
	if (height_get < 1 or height_get > int(MAXHEIGHT))
	{
		cout << "Error: The grid height is illegal!" << endl;
		return 0;
	}
	width_get = atoi(world_file_lines[1].c_str());
	if (width_get <1 or width_get > int(MAXHEIGHT))
	{
		cout << "Error: The grid width is illegal!" << endl;
		return 0;
	}
	simworld1.grid.height = height_get;
	simworld1.grid.width = width_get;
	int cr_count_real = cr_count - 2;
	if (cr_count_real > int(MAXCREATURES))
	{
		cout << "Error: Too many creatures!\nMaximal number of creatures is " << MAXCREATURES << endl;
		return 0;
	}
	simworld1.numCreatures = cr_count_real;

	string type_str;
	string direction_str;
	for (int i = 2; i < cr_count; i ++)
	{
		simworld1.creatures[i-2].programID = 0;
		istringstream is(world_file_lines[i]);
		is >> type_str >> direction_str >> simworld1.creatures[i-2].location.r >> simworld1.creatures[i-2].location.c;
		int sp_recog = 0;
		for (int j = 0; j < sp_count; j ++)
		{
			if (type_str == simworld1.species[j].name)
			{
				simworld1.creatures[i-2].species = &simworld1.species[j];
				sp_recog = 1;
				break;
			}
		}
		if (sp_recog == 0)
		{
			cout << "Error: Species " << type_str << " not found!" << endl;
			return 0;
		}

		for (int j = 0; j < 4; j ++)
		{
			if (direction_str == "east")
				simworld1.creatures[i-2].direction = EAST;
			else if (direction_str == "south")
				simworld1.creatures[i-2].direction = SOUTH;
			else if (direction_str == "west")
				simworld1.creatures[i-2].direction = WEST;
			else if (direction_str == "north")
				simworld1.creatures[i-2].direction = NORTH;
			else
			{
				cout << "Error: Direction " << direction_str << " is not recognized!" << endl;
				return 0;
			}
		}
	}
	for (int i = 0; i < cr_count_real; i ++)
	{
		if (simworld1.creatures[i].location.r < 0 or simworld1.creatures[i].location.r > int(simworld1.grid.height -1) or 
			simworld1.creatures[i].location.c < 0 or simworld1.creatures[i].location.c > int(simworld1.grid.width -1))
		{
			cout << "Error: Creature (" << simworld1.creatures[i].species -> name << " " << directName[simworld1.creatures[i].direction]
			 << " " << simworld1.creatures[i].location.r << " " << simworld1.creatures[i].location.c << ") is out of bound!\nThe grid size is "
			 << simworld1.grid.height << "-by-" << simworld1.grid.width << "." << endl;
			return 0;
		}
	}

	for (int i = 0; i < int(simworld1.grid.height); i ++)
	{
		for (int j = 0; j < int(simworld1.grid.width); j ++)
			simworld1.grid.squares[i][j] = NULL;
	}
	for (int i = 0; i < cr_count_real; i ++)
	{
		int cr_row = simworld1.creatures[i].location.r;
		int cr_col = simworld1.creatures[i].location.c;
		if (simworld1.grid.squares[cr_row][cr_col] == NULL)
			simworld1.grid.squares[cr_row][cr_col] = & simworld1.creatures[i];
		else
		{
			cout << "Error: Creature (" << simworld1.creatures[i].species -> name << " " << directName[simworld1.creatures[i].direction] << " " 
				<< simworld1.creatures[i].location.r << " " << simworld1.creatures[i].location.c << ") overlaps with creature (" 
				<< simworld1.grid.squares[cr_row][cr_col] -> species -> name << " " << directName[simworld1.grid.squares[cr_row][cr_col] -> direction] 
				<< " " << simworld1.grid.squares[cr_row][cr_col] -> location.r << " " << simworld1.grid.squares[cr_row][cr_col] -> location.c << ")!" << endl;
			return 0;

		}
	}
/*
	for (int i = 0; i < simworld1.numCreatures; i ++)
	{
		cout << "creature " << i << " location is (" << simworld1.creatures[i].location.r << "," 
			<< simworld1.creatures[i].location.c << ")." << endl;
		cout << "its direction is " << simworld1.creatures[i].direction << endl;
		cout << "its species is " << simworld1.creatures[i].species -> name << endl;
		cout << "pid is" << simworld1.creatures[i].programID << endl;
	}
	cout << "World gird height: " << simworld1.grid.height << " world gird width: " << simworld1.grid.width << endl;
	cout << "World num creatures: " << cr_count_real << endl;
*/
	int if_verb = 0;
	string if_verb_str;
	if (argc < 5)
		if_verb_str = "c";
	else
		if_verb_str = argv[4];
	if (if_verb_str == "v" or if_verb_str == "verbose")
		if_verb = 1;
	if (if_verb_str == "c")
		if_verb = 0;
	
//	cout << "Verbose?" << if_verb << endl;

// Start simulating
	cout << "Initial state" << endl;
	simu_output(simworld1);
	for (int round = 1; round <= round_set; round ++)
	{
		cout << "Round " << round << endl;
		for (int cr_i = 0; cr_i < int(simworld1.numCreatures); cr_i ++)
		{
			cout << "Creature (" << simworld1.creatures[cr_i].species -> name << " "
				<< directName[simworld1.creatures[cr_i].direction] << " "
				<< simworld1.creatures[cr_i].location.r << " " << simworld1.creatures[cr_i].location.c
				<< ") takes action:";
			if (if_verb == 1)
				cout << endl;
			round_play(cr_i, simworld1, if_verb);
			if (if_verb)
				simu_output(simworld1);
		}
		if (if_verb == 0)
			simu_output(simworld1);
	}
}
