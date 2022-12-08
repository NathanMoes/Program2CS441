#include "Header.h"



queens::queens() {
	pop = new node[100];
	for (int i = 0; i < 100; i++) {
		//init node
		for (int j = 0; j < 8; j++) {
			pop[i].position[j] = rand() % 8 + 1;
		}
		//set fitness values
		queens::getfit(pop[i]);
	}
	population = 100;
}

queens::queens(int size) {
	pop = new node[size];
	for (int i = 0; i < size; i++) {
		//init node
		for (int j = 0; j < 8; j++) {
			pop[i].position[j] = rand() % 8 + 1;
		}
		//set fitness values
		queens::getfit(pop[i]);
	}
	population = size;
}
queens::~queens() {

}
int queens::getfit(node& current) {
	int count = 0;
	int compq = 0;
	int xdif = 0;
	int ydif = 0;
	for (int i = 0; i < 8; i++) {
		compq = current.position[i];
		for (int j = (i+1); j < 8; j++) {
			if (compq == current.position[j])
				count++;
			xdif = abs(j - i);
			ydif = abs(current.position[j] - compq);
			if (xdif == ydif)
				count++;
		}
	}
	current.fitness = (28 - count);
	return count;
}

void queens::printgen() {
	for (int i = 0; i < population; i++) {
		for (int j = 0; j < 8; j++) {
			std::cout << pop[i].position[j] << ",";
		}
		std::cout << "FITNESS: " << pop[i].fitness;
		std::cout << std::endl;
	}
}

void queens::mutation(node& current) {
	int tomu = rand() % 8;
	int newval = rand() % 8 + 1;
	current.position[tomu] = newval;
}

void queens::crossover(node& dad, node& mom, node & child1, node & child2) {
	//random select crossover point
	//values after crossover point chance for future offspring.
	//
	//int index = 0;
	int crosspoint = rand() % 7; //set to 7 so that it will corss over at least 1 string peice
	//now copy across the data from each thing to child. Child1 = dad, child2 = mom
	//take at cross point for child1 to = child2's after cross point data.
	//do for index = 0; index < 8; index++;
	//if index > crosspoint then crossover;
	for (int index = 0; index < 8; index++) {
		if (index <= crosspoint) {
			child1.position[index] = dad.position[index];
			child2.position[index] = mom.position[index];
		}
		else {
			child1.position[index] = mom.position[index];
			child2.position[index] = dad.position[index];
		}
	}
	getfit(child1);
	getfit(child2);
}

int queens::mutationpct() {
	int check = rand() % 1000;
	if (check == 0)
		return 1;
	else
		return 0;
}


void queens::swappop(node* newpop) {
	delete []pop;
	pop = newpop;
}

int queens::getpopfit() {
	int count = 0;
	for (int i = 0; i < population; i++) {
		count += pop[i].fitness;
	}
	return count;
}

void createnewpop(queens& origin) {
	int size = origin.getpopfit();
	node *distro;
	//distro = new node*[size];
	int localfit = 0;
	//for 1 to pop size
	//i-1 access it for the fit num
	for (int i = 0; i < origin.population; i++)
	{
		localfit = origin.pop[i].fitness;
		for (int j = 0; j < localfit; j++)
		{
			//*distro[i] = origin.pop[i]; fix this
		}
	}
	std::cout << "SIZE OF IS: " << sizeof(distro) << std::endl;
}

void queens::initnewpop() {
	//need to make this work on standard distrobution
	//maybe get full population fitness, take current node fitness. 
	//use current/fullpop to get rand value.
	//if value - rand > 0;
	//if value - rand >= 0; if we use rand() % fullpop; and not fullpop +1; 
	//create array size of value, keep an index to check how full, keep making more until index = full;
	/*int size = getpopfit();
	int index = 0;
	int localfit = 0;
	node** newpop = new node* [size];
	for (int k = 0; k < size; k++) {
		newpop[k] = NULL;
	}
	for (int i = 0; i < size; i++) {
		localfit = pop[index].fitness;
		for (int j = 0; j < localfit; j++) {
			newpop[i] = &pop[index];
			i++;
		}
		index++;
	}
	for (int h = 0; h < population; h++) {
		if(newpop[h] != NULL)
			std::cout << newpop[h]->fitness << std::endl;
	}
	std::cout << "SIZE OF IS: " << sizeof(*newpop) << std::endl;
	*/
	node* mom = NULL;
	node* dad = NULL;
	node* child1 = NULL;
	node* child2 = NULL;
	int index = 0; 
	int selection = 0;
	int check = 0;
	int size = getpopfit();
	node* newpop = new node[population];
	while (index < population)
	{
		if (selection >= population) //bounds checking, plus reset back
		{
			selection = 0;
			continue;
		}
		int currentfit = pop[selection].fitness;
		//do rand value in size, if check - size >= 0 then do thing
		while (!mom && !dad)
		{
			if (selection >= population)
				selection = 0;
			check = rand() % size;
			if ((pop[selection].fitness - check) >= 0)
			{
				if (!mom)
					mom = &pop[selection];
				if (!dad)
					dad = &pop[selection];
			}
			selection++;
		}
		//init child1
		//init child2
		child1 = &newpop[index];
		child2 = &newpop[index + 1];
		crossover(*dad, *mom, *child1, *child2);
		if (mutationpct() == 1)
			mutation(*child1);
		if (mutationpct() == 1)
			mutation(*child2);
		index += 2;
		mom = NULL;
		dad = NULL;
	}
	delete []pop;
	pop = newpop;
}