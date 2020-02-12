#include "Aresta.h"


Aresta::Aresta(int origem, int destino, double preco)	//Construtor da classe aresta
{
	Origem = origem;		//Inicializa a variável Origem
	Destino = destino;		//Inicializa a variável Destino
	Preco = preco;			//Inicializa a variável Preco
}


Aresta::~Aresta(void)
{
}

void Aresta::Mostrar() {		//Mostra as variáveis existentes nesta classe
	cout << "Origem:" << Origem << endl;
	cout << "Destino:" << Destino << endl;
	cout << "Preço:" << Preco << endl << endl;
}

int Aresta::GetOrigem() {	//Retorna a origem da aresta
	return Origem;
}

int Aresta::GetDestino() {	//Retorna o destino da aresta
	return Destino;
}

double Aresta::GetPreco() {	//Retorna o preço da aresta
	return Preco;
}

int Aresta::Memoria() { //soma a memoria ocupada por cada variavel da aresta e da return
	int memoria = 0;
	memoria += sizeof(int);	//Relativo à origem
	memoria += sizeof(int);	//Relativo ao destino
	memoria += sizeof(double);	//Relativo ao preco
	return memoria;
}