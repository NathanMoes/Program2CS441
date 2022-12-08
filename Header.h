#pragma once
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <cstdlib>

struct node {
	int position[8];
	int fitness;
};

class queens {
public:
	queens();
	queens(int size);
	~queens();
	int getfit(node&);
	int mutationpct();
	int getpopfit();
	void printgen();
	void mutation(node&);
	void crossover(node& dad, node& mom, node & child1, node & child2);
	void swappop(node * newpop);
	void initnewpop();
	node * pop;
	int population;
private:
protected:
};


void createnewpop(queens &origin);