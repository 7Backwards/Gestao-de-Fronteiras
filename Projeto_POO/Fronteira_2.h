#pragma once
#include "fronteira.h"
class Fronteira_2 :
	public Fronteira
{
public:
	Fronteira_2(int cx, int cy); //construtor de uma fronteira do tipo 2
	~Fronteira_2(void); //destrutor de uma fronteira do tipo 2
	int GetTipo(); //dá return do tipo de fronteira
	int GetPeso(); //dá return do peso que tem de levar ao atravessar uma fronteira
	void Mostrar(); //mostra as infromações de uma fronteira
	int Getcusto(); //dá return do custo ao atravessar uma fronteira
};

