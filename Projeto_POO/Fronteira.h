#pragma once
#include "Pessoa.h"


using namespace std;
class Aresta;
class Fronteira
{
	int X, Y, contador; //coordenadas das fronteiras e contador do numero de pessoas que ja la passaram
	list<Aresta *> Adj; //lista de arestas adjacentes à fronteira

public:
	Fronteira(int cx, int cy); //construtor da fronteira
	~Fronteira(void); //destrutor da fronteira
	virtual int GetTipo(); //dá return do tipo de cada fronteira usando o virtual
	virtual int GetPeso(); //dá return do peso (se houver) de cada fronteira usando o virtual
	virtual void Mostrar(); //dá return do tipo de cada fronteira usando o virtual
	int Memoria(); //dá return da memoria ocupada por cada fronteira
	int Getcontador(); //dá return do numero de pessoas que já passaram na fronteira
	int GetCoordX(); //dá return da coordenada x da fronteira
	int GetCoordY(); //dá return da coordenada y da fronteira
	void Addadj(Aresta *novo); //adiciona uma aresta à lista de arestas adjcentes de uma fronteira
	list < Aresta*> GetFronteiraAdjacente(); //dá return da lista de arestas adjacentes de uma fronteira
	virtual int Getcusto() { return 0; } //dá return do custo (se houver) ao atravessae cada fronteira usando o virtual
	void LimparAdj(); //limpa a lista de arestas adjacentes de uma fronteira
	void Setcontador(); //incrementa o numero de pessoas que atravessaram uma fronteira
};

