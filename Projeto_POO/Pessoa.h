#pragma once
#include <iostream>
#include <map>
#include <string>
#include <list>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;
class Fronteira;
class Pessoa
{
	string Nome; //nome da pessoa
	int Partida, Chegada;	//De onde a pessoa parte a onde quer chegar.
	list<string> *Info;		//Informação dada pelo país ao passar na fronteira oficial.
	list<int> *cam; //lista do caminho que percorreu
	bool Percorreu; //variavel para verificar se ja percorreu o caminho
public:
	Pessoa(int partida, int chegada, string nome); //construtor da pessoa
	~Pessoa(void); //destrutor da pessoa 
	int GetPartida(); //dá return da fronteira de onde quer partir
	string GetNome(); //dá return do nome da pessoa
	int GetChegada(); //dá return da fronteira para onde quer ir
	void Mostrar(); //mostra as informações da pessoa
	void PassaFronteira(int f); //adiciona à lista dos caminhos a fronteira por onde passou
	int Memoria(); //dá return da memoria ocupada por uma pessoa
	bool GetPercorreu(); //dá return da variavel percorreu
	void SetPercorreu(); //coloca a variavel percorreu a true
};

