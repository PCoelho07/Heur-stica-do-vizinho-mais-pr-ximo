#include "NNeighbor.hpp"
#include <ctime>
#include <cmath>
#include <sys/time.h>
#include <cstring>

NNeighbor::NNeighbor(char *nomeArq){
	City startCity;
	this->nomeArq = nomeArq;
	this->readFile();
	srand((unsigned)time(NULL));

	int id = 1 + (rand() % this->tamanho);
	vector<City>::iterator c = this->cities.begin();

	std::cout << id << "\n";
	// //Escolho uma cidade aleatoria para dar início a execução
	while(c != this->cities.end()){
		if(c->id == id){
			startCity = (*c);
		}
		c++;
	}
	this->path.push_back(startCity);

	City current = startCity;
	vector<City>::iterator it;
	while(this->path.size() < this->tamanho){
		City nextCity = this->findMin(current);
		if(nextCity.id > 0){
			this->path.push_back(nextCity);
			current = nextCity;
		}
		else{
			std::cout << "Vizinho mais proximo nao encontrado!!\n Verifique a instancia usada!!\n";
			exit(0);
		}

	}

	this->writeOut(); //Escreve o arquivo de saída com o melhor caminho
}

void NNeighbor::readFile(){
	
	// char comentario[50]; //COMMENNT
	char tipo[20]; // TYPE
	char formato[20]; // EDGE_WEIGHT_TYPE
	char flag[255];

	FILE *f = fopen(this->nomeArq, "r");
	// FILE *fout = fopen("out.txt", "a");

	if(f == NULL){
		std::cout << "\nArquivo nao existe!!\n";
		exit(0);
	}

	/* 
		Captura apenas o cabeçalho do arquivo 
		Obs.: Adaptado do código do prof. Givanaldo
	*/
	while (!feof(f)){
		fscanf(f, "%s", flag);
		if(strcmp(flag, "NAME:") == 0)
			fscanf(f, " %s", this->nome);
		else if(strcmp(flag, "NAME") == 0)
			fscanf(f, " : %s", this->nome);
		else if (strcmp(flag, "DIMENSION:") == 0)
			fscanf(f, " %d", &this->tamanho);
		else if (strcmp(flag, "DIMENSION") == 0)
			fscanf(f, " : %d", &this->tamanho);
		else if (strcmp(flag, "EDGE_WEIGHT_TYPE:") == 0)
			fscanf(f, " %s", formato);
		else if (strcmp(flag, "EDGE_WEIGHT_TYPE") == 0)
			fscanf(f, " : %s", formato);
		else if (strcmp(flag, "TYPE:") == 0)
			fscanf(f, " %s", tipo);
		else if (strcmp(flag, "TYPE") == 0)
			fscanf(f, " : %s", tipo);
		else if (strcmp(flag, "NODE_COORD_SECTION") == 0)
			break;
		else if (strcmp(flag, "EOF") == 0) {
			printf("ERRO: O campo EDGE_WEIGHT_FORMAT ou NODE_COORD_SECTION nao existe no arquivo %s.\n", nomeArq);
			exit(0);
		}
	}

	/* Carrego apenas as cidades e suas coordenadas no vetor */
	City c;
	int i = 0;
	while(i < this->tamanho){
		fscanf(f, "%d %d %d\n", &c.id, &c.x, &c.y);
		this->cities.push_back(c);
		i++;
	}

	this->custo = new float *[this->tamanho];
	for (int i = 0; i < this->tamanho; ++i){ 
		this->custo[i] = new float[this->tamanho];
	}
	/* Alimento a matriz de distancias entre as cidades */
	for(int i = 0; i < this->tamanho; i++){
		for(int j = 0; j < this->tamanho; j++){
			if(i == j)
				custo[i][j] = 0;
			else{
				custo[i][j] = (float)sqrt(pow(this->cities.at(i).x - this->cities.at(j).x, 2) + pow(this->cities.at(i).y - this->cities.at(j).y, 2));
			}
			custo[j][i] = custo[i][j];
		}
	}

	fclose(f);
}

bool NNeighbor::isCityInPath(int cityId){
	vector<City>::iterator it = this->path.begin(); 
	if(this->path.size() > 0){
		while(it != this->path.end()){
			if(it->id == cityId){
				return true;
			}
			it++;
		}
	}	
	return false;
}

City NNeighbor::findMin(City c){
	City nextCity;
	vector<City>::iterator it;

	int icity = this->getCityInVector(c);
	float min = INT_MAX;
	nextCity.id = 0;

	for(int j = 0; j < this->tamanho; j++){		
		if(custo[icity][j] > 0){
			if(custo[icity][j] < min && !isCityInPath(this->cities.at(j).id)){
				min = custo[icity][j];
				nextCity = this->cities.at(j);
			}			
		}		
	}
	return nextCity;	
}

float NNeighbor::costCalc(){
	int custoFinal = 0;

	for(int i = 0; i < this->tamanho-1;  ++i){
		// custoFinal += this->custo[this->path.at(i).id-1][this->path.at(i+1).id-1];
		custoFinal += this->custo[getCityInVector(this->path[i])][getCityInVector(this->path[i+1])];
	}
	// custoFinal += this->custo[this->path[this->tamanho-1].id-1][this->path[0].id-1];	
	custoFinal += this->custo[getCityInVector(this->path[this->tamanho-1])][getCityInVector(this->path[0])];
	return custoFinal;
}


int NNeighbor::getCityInVector(City c){
	for(int i =0; i < this->tamanho; i++){
		if(this->cities.at(i).id == c.id)
			return i;
	}
	return 0;
}

void NNeighbor::writeOut(){
	vector<City>::iterator it = this->path.begin();
	printf("\n%d\n", (int)this->costCalc());
	while(it != this->path.end()){
		printf("%d %d %d\n", it->id, it->x, it->y);
		it++;
	}
}

void NNeighbor::showPath(){
	vector<City>::iterator it = this->path.begin();
	std::cout << "\n --- Melhor caminho --- \n";
	while(it != this->path.end()){
		std::cout << it->id << "\n";
		it++;	
	}
}

void NNeighbor::showCities(){
	vector<City>::iterator it = this->cities.begin();
	std::cout << "\n --- Cidades --- \n";
	while(it != this->cities.end()){
		std::cout << it->id << "\n";
		it++;		
	}
}