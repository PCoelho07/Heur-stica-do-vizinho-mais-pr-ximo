#include "NNeighbor.hpp"

int main(int argc, char *argv[]){
	if(argc == 2){
		NNeighbor *n = new NNeighbor(argv[1]);
	}
	else
		std::cout << "\n  --- Arquivo nao informado! --- \n";
	return 0;
}