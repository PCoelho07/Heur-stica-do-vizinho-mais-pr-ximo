#ifndef __NNeighbor__HPP__
#define __NNeighbor__HPP__


#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <climits>

using std::vector;

struct City{
	int id, x, y, z = (int)NULL;
};

/*
	Início da classe NNeighbor(Nearest Neighbor - Vizinho mais próximo)
	Ps.: Não sei o motivo pelo qual coloquei isso em inglês, talvez seja só mania! (rs)
*/
class NNeighbor{
	private:
		vector<City> path;  //Vetor genérico que armazena o melhor caminho
		vector<City> cities; //Vetor genérico que armazena as cidades que serão recuperadas do arquivo
		int tamanho; // Tamanho da minha instancia (numero de cidades)
		float **custo; //Matriz dinâmica de distancias entre as cidades, é dinâmica pois o tamanho da minha instância pode variar
		char *nomeArq;
		char nome[20];// Nome da arquivo para ser impresso na saída
	public:
		NNeighbor(char *nomeArq);
		~NNeighbor();

	private:
		void readFile(); //Ler o grafo
		bool isCityInPath(int city); //Verifica se a cidade já foi visitada
		City findMin(City c); //Encontra a cidade mais próxima(Na verdade, é aqui que acontece a "mágica"!)
		void writeOut(); //Escrevo o arquivo da saída
		int getCityInVector(City c); // Pego o índice no vetor correspondente a cidade passada por parâmetro
		float costCalc();
	public:
		/* 
		---- Na verdade, as funções abaixo foram só para fins de depuração, elas não são de suma importância para o funcionamento do algoritmo  ---- 
		*/

		void showPath(); // Mostro o conteúdo do meu vector "path"
		void showCities(); //Mostro o contéudo do meu vector "cities"
		int getTam(){ return this->tamanho; }; //Pego a dimensão da minha instância
};

#endif