#pragma once
#include "Fronteira.h"
class Aresta
{
	int Origem, Destino;		//Pontos delimitadores da aresta.
	double Preco;				//Custo de passagem.

public:
	Aresta(int origem, int destino, double preco); //contrutor da aresta
	~Aresta(void); //destrutor da aresta
	void Mostrar(); //Mostra as informaçoes de cada aresta
	int GetOrigem(); //dá return da origem da aresta
	int GetDestino(); //dá return do destino da aresta
	double GetPreco(); //dá return do preço de uma aresta
	int Memoria(); //dá return do espaço ocupado por cada aresta
};

