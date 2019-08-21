#ifndef SIMULATION_H
#define SIMULATION_H


void simu_output(const world_t &world);
void round_play(int cr_i, world_t &theWorld, int if_verb);

void hop(int cr_i, world_t &theWorld);
void left(int cr_i, world_t &theWorld);
void right(int cr_i, world_t &theWorld);
void infect(int cr_i, world_t &theWorld);
bool ifenemy(int cr_i, world_t &theWorld);
bool ifempty(int cr_i, world_t &theWorld);
bool ifsame(int cr_i, world_t &theWorld);
bool ifwall(int cr_i, world_t &theWorld);
void go(unsigned int n, int cr_i, world_t &theWorld);

point_t front_loc(int cr_i, world_t &theWorld);

#endif