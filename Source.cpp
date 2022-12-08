#include "Header.h"

//gen 5000 run 1000 iterations get 28 !!!!!!! 28 = good
int main() {
	srand(time(NULL));
	int chrome = 0;
	int num = 0;
	int iterations = 0;
	std::cout << "Enter population number\n" << std::endl;
	std::cin >> num;
	std::cin.ignore(100, '\n');
	queens testing(num);
	std::cout << "initial population" << std::endl;
	testing.printgen();
	//testing.printgen();
	std::cout << "Pop fit: " << testing.getpopfit() << std::endl;
	//createnewpop(testing);
	std::cout << "Enter number of itterations to compute" << std::endl;
	std::cin >> iterations;
	std::cin.ignore(100, '\n');
	for(int i = 0; i < iterations; i++){
		//std::cout << "NEW POPULATION HERE" << std::endl;
		std::cout << "Computing generation: " << i << std::endl;
		testing.initnewpop();
		//testing.printgen();
	}
	std::cout << "Final POPULATION HERE" << std::endl;
	testing.printgen();
	exit(EXIT_SUCCESS);
}

//class that inits the nodes
//have 2 constructors, one random one that takes 2 args from mom and pop
//max of 28 attacking pairs
//init gen 1 and then do random selction across the set and mutate random too
//once it reached end of gen 1 gen+=1 and becomes gen 2. maybe save most fit thing?
//1 in 1000 mutation chance
//let extern function create new gen, intern function swap em
//randomise select check if hits chance in the total pool, if not then keep seraching if so the use it as parrent
//getpopfit then populate each node in by the number of its fitness function EX: 100 fitness 10 for a node. Makes 0-9 point to the node.