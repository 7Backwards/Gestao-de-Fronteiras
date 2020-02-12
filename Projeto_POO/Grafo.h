#pragma once
#include "Aresta.h"
#include "Fronteira_1.h"
#include "Fronteira_2.h"
#include "Fronteira_Oficial.h"

class Grafo
{
	map<int, Pessoa *> *Lista_Pessoas; //map com o id das pessoas e as suas informçoes
	map<int, Fronteira *> *FT; //Utilizado para definir várias fronteiras do grafo.
	list<Aresta *> *Lista_Aresta; //Lista de arestas do grafo.
public:
	Grafo(); //Construtor do grafo

	//Implemente o destrutor do Grafo;
	~Grafo();

	//Carregar os dados de ficheiros (do grafo e de pessoas);
	bool Load(const string &fich_grafo, const string &fich_pessoas);

	//Mostra a lista das pessoas lidas
	void MostrarPessoas();

	void MostrarFronteiras(); //Mostra a lista das fronteiras

	void MostrarArestas(); //Mostra a lista das arestas

	//Contar o número de nós/fronteiras do grafo;
	int ContarNos();

	//Contar o número de arestas/arcos do grafo;
	int ContarArcos();

	//Determinar toda a memória ocupada;
	int Memoria();

	//Determinar qual o nó/fronteira que tem mais arcos/aresta, se existirem vários devolve uma lista deles;
	list<int> *NoMaisArcos();

	//Verificar se um nó é adjacente de outro nó do Grafo;
	bool Adjacencia(int v1, int v2);

	//Determinar um caminho(não interessa se é o mais rápido!, é qualquer um!) de um nó/fronteira para outro.... //devolvendo o custo total;
	list<int> *Caminho(int v1, int v2, double &custo_total);

	//Determinar quais os vértices que estão isolados (Um vértice é isolado se não existe nenhum caminho até ele!);
	list<int> *VerticesIsolados();

	//Verificar se um dado vértice existe
	bool Search(int v);

	//Remover um dado vértice, também será necessário remover todas as arestas;
	bool RemoverVertice(int v);

	//Remover a aresta que liga 2 vértices;
	bool RemoverAresta(int v1, int v2);

	//Gravar para ficheiro em formato XML todas as informações do Grafo;
	void EscreverXML(const string &s);

	//Ler de um ficheiro em formato XML todo o Grafo (antes de ler deve ser apagado tudo o que estiver no Grafo); Se leu corretamente devolve //true, senão devolve false;
	bool LerXML(const string &s);

	//Devolver uma lista de todos os vértices/fronteiras de um dado tipo;
	list<int> *DevolveVerticesTipo(const string &tipo);

	//Determinar o caminho mínimo entre 2 nós, devolvendo o custo total;
	list<int> *CaminhoMinimo(int v1, int v2, double &custo_total);

	//Determinar o caminho máximo entre 2 nós (passando somente uma vez em cada vértice), devolvendo o custo total;
	list<int> *CaminhoMaximo(int v1, int v2, double &custo_total);

	//Será possível ir de uma fronteira(v1) a outra(v2), passando somente por fronteiras de um dado tipo?
	bool PossivelCaminho(int v1, int v2, int TipoFronteira);

	//Assumindo que todas as pessoas (do ficheiro) andaram em viagem, qual foi a fronteira com menos tráfego/visitas? (No caso de serem várias,// deve devolver uma lista com as fronteiras);
	void FronteirasMenosVisitadas(list<int> &Lv);

	//Dada uma fronteira (v1), determinar todas as fronteiras onde não é possível chegar apartir de v1. Deve devolver uma lista dessas fronteiras!;
	void SitiosInacessiveisAPartirDe(int V1, list<int> &Lv);

	//Será possível ir de uma fronteira(v1) a outra(v2), passando por qualquer tipo de fronteiras?
	bool PossivelCaminho_Independente_Tipo(int v1, int v2);

	//Função que mostra o menu
	int Menu();

	//Função que verifica qual a opção do menu selecionada
	void TrataMenu(int opcao);
};