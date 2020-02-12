#include "Fronteira.h"
#include "Aresta.h"

Fronteira::Fronteira(int cx, int cy)	//Construtor da classe Fronteira
{
	X = cx;	//Inicializa a variável X
	Y = cy;	//Inicializa a variável Y
}


Fronteira::~Fronteira(void)
{
	Adj.clear(); //Liberta os ponteiros para as arestas existentes na lista de arestas adjacentes
}

int Fronteira::GetTipo()
{
	return 0;
}

int Fronteira::GetPeso() //Senão houver a função no filho respetivo da return 0 por default
{
	return 0;
}

void Fronteira::Mostrar() {	//Mostra o conteúdo das variáveis desta classe
	cout << "Coordenada X:" << X << endl;
	cout << "Coordenada Y:" << Y << endl;
	cout << "Numero de pessoas que passaram pelo vértice:" << contador << endl;
}

int Fronteira::Memoria() { //Soma a memoria ocupada por cada variável e da lista de arestas adjacentes da fronteira, dando return no final.
	int memoria = 0;
	memoria += sizeof(int);	//Relativo à variável X
	memoria += sizeof(int); //Relativo à variável Y
	memoria += sizeof(int);	//Relativo à variavel contador
	for (auto i = Adj.begin(); i != Adj.end(); i++) {	//Percorre a lista das arestas adjacentes
		memoria += sizeof(Aresta *);	//Relativo a cada aresta da lista das arestas adjacentes
		memoria += (*i)->Memoria();		//Relativo à memória ocupada por cada aresta pertencente a essa lista
	}
	memoria += sizeof(list<Aresta *>);	//A própria lista
	return memoria;
}

int Fronteira::Getcontador() {
	return contador;	//Retorna o valor da variável contador
}

int Fronteira::GetCoordX() {
	return X;		//Retorna o valor da variável X
}

int Fronteira::GetCoordY() {
	return Y;	//Retorna o valor da variável Y
}

void Fronteira::Addadj(Aresta *novo) {
	Adj.push_back(novo);	//Adiciona uma aresta à lista das arestas adjacentes
}

list<Aresta*> Fronteira::GetFronteiraAdjacente() {
	return Adj;
}

void Fronteira::LimparAdj() {
	Adj.clear();
}

void Fronteira::Setcontador() {
	contador++;
}

