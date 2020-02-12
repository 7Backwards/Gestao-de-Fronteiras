#include "Pessoa.h"
#include "Fronteira.h"

Pessoa::Pessoa(int partida, int chegada, string nome)	//Construtor da classe Pessoa
{
	Partida = partida;	//Inicializa a variável Partida
	Chegada = chegada;  //Inicializa a variável Chegada
	Nome = nome;        //Inicializa a variável Nome
	Info = new list<string>; //Cria a lista de informações que recebe quando atravessa fronteiras oficiais
	cam = new list<int>; //Cria a lista para o caminho que vai atravessar
	Percorreu = false;
}

Pessoa::~Pessoa(void)
{
	Info->clear(); //Liberta todos os elementos da lista Info deixando-a com size = 0
	delete Info; //Liberta o ponteiro para a lista das informaçoes
	cam->clear(); //Liberta todos os elementos da lista cam deixando-a com size = 0
	delete cam; //Liberta o ponteiro para a lista do caminho
}

string Pessoa::GetNome() {
	return Nome;
}
int Pessoa::GetChegada() {
	return Chegada;
}

int Pessoa::GetPartida() {
	return Partida;
}

void Pessoa::Mostrar() {	//Mostra o valor das variáveis pertencentes a  esta classe
	cout << "Nome:" << Nome << endl;
	cout << "Partida:" << Partida << endl;
	cout << "Chegada:" << Chegada << endl << endl;
}

int Pessoa::Memoria() {
	int memoria = 0;
	memoria += sizeof(string);		//Relativo ao Nome
	memoria += ((Nome.size() + 1) * sizeof(char));	//Relativo ao espaço ocupado pelo Nome somado com o '/0' e com o tamanho de cada char.
	memoria += sizeof(bool);	//Relativo ao Percorreu
	memoria += sizeof(int);		//Relativo à Partida
	memoria += sizeof(int);		//Relativo à Chegada
	for (auto i = Info->begin(); i != Info->end(); i++) { //Percorre a lista das informações
		memoria += sizeof(string); //Adiciona o tamanho da string de informaçoes
		memoria += ((*i).size() + 1) * sizeof(char); //Adiciona o tamanho de cada caracter dentro da string
	}
	memoria += sizeof(list<string>);
	for (auto i = cam->begin(); i != cam->end(); i++) { //Percorre a lista dos caminhos
		memoria += sizeof(int); //Adiciona o tamanho do int por cada fronteira que esteja na lista
	}
	memoria += sizeof(list<int>);	//Adiciona o tamanho da lista
	return memoria;
}

void Pessoa::PassaFronteira(int f) {	//Adiciona uma fronteira à lista cam (locais onde esta pessoa passou)
	cam->push_back(f);
}

bool Pessoa::GetPercorreu() {
	return Percorreu;
}

void Pessoa::SetPercorreu() {
	Percorreu = true;
}

