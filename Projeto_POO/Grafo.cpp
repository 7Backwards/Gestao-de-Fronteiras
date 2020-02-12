#include "Grafo.h"

Grafo::Grafo() {
	cout << "Passei em " << __FUNCTION__ << endl;
	Lista_Aresta = new list<Aresta*>; //cria a lista de arestas
	Lista_Pessoas = new map<int, Pessoa*>; //cria o mapa para as pessoas
	FT = new map<int, Fronteira*>; //cria o mapa para as fronteiras
}

Grafo::~Grafo() {
	cout << "Passei em " << __FUNCTION__ << endl;
	for (auto i = FT->begin(); i != FT->end(); i++) { //percorre o mapa das fronteiras 
		delete (*i).second; //liberta a memoria ocupada por cada fronteira
	}
	FT->clear(); //liberta os ponteiros para as fronteiras
	delete FT; //liberta o ponteiro para o mapa
	for (auto i = Lista_Aresta->begin(); i != Lista_Aresta->end();) { //percorre a lista das arestas
		delete *i++; //liberta a memoria ocupada por cada aresta
	}
	Lista_Aresta->clear(); //liberta os ponteiros para as arestas
	delete Lista_Aresta; //liberta o ponteiro para a lista
	for (auto i = Lista_Pessoas->begin(); i != Lista_Pessoas->end(); i++) { //percorre o mapa das pessoas
		delete (*i).second; //liberta a memoria ocupada por cada pessoa
	}
	Lista_Pessoas->clear(); //liberta os ponteiros para as pessoas
	delete Lista_Pessoas; //liberta o ponteiro para o mapa
}

int Grafo::Menu() { //mostra as opções e le a opção escolhida
	int opcao = 0;
	cout << "----------------------------------------" << endl;
	cout << "|             GRAFO                    |" << endl;
	cout << "|--------------------------------------|" << endl;
	cout << "| 1. Contar numero de fronteiras       |" << endl;
	cout << "| 2. Contar numero de arestas          |" << endl;
	cout << "| 3. Memoria ocupada pelo grafo        |" << endl;
	cout << "| 4. Fronteira com mais arcos          |" << endl;
	cout << "| 5. Verificar adjacencia              |" << endl;
	cout << "| 6. Caminho entre duas fronteiras     |" << endl;
	cout << "| 7. Vertices isolados                 |" << endl;
	cout << "| 8. Search (Procura fronteira)        |" << endl;
	cout << "| 9. Remover um vertice                |" << endl;
	cout << "| 10. Remover uma aresta               |" << endl;
	cout << "| 11. Escrever XML                     |" << endl;
	cout << "| 12. Ler XML                          |" << endl;
	cout << "| 13. Devolve vertices de um tipo      |" << endl;
	cout << "| 14. Possivel caminho                 |" << endl;
	cout << "| 15. Possivel caminho(Tipo Fronteira) |" << endl;
	cout << "| 16. Fronteiras menos visitadas       |" << endl;
	cout << "| 17. Caminho (Pessoas)                |" << endl;
	cout << "| 18. Caminho minimo                   |" << endl;
	cout << "| 19. Caminho maximo                   |" << endl;
	cout << "| 20. Sitios Inacessiveis              |" << endl;
	cout << "| 21. Mostrar Dados                    |" << endl;
	cout << "| 22. Testar Memoria                   |" << endl;
	cout << "|--------------------------------------|" << endl;
	cout << "| 0. Sair                              |" << endl;
	cout << "----------------------------------------" << endl;

	cout << "Qual a opcao que pretende selecionar?" << endl;
	while (!(cin >> opcao) || opcao < 0 || opcao>22) { //Verifica se a opçao é valida
		cin.clear(); //Limpa o cin para não haver erros no input dos dados
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Opcao invalida!Introduza uma nova opcao" << endl;
	}
	return opcao;
}

void Grafo::TrataMenu(int opcao) { //Recebe a opção escolhida e chama as funçoes correspondentes
	switch (opcao) {
	case 0: {
		break;
	}
	case 1: {//Contar o numero de nos
		int Numero_Nos = ContarNos();
		cout << "O numero de vertices existentes no grafo: " << Numero_Nos << endl;
		break;
	}
	case 2: {//Contar o numero de arcos
		int Numero_Arestas = ContarArcos();
		cout << "O numero de arestas existentes no grafo: " << Numero_Arestas << endl;
		break;
	}
	case 3: {//Calcula a memoria ocupada
		int Mem = Memoria();
		cout << "Memoria ocupada: " << Mem << "bytes." << endl;
		break;
	}
	case 4: { //mostra os nos com mais arcos
		list<int> *Arcos = NoMaisArcos();
		cout << "Fronteiras com mais arcos: " << endl;
		for (auto i = Arcos->begin(); i != Arcos->end(); i++) //percorre a lista de nos com mais arcos para mostrar
			cout << (*i) << endl;
		if (Arcos) //liberta a memoria usada
			Arcos->clear();
		delete Arcos;
		break;
	}
	case 5: { //verifica se ha adjacencia entres dois vertices
		int v1, v2;
		cout << "Introduza o ID de duas fronteiras para verificar adjacencia: " << endl;
		while (!(cin >> v1 >> v2)) { //Verifica se a opçao é valida
			cin.clear(); //Limpa o cin para não haver erros no input dos dados
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Opcao invalida!Introduza uma nova opcao" << endl;
		}
		if (Adjacencia(v1, v2))
			cout << "Ha adjacencia." << endl;
		else
			cout << "Nao ha adjacencia." << endl;
		break;
	}
	case 6: { //mostra um camihno possivel entre duas fronteiras se existir
		int v1, v2;
		double custo_total = 0;
		list<int> *Cam;
		cout << "Introduza o ID de duas fronteiras para obter um caminho: " << endl;
		while (!(cin >> v1 >> v2)) { //Verifica se a opçao é valida
			cin.clear(); //Limpa o cin para não haver erros no input dos dados
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Opcao invalida!Introduza uma nova opcao" << endl;
		}
		Cam = Caminho(v1, v2, custo_total);
		if (Cam) { //verifica se existe caminho
			cout << "Caminho:" << endl;
			for (auto i = Cam->begin(); i != Cam->end(); i++) //percorre a lista do caminho para mostrar
				cout << (*i) << endl;
			cout << "Custo total:" << custo_total << endl;
		}
		if (Cam) //liberta a lista
			Cam->clear();
		delete Cam;
		break;
	}
	case 7: { //mostra a lista de vertices isolados se existirem
		cout << "Vertices isolados: " << endl;
		list<int> *Vertices_Iso = VerticesIsolados();
		for (auto i = Vertices_Iso->begin(); i != Vertices_Iso->end(); i++) //percorre a lista de nos isolados para mostrar
			cout << *i << endl;
		if (Vertices_Iso) //liberta a lista
			Vertices_Iso->clear();
		delete Vertices_Iso;
		break;
	}
	case 8: { //verifica se um dado vertice existe
		int vertice;
		cout << "Introduza o ID de um vertice:" << endl;
		while (!(cin >> vertice)) { //Verifica se a opçao é valida
			cin.clear(); //Limpa o cin para não haver erros no input dos dados
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Opcao invalida!Introduza uma nova opcao" << endl;
		}
		if (Search(vertice))
			cout << "O vertice que pesquisou existe." << endl;
		else
			cout << "O vertice que pesquisou nao existe." << endl;
		break;
	}
	case 9: { //remove um vertice se possivel
		int vertice;
		cout << "Introduza o ID do vertice que pretende remover:" << endl;
		cin >> vertice;
		if (RemoverVertice(vertice))
			cout << "Vertice removido com sucesso." << endl;
		else
			cout << "Impossivel remover o vertice pretendido." << endl;
		break;
	}
	case 10: { //remove uma aresta se possivel
		int v1, v2;
		cout << "Introduza o ID dos vertice que delimitam a aresta:" << endl;
		while (!(cin >> v1 >> v2)) { //Verifica se a opçao é valida
			cin.clear(); //Limpa o cin para não haver erros no input dos dados
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Opcao invalida!Introduza uma nova opcao" << endl;
		}
		if (RemoverAresta(v1, v2))
			cout << "Aresta removida com sucesso." << endl;
		else
			cout << "Impossivel remover a aresta pretendido." << endl;
		break;
	} //escreve os dados num ficheiro xml
	case 11: {
		string Nome_Fich;
		cout << "Introduza o nome do ficheiro:" << endl;
		cin >> Nome_Fich;
		EscreverXML(Nome_Fich);
		break;
	}
	case 12: { //le os dados de um ficheiro xml
		string Nome_Fich;
		cout << "Introduza o nome do ficheiro:" << endl;
		cin >> Nome_Fich;
		LerXML(Nome_Fich);
		break;
	}
	case 13: { //mostra os vertices de um dado tipo
		string tipo;
		list<int> *VerticesTipo;
		cout << "Introduza o tipo de vertice que pretende:" << endl;
		while (!(cin >> tipo) || stoi(tipo) < 0 || stoi(tipo) > 3) { //Verifica se a opçao é valida
			cin.clear(); //Limpa o cin para não haver erros no input dos dados
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Opcao invalida!Introduza uma nova opcao" << endl;
		}
		VerticesTipo = DevolveVerticesTipo(tipo);
		cout << "Vertices do tipo indicado:" << endl;
		for (auto i = VerticesTipo->begin(); i != VerticesTipo->end(); i++) //percorre a lista de nos do mesmo tipo para mostrar
			cout << (*i) << endl;
		if (VerticesTipo) //liberta a lista de vertices
			VerticesTipo->clear();
		delete VerticesTipo;
		break;
	}
	case 14: { //verifica se existe caminho entre 2 vertices	
		int v1, v2;
		cout << "Introduza os vertices que pretende verificar a existencia de caminho: " << endl;
		cout << "Origem: " << endl;
		while (!(cin >> v1)) { //Verifica se a opçao é valida
			cin.clear(); //Limpa o cin para não haver erros no input dos dados
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Opcao invalida!Introduza uma nova opcao" << endl;
		}
		cout << "Destino: " << endl;
		while (!(cin >> v2)) { //Verifica se a opçao é valida
			cin.clear(); //Limpa o cin para não haver erros no input dos dados
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Opcao invalida!Introduza uma nova opcao" << endl;
		}
		if (PossivelCaminho_Independente_Tipo(v1, v2))
			cout << "Existe um caminho entre estes dois vertices." << endl;
		else
			cout << "Nao existe nenhum caminho entre estes dois vertices." << endl;
		break;
	}
	case 15: { //verifica se existe caminho entre 2 vertices atravessando vertices de um dado tipo
		int tipo;
		int v1, v2;
		cout << "Introduza o tipo de vertices que pretende: (Tipo 1,2,3)" << endl;
		while (!(cin >> tipo) || tipo < 0 || tipo>3) { //Verifica se a opçao é valida
			cin.clear(); //Limpa o cin para não haver erros no input dos dados
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Opcao invalida!Introduza uma nova opcao" << endl;
		}
		cout << "Introduza os vertices que pretende verificar a existencia de caminho: " << endl;
		cout << "Origem: " << endl;
		while (!(cin >> v1)) { //Verifica se a opçao é valida
			cin.clear(); //Limpa o cin para não haver erros no input dos dados
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Opcao invalida!Introduza uma nova opcao" << endl;
		}
		cout << "Destino: " << endl;
		while (!(cin >> v2)) { //Verifica se a opçao é valida
			cin.clear(); //Limpa o cin para não haver erros no input dos dados
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Opcao invalida!Introduza uma nova opcao" << endl;
		}
		if (PossivelCaminho(v1, v2, tipo))
			cout << "Existe um caminho entre estes dois vertices atravessando somente fronteiras do tipo " << tipo << "." << endl;
		else
			cout << "Nao existe nenhum caminho entre estes dois vertices atravessando somente fronteiras do tipo" << tipo << "." << endl;
		break;
	}
	case 16: { //mostra as fronteiras menos visitadas
		list<int> *l = new list<int>;
		FronteirasMenosVisitadas(*l);
		if (l) {
			cout << "Frontariras menos visitadas:" << endl;
			for (auto i = l->begin(); i != l->end(); i++) //percorre a lista de fronteiras para mostrar
				cout << "Fronteira" << (*i) << "-" << FT->find(*i)->second->Getcontador() << "visitas" << endl;
			l->clear(); //liberta a lista
		}
		delete l;
		break;
	}
	case 17: { //faz uma pessoa percorrer o tipo de caminho desejado
		int id, cam;
		list<int> *l;
		int tam = Lista_Pessoas->size();
		double custo_total = 0;
		MostrarPessoas();
		cout << "Da lista de pessoas escolha uma para executar o seu caminho e indique o seu id:" << endl; //escolhe a pessoa
		while (!(cin >> id) || id < 0 || id>tam || Lista_Pessoas->find(id)->second->GetPercorreu()) { //verifica se a pessoa existe
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //limpa o input
			cout << "ID invalido! Introduza novo id" << endl;
		}
		auto i = Lista_Pessoas->find(id);
		cout << "1. Caminho qualquer" << endl;
		cout << "2. Caminho minimo" << endl;
		cout << "3. Caminho maximo" << endl;
		cout << "Escolha qual o tipo de caminho que pretende percorrer:" << endl;
		while (!(cin >> cam) || cam < 0 || cam>3) { //escolhe o tipo de camihno e verifica se é valido
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //limpa o input
			cout << "Caminho invalido! Introduza nova opcao" << endl;
		}
		switch (cam) { //executa a funçao do tipo de caminho conforme escolhido
		case 1: {
			l = Caminho(i->second->GetPartida(), i->second->GetChegada(), custo_total);
			if (!l) //verifica se existe caminho
				cout << "Não existe caminho" << endl;
			else {
				cout << "Caminho" << endl;
				for (auto j = l->begin(); j != l->end(); j++) {
					cout << *j << endl; //mostra o caminho
					i->second->PassaFronteira(*j); //coloca o caminho percorrido na lista do caminho da pessoa
					FT->find(*j)->second->Setcontador(); //incrementa o valor do contador de pessoas que percorreram a fronteira
				}
				cout << "Custo total:" << custo_total << endl; //mostra o custo total ao percorrer o caminho
				Lista_Pessoas->find(id)->second->SetPercorreu(); //colocar a true a variavel percorreu da pessoa 
			}
			break;
		}
		case 2: {
			l = CaminhoMinimo(i->second->GetPartida(), i->second->GetChegada(), custo_total);
			if (!l) //verifica se existe caminho
				cout << "Não existe caminho" << endl;
			else {
				cout << "Caminho" << endl;
				for (auto j = l->begin(); j != l->end(); j++) {
					cout << *j << endl; //mostra o caminho
					i->second->PassaFronteira(*j); //coloca o caminho percorrido na lista do caminho da pessoa
					FT->find(*j)->second->Setcontador(); //incrementa o valor do contador de pessoas que percorreram a fronteira
				}
				cout << "Custo total:" << custo_total << endl; //mostra o custo total ao percorrer o caminho
				Lista_Pessoas->find(id)->second->SetPercorreu(); //colocar a true a variavel percorreu da pessoa
			}
			break;
		}
		case 3: {
			l = CaminhoMaximo(i->second->GetPartida(), i->second->GetChegada(), custo_total);
			if (!l) //verifica se existe caminho
				cout << "Não existe caminho" << endl;
			else {
				cout << "Caminho" << endl;
				for (auto j = l->begin(); j != l->end(); j++) {
					cout << *j << endl; //mostra o caminho
					i->second->PassaFronteira(*j); //coloca o caminho percorrido na lista do caminho da pessoa
					FT->find(*j)->second->Setcontador(); //incrementa o valor do contador de pessoas que percorreram a fronteira
				}
				cout << "Custo total:" << custo_total << endl; //mostra o custo total ao percorrer o caminho
				Lista_Pessoas->find(id)->second->SetPercorreu(); //colocar a true a variavel percorreu da pessoa
			}
			break;
		}
		}
		break;
	}
	case 18: { //calcula o caminho minimo entre 2 vertices se existirem
		int v1, v2;
		list<int> *CaminhoMin = new list<int>;
		cout << "Introduza o vertice de partida:" << endl;
		while (!(cin >> v1)) { //Verifica se a opçao é valida
			cin.clear(); //Limpa o cin para não haver erros no input dos dados
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Opcao invalida!Introduza uma nova opcao" << endl;
		}
		cout << "Introduza o vertice de chegada:" << endl;
		while (!(cin >> v2)) { //Verifica se a opçao é valida
			cin.clear(); //Limpa o cin para não haver erros no input dos dados
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Opcao invalida!Introduza uma nova opcao" << endl;
		}
		double Custo_Total = numeric_limits<double>::infinity();
		CaminhoMin = CaminhoMinimo(v1, v2, Custo_Total);
		if (CaminhoMin != NULL) { //verifica se existe caminho
			cout << "Custo total: " << Custo_Total << endl; //mostra o custo
			cout << "Caminho minimo: " << endl;
			for (auto i = CaminhoMin->begin(); i != CaminhoMin->end(); i++) //mostra o caminho
				cout << *i << endl;
			CaminhoMin->clear(); //liberta a lista
		}
		delete CaminhoMin;
		break;
	}
	case 19: { //calcula o caminho maximo entre 2 vertices se existirem
		int v1, v2;
		list<int> *CaminhoMax = new list<int>;
		cout << "Introduza o vertice de partida:" << endl;
		while (!(cin >> v1)) { //Verifica se a opçao é valida
			cin.clear(); //Limpa o cin para não haver erros no input dos dados
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Opcao invalida!Introduza uma nova opcao" << endl;
		}
		cout << "Introduza o vertice de chegada:" << endl;
		while (!(cin >> v2)) { //Verifica se a opçao é valida
			cin.clear(); //Limpa o cin para não haver erros no input dos dados
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Opcao invalida!Introduza uma nova opcao" << endl;
		}
		double Custo_Total = numeric_limits<double>::infinity();
		CaminhoMax = CaminhoMaximo(v1, v2, Custo_Total);
		if (CaminhoMax != NULL) { //verifica se existe caminho
			cout << "Custo total: " << Custo_Total << endl; //mostra o custo
			cout << "Caminho maximo: " << endl;
			for (auto i = CaminhoMax->begin(); i != CaminhoMax->end(); i++) //mostra o caminho
				cout << *i << endl;
			CaminhoMax->clear(); //liberta a lista
		}
		delete CaminhoMax;
		break;
	};
	case 20: { //mostra os vertices inacessiveis a partir de um dado vertice
		list<int> LV;
		int v1;
		cout << "Introduza um vertice para saber os sitios inacessiveis: " << endl;
		while (!(cin >> v1)) { //Verifica se a opçao é valida
			cin.clear(); //Limpa o cin para não haver erros no input dos dados
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Opcao invalida!Introduza uma nova opcao" << endl;
		}
		SitiosInacessiveisAPartirDe(v1, LV);
		cout << "Sitios inacessiveis: " << endl;
		for (auto i = LV.begin(); i != LV.end(); i++) //mostra os vertices inacessiveis
			cout << (*i) << endl;
		break;
	}
	case 21: { //mostra os dados do grafo
		MostrarFronteiras();
		MostrarArestas();
		MostrarPessoas();
		break;
	}
	case 22: { //testa a memória do programa
		double custo_total;
		while (1) {

			ContarNos();   //testada a memória, a funcionar
			ContarArcos(); //testada a memória, a funcionar
			Memoria();     //testada a memória, a funcionar
						   //NoMaisArcos(); //com erros de memória
			Adjacencia(12, 5); //testada a memória, a funcionar
			list<int> *Arcos = NoMaisArcos();
			cout << "Fronteiras com mais arcos: " << endl;
			for (auto i = Arcos->begin(); i != Arcos->end(); i++) //percorre a lista de nos com mais arcos para mostrar
				cout << (*i) << endl;
			if (Arcos) //liberta a memoria usada
				Arcos->clear();
			delete Arcos;
							   //---------------------------------------------//  //testada a memória, a funcionar
			list<int> *Vertices_Iso = VerticesIsolados();
			for (auto i = Vertices_Iso->begin(); i != Vertices_Iso->end(); i++) //percorre a lista de nos isolados para mostrar      
				cout << *i << endl;
			if (Vertices_Iso) //liberta a lista
				Vertices_Iso->clear();
			delete Vertices_Iso;
			//---------------------------------------------//
			Search(15);   //testada a memória, a funcionar
			RemoverVertice(25);  //testada a memória, a funcionar
			RemoverAresta(1, 2);  //testada a memória, a funcionar
			EscreverXML("Ola.xml");  //testada a memória, a funcionar
									 //	LerXML("Ola.xml");  //aumenta a memória, porém comportamento normal visto estar a ler de um ficheiro
									 //---------------------------------------------//
			list<int> *VerticesTipo;
			VerticesTipo = DevolveVerticesTipo("2");
			cout << "Vertices do tipo indicado:" << endl;
			for (auto i = VerticesTipo->begin(); i != VerticesTipo->end(); i++) //percorre a lista de nos do mesmo tipo para mostrar
				cout << (*i) << endl;
			if (VerticesTipo) //liberta a lista de vertices
				VerticesTipo->clear();
			delete VerticesTipo;
			//----------------------------------------------//   //testada a memória, a funcionar
			list<int> *l = new list<int>;
			FronteirasMenosVisitadas(*l);
			if (l) {
				cout << "Frontariras menos visitadas:" << endl;
				for (auto i = l->begin(); i != l->end(); i++) //percorre a lista de fronteiras para mostrar
					cout << "Fronteira" << (*i) << "-" << FT->find(*i)->second->Getcontador() << "visitas" << endl;
				l->clear(); //liberta a lista
			}
			delete l;
			//-----------------------------------------------//
			MostrarFronteiras();  //testada a memória, a funcionar
			MostrarArestas();      //testada a memória, a funcionar
			MostrarPessoas();       //testada a memória, a funcionar
			list<int> LV;
			SitiosInacessiveisAPartirDe(15, LV);     //testada a memória, a funcionar
			list<int>*Return;
			Return = Caminho(12, 1, custo_total);  //testada a memória, a funcionar
			delete(Return);
			Return = CaminhoMaximo(12, 15, custo_total); //testada a memória, a funcionar
			delete(Return);
			Return = CaminhoMinimo(12, 15, custo_total); //testada a memória, a funcionar
			delete(Return);
			PossivelCaminho(12, 15, 2); //testada a memória, a funcionar
			PossivelCaminho_Independente_Tipo(12, 15); //testada a memória, a funcionar*/
		}
		break;
	}
	default: break;
	}
	cout << "Press any key to continue..." << endl;  //Alternativa ao system("pause"),
	cin.ignore();                                    // visto ser uma função dependendo do OS
	getchar();                                       // e que estava a causar memory leaks.
}

bool Grafo::Load(const string &fich_grafo, const string &fich_pessoas)		//Carrega toda a informa~ção proveniente de um ficheiro para as variáveis pertences ao programa.
{
	ifstream Fich;		//Declaração de um ficheiro
	int N_Arestas, N_Fronteiras, ID, Partida, Chegada, Cx, Cy, Tipo, Destino, Origem; double Preco;	//Variáveis utilizadas
	string Linha, id, partida, chegada, Nome, cx, cy, tipo, preco, origem, destino;
	Fich.open(fich_pessoas.c_str());	//Abertura do ficheiro relativo às pessoas
	if (!Fich)
		return false;
	while (getline(Fich, Linha)) {	//Enquanto não chegar ao fim da linha
		stringstream ss(Linha);
		getline(ss, id, ';'); //leitura de uma linha, tendo como delimitador o caracter ';', obtendo o id
		getline(ss, Nome, ';');	//o mesmo acontece para o nome
		getline(ss, partida, ';'); //para a partida
		getline(ss, chegada, ';'); //para a chegada
		ID = stoi(id);	//Converte uma string para inteiro, dando um valor à variável ID
		Partida = stoi(partida);	//Atribui o valor a Partida
		Chegada = stoi(chegada);	//Atribui o valor a Chegada
		Pessoa *P = new Pessoa(Partida, Chegada, Nome);	//Cria um objeto Pessoa
		if (!P) return false;
		Lista_Pessoas->insert(pair<int, Pessoa *>(ID, P));	//Insere essa Pessoa na Lista_Pessoas, existente na classe Grafo
	}
	Fich.close();	//Fecha o ficheiro
	Fich.open(fich_grafo.c_str());	//Abertura do ficheiro relativo a arestas e fronteiras
	if (!Fich)
		return false;
	getline(Fich, Linha);	//Lê a primeira linha
	N_Fronteiras = atoi(Linha.c_str());	//Onde se obtém o valor/número de fronteiras, atribuindo o respetivo valor
	getline(Fich, Linha);	//Lê a segunda linha
	N_Arestas = atoi(Linha.c_str());	//Onde se obtém o valor/número de arestas, atribuindo o respetivo valor
	for (int i = 0; i < N_Fronteiras; i++) {	//Para o número de fronteiras existentes no ficheiro
		Fronteira *F;
		getline(Fich, Linha);	//Lê-se uma linha
		stringstream ss(Linha);
		getline(ss, id, ';');	//Delimita-se o conteúdo de cada linha através do caracter ';', obtendo o id.
		getline(ss, cx, ';');	//Delimita-se o conteúdo de cada linha através do caracter ';', obtendo cx.
		getline(ss, cy, ';');	//Delimita-se o conteúdo de cada linha através do caracter ';', obtendo cy.
		getline(ss, tipo, ';');	//Delimita-se o conteúdo de cada linha através do caracter ';', obtendo o tipo.
		ID = stoi(id);	//Atribuem-se os respetivos valores lidos do ficheiro
		Cx = stoi(cx);
		Cy = stoi(cy);
		Tipo = stoi(tipo);
		switch (Tipo) {	//Utilizamos um switch, dado que o tipo da fronteira pode ser 1,2 ou Oficial, de modo a fazer a distinção, inserindo as fronteiras num map de fronteiras (FT)
		//Para cada case, criamos uma Fronteira, atribuindo-lhe os valores lidos
		case 1:F = new Fronteira_1(Cx, Cy);
			if (!F)
				return false;
			FT->insert(pair<int, Fronteira *>(ID, F));
			break;
		case 2:F = new Fronteira_2(Cx, Cy);
			if (!F)
				return false;
			FT->insert(pair<int, Fronteira *>(ID, F));
			break;
		case 3:F = new Fronteira_Oficial(Cx, Cy);
			if (!F)
				return false;
			FT->insert(pair<int, Fronteira *>(ID, F));
			break;
		}
	}		//O mesmo ocorre para as arestas
	getline(Fich, Linha);	//Lê-se linha a linha
	for (int i = 0; i < N_Arestas; i++) {	//E para cada aresta existente no ficheiro
		getline(Fich, Linha);	//Obtém-se uma linha nova
		stringstream ss(Linha);
		getline(ss, origem, ';');	//Delimita-se o conteúdo de cada linha através do caracter ';', obtendo a origem.
		getline(ss, destino, ';');	//Delimita-se o conteúdo de cada linha através do caracter ';', obtendo o destino.
		getline(ss, preco, ';');	//Delimita-se o conteúdo de cada linha através do caracter ';', obtendo o preco.
		Origem = stoi(origem);	//Atribuimos os respetivos valores lidos do ficheiro
		Destino = stoi(destino);
		Preco = stoi(preco);
		Aresta *A = new Aresta(Origem, Destino, Preco);	//Criamos uma nova Aresta, através dos campos obtidos
		Lista_Aresta->push_back(A);	//E adicionamos-la na Lista_Aresta da classe Grafo
		FT->find(Origem)->second->Addadj(A);	//Procuramos no map das fronteiras alguma que tenha o ID igual à Origem, chamando o método Addadj para introduzir a aresta criada (A) 
		//na lista das arestas adjacentes.
	}
	Fich.close();
	return true;
}

void Grafo::MostrarPessoas() {	//Mostra todo o conteúdo existente na Lista_Pessoas e os seus constituintes

	for (auto i = Lista_Pessoas->begin(); i != Lista_Pessoas->end(); i++) {
		cout << "ID:" << i->first << endl;
		i->second->Mostrar();
	}
}

void Grafo::MostrarFronteiras() {	//Mostra todo o conteúdo existente no map FT (relativo às fronteiras) e os seus constituintes
	for (auto i = FT->begin(); i != FT->end(); i++) {
		cout << "ID:" << i->first << endl;
		i->second->Mostrar();
	}
}

void Grafo::MostrarArestas() {		//Mostra todo o conteúdo existente na Lista_Arestas e os seus constituintes
	for (auto i = Lista_Aresta->begin(); i != Lista_Aresta->end(); i++)
		(*i)->Mostrar();
}

int Grafo::ContarNos() {	//Conta o número de vértices do grafo
	return FT->size();	//Devolve o size do map relativo às Fronteiras, correspondente aos vértices
}

int Grafo::ContarArcos() {	//Conta o número de arestas do grafo
	return Lista_Aresta->size();	//Devolve o size da lista de arestas do grafo.
}

int Grafo::Memoria() {		//Retorna toda a memória ocupada pelo programa
	int memoria = 0;		//Declara-se uma variável memoria
	for (auto i = Lista_Aresta->begin(); i != Lista_Aresta->end(); i++) {	//Percorremos a lista de arestas do grafo
		memoria += sizeof(Aresta *);	//E adicionamos à variável memoria o tamanho de um objeto da classe Aresta
		memoria += (*i)->Memoria();		//Juntamente com o conteúdo do objeto da classe Aresta
	}
	memoria += sizeof(list<Aresta *>);	//Para além disso, adicionamos o tamanho da lista de arestas
	//O mesmo ocorre para as pessoas
	for (auto i = Lista_Pessoas->begin(); i != Lista_Pessoas->end(); i++) {	//Percorremos o map de pessoas do grafo
		memoria += sizeof(int);		//Adicionamos à variavel memoria o tamanho da chave do map, que neste caso é um inteiro
		memoria += sizeof(Pessoa *);	//Adicionamos também o tamanho de um objeto da classe Pessoa
		memoria += i->second->Memoria();	//Juntamente com o espaço ocupado pelo conteúdo desse objeto
	}
	memoria += sizeof(map<int, Pessoa *>);	//Para além disso adicionamos o espaço ocupado pelo próprio map
	for (auto i = FT->begin(); i != FT->end(); i++) {	//Percorremos o map das fronteiras do grafo
		memoria += sizeof(int);	//Adicionamos o valor da chave do map, que neste caso é um inteiro relativo ao número da fronteira
		memoria += sizeof(Fronteira *);	//Adicionamos o valor de um objeto da classe Fronteira
		memoria += i->second->Memoria();	//Juntamente com o espaço ocupado pelo conteúdo desse objeto
	}
	memoria += sizeof(map<int, Fronteira*>);	//Tal como o tamanho ocupado pelo map das fronteiras
	return memoria;
}

list<int> *Grafo::NoMaisArcos()	//Função que verifica qual o vértice com mais arestas, retornando uma lista de inteiros relativos ao número da fronteira
{
	map<int, int> *contagem = new map<int, int>;	//Declaramos uma variável contagem relativa a um map
	list<int> *l = new list<int>;		//Tal como uma lista de inteiros
	int c = 0;
	for (auto i = FT->begin(); i != FT->end(); i++) {		//Percorremos o map das fronteiras
		c = 0;
		for (auto j = Lista_Aresta->begin(); j != Lista_Aresta->end(); j++)		//Percorremos a lista de arestas
			if ((*j)->GetOrigem() == i->first || (*j)->GetDestino() == i->first)	//Caso alguma aresta tenha Origem ou Destino igual ao número do objeto Fronteira em questão (i->first)
				c++;	//Incrementamos o valor de uma variável c que será inserida no map contagem
		contagem->insert(pair<int, int>(i->first, c));	//Insere-se no map o número da fronteira como chave, e a variavel c relativa ao número de arestas daquele vértice
	}
	c = contagem->begin()->first;
	for (auto i = contagem->begin(); i != contagem->end(); i++) {	//Percorremos o map contagem
		if (contagem->find(c)->second < i->second) {	//Verifica se o c->second (relativo ao número de arestas daquele vertice) é menor que o do iterador do ciclo for (i->second)
			l->clear();	//Se assim for, limpar a lista l.
			l->push_back(i->first);	//E adiciona à lista o vértice correspondente ao iterador do ciclo for
			c = i->first;	//A variável c fica com o valor de i->first, ou seja, até ao momento, a fronteira com mais arestas adjacentes
		}
		else
			if (contagem->find(c)->second == i->second) {	//Caso o iterador do ciclo for, possua o mesmo numero de arestas adjacentes que a variável c (a variável com mais arestas adjacentes)
				l->push_back(i->first);	//Insere na lista outro numero de fronteira com o mesmo numero de arestas adjacentes
				c = i->first;
			}
			else
				if (contagem->find(c)->second > i->second) {}
				else {
					l->push_back(i->first);
					c = i->first;
				}
	}
	if(!contagem->empty())
		contagem->clear();	//Limpa o map contagem
	delete contagem;	//Apaga-o
	return l;	//E retorna a lista de fronteiras com mais arestas
}

bool Grafo::Adjacencia(int v1, int v2)	//Função que verifica se há adjacência entre dois vértices
{
	for (auto i = Lista_Aresta->begin(); i != Lista_Aresta->end(); i++)	//Percorremos a lista de arestas
		if (((*i)->GetOrigem() == v1 && (*i)->GetDestino() == v2) || ((*i)->GetOrigem() == v2 && (*i)->GetDestino() == v1))	//Caso exista algum vértice que possua Origem igual a v1 ou v2 e Destino igual a v2 ou v1
			return true;	//Retorna true
	return false;	//Senão retorna false
}

list<int> *Grafo::Caminho(int v1, int v2, double &custo_total) {

	custo_total = 0.0;

	double custoprovisorio = 0.0;
	int vertice;
	bool adicionar, Continuar = true;
	list<Aresta*> ArestasAdj;


	if (v1 == v2) {
		cout << "A origem e o destino sao o mesmo!" << endl;
		return NULL;
	}



	if (Search(v1) == 0 || Search(v2) == 0) {
		if (Search(v1) == 0 && Search(v2) == 0)
			cout << "Ambos os vertices nao existem" << endl;
		else if (Search(v1) == 0)
			cout << "O vertice" << v1 << "nao existe" << endl;
		else
			cout << "O vertice" << v2 << "nao existe" << endl;
		return NULL;
	}



	//Criar map que relacione os vertices percorridos de x a y (list<int>) com o custo associado ao seu percurso
	map <list<int>, double > *PossiveisCaminhos = new map <list<int>, double>;
	list<int> element;
	list<int> Vertice;
	int novoelemento;
	int contadortipo2atual;
	Vertice.push_back(v1);
	custoprovisorio = FT->find(v1)->second->GetPeso();
	PossiveisCaminhos->insert(pair<list<int>, double>(Vertice, custoprovisorio));

	while (Continuar != false) {
		Continuar = false;
		for (auto x = PossiveisCaminhos->begin(); x != PossiveisCaminhos->end();)
		{
			Continuar = false;

			vertice = (*x).first.back();
			if (vertice != v2) {
				Continuar = true;
				ArestasAdj = FT->find(vertice)->second->GetFronteiraAdjacente();
				for (auto it = ArestasAdj.begin(); it != ArestasAdj.end(); it++) {
					adicionar = true;
					element.clear();
					element = (*x).first;
					novoelemento = (*it)->GetDestino();
					element.push_back(novoelemento);
					custoprovisorio = (*x).second + (*it)->GetPreco() + FT->find(novoelemento)->second->Getcusto();
					contadortipo2atual = 0;
					for (auto w = x->first.begin(); w != x->first.end(); w++) { //Calcular por quantas fronteiras do tipo 2 passa o caminho que se pretende colocar no map PercorrerCaminho
						if (FT->find(*w)->second->GetTipo() == 2)
							contadortipo2atual++;
					}
					if (contadortipo2atual >= 10) { //Se o caminho que pretendemos adicionar aos PossiveisCaminhos passar por mais do que 10 fronteiras do tipo 2 nao o adicionar (visto ter sido o que nos foi proposto no enunciado)
						adicionar = false;
					}

					//Verificar se não estamos num loop, em que o vertice já se encontra na lista
					if (adicionar == true) {

						int tamanho = element.size();
						int percorrido = 0;
						for (auto i = element.begin(); i != element.end(); i++) {
							if (percorrido + 1 != tamanho) { //Significa que ainda não chegámos ao ultimo elemento
								if ((*it)->GetDestino() == (*i)) { //Significa que está em loop, logo não adicionar este vértice
									adicionar = false;
								}
							}
							percorrido++;
						}
						if (adicionar == true)
							PossiveisCaminhos->insert(pair<list<int>, double>(element, custoprovisorio));
					}

				}
				PossiveisCaminhos->erase(x++);
			}
			else
				x++;
		}
	}

	list<int> *Caminho = new list<int>;
	if (PossiveisCaminhos->empty()) { //Verifica se o map dos caminhos esta vazio, se estiver quer dizer que não ha caminho
		delete Caminho;
		delete PossiveisCaminhos;
		cout << "Não ha caminho entre " << v1 << " e " << v2 << endl;
		return NULL;
	}
	//Como queremos dar return de um qualquer caminho da origem ao destino, entao optamos por dar return do primeiro caminho que encontrámos
	element = PossiveisCaminhos->begin()->first;
	for (auto i = element.begin(); i != element.end(); i++)
		Caminho->push_back((*i));
	custo_total = PossiveisCaminhos->begin()->second;
	if (PossiveisCaminhos)           //
		PossiveisCaminhos->clear();  // Limpamos a memória da variável que usamos ao longo desta função
	delete PossiveisCaminhos;        //
	return Caminho;
}

list<int> *Grafo::VerticesIsolados()	//Função que verifica quais são os vértices que não possuem nenhuma aresta adjacente, adicionando-os numa lista de inteiros
{
	list<int> *l = new list<int>;	//Declaramos uma nova lista
	int v = 1;
	if (!l)
		return NULL;
	for (auto i = FT->begin(); i != FT->end(); i++) {	//Percorremos o map relativo às fronteiras
		v = 1;	//Colocamos um inteiro igual a 1
		for (auto j = Lista_Aresta->begin(); j != Lista_Aresta->end(); j++)	//Percorremos a lista de arestas do grafo
			if ((*j)->GetDestino() == i->first)	//Caso haja alguma aresta cujo destino seja igual a um vértice do grafo
				v = 0;	//Colocamos v com o valor 0
		if (v)	//Caso v tenha valor 1
			l->push_back(i->first);	//Inserimos na lista l o valor do vértice isolado
	}
	return l;	//Devolvemos a lista
}

bool Grafo::Search(int v)	//Função que verifica se existe um vértice no map das fronteiras
{
	for (auto i = FT->begin(); i != FT->end(); i++)	//Percorremos o map relativo às fronteiras
		if (i->first == v) //Caso haja algum vértice cujo indice seja igual a v
			return true;	//Retorna true
	return false;	//Senão retorna false
}

bool Grafo::RemoverVertice(int v)	//Função que permite a remoção de um vértice
{
	if (!Search(v))	//Primeiro verificamos se aquele vértice existe no grafo
		return false;
	delete FT->find(v)->second;	//Apagamos do map, a Fronteira relativa ao vértice com indíce igual a v
	FT->erase(v);	//E eliminamos do map o conteúdo relativo ao indíce v
	list<Aresta *> *laux = new list<Aresta *>;	//Criamos uma lista auxiliar com ponteiros para Arestas
	for (auto i = Lista_Aresta->begin(); i != Lista_Aresta->end(); i++) //Irá eliminar todas as arestas que contenham v, visto que v vai ser destruido
		if ((*i)->GetDestino() == v || (*i)->GetOrigem() == v)	//Caso haja alguma aresta com destino ou origem igual a v 
			laux->push_back(*i);    //Inserimos na lista auxiliar o valor do iterador i
	for (auto i = laux->begin(); i != laux->end(); i++) {		//Percorremos a lista auxiliar
		(*i)->~Aresta();	//E para cada Aresta pertencente a essa lista, chamamos o seu destrutor
		Lista_Aresta->remove(*i);	//Removemos da lista de arestas, a aresta i
	}
	//Aqui reconstruimos todas as arestas do grafo, excluindo aquelas que estavam ligadas à fronteira eliminada 
	for (auto i = FT->begin(); i != FT->end(); i++)		//Percorremos o map das fronteiras
		i->second->LimparAdj();	//E chamamos um método que nos permite limpar as arestas adjacentes da fronteira i
	for (auto i = Lista_Aresta->begin(); i != Lista_Aresta->end(); i++)	//Percorremos a lista das arestas
		FT->find((*i)->GetOrigem())->second->Addadj(*i);	//E adicionamos numa fronteira com a Origem de i, o próprio conteúdo de i como uma aresta adjacente
	if (laux)
		laux->clear();		//Limpamos a lista auxiliar
	delete laux;	//Apagamos essa lista
	return true;
}

bool Grafo::RemoverAresta(int v1, int v2)	//Função que remove uma aresta delimitada por v1 e v2
{
	int c = 0;
	if (!Search(v1) || !Search(v2)) {
		cout << "Os vertices inseridos são invalidos" << endl;
		return false;
	}
	if (!Adjacencia(v1, v2))
		return false;
	for (auto i = Lista_Aresta->begin(); i != Lista_Aresta->end(); i++)		//Percorremos a lista das arestas
		if (((*i)->GetOrigem() == v1 && (*i)->GetDestino() == v2) || ((*i)->GetOrigem() == v2 && (*i)->GetDestino() == v1)) {	//Caso haja alguma com origem em v1 e destino em v2 ou origem em v2 e destino em v1
			(*i)->~Aresta();	//Chamamos o destrutor da aresta correspondente àquele iterador i
			Lista_Aresta->remove(*i);	//E removemos da lista de arestas a aresta correspondente ao iterador i
			c = 1;	//Colocamos um inteiro c com valor 1
			break;
		}
	if (c) {	//Caso c tenha valor 1
		//Fazemos a reconstrução das arestas do grafo, excluindo a que foi eliminada
		for (auto i = FT->begin(); i != FT->end(); i++)	//Percorremos o map relativo às fronteiras do grafo
			i->second->LimparAdj();	//E limpamos as arestas adjacentes
		for (auto i = Lista_Aresta->begin(); i != Lista_Aresta->end(); i++)	//Percorremos a lista das arestas do grafo
			FT->find((*i)->GetOrigem())->second->Addadj(*i);	//E adicionamos numa fronteira com a Origem de i, o próprio conteúdo de i como uma aresta adjacente
		return true;
	}
	return false;
}

list<int> *Grafo::DevolveVerticesTipo(const string &tipo) {	//Função que devolve, numa lista de inteiros, todos os vértices de um dado tipo
	list<int> *l = new list<int>;	//Declaramos uma nova lista de inteiros
	for (auto it = FT->begin(); it != FT->end(); it++)	//Percorremos o map relativo às fronteiras do grafo
		if (it->second->GetTipo() == stoi(tipo))	//Caso haja alguma cujo tipo seja igual ao que foi passado por argumento			//Converte constant string to integer.
			l->push_back(it->first);	//Insere-o na lista que vai ser retornada no fim da função
	return l;
}

void Grafo::FronteirasMenosVisitadas(list<int> &Lv)		//Função que vai inserir numa lista passada por argumento as fronteiras menos visitadas
{
	int m = FT->begin()->second->Getcontador();		//Declaramos um inteiro que vai ficar com o valor do contador relativo primeiro elemento do map
	for (auto i = FT->begin(); i != FT->end(); i++)	//Percorremos o map relativo às fronteiras do grafo
		if (m > i->second->Getcontador()) {		//Caso a variavel m seja maior do que o contador naquele elemento do map das fronteiras
			Lv.clear();	//A lista Lv é limpa
			Lv.push_back(i->first);	//E é inserido aquele elemento na lista
			m = i->second->Getcontador();	//A variável m ficará com o conteúdo daquele elemento, relativamente ao contador das pessoas
		}
		else
			if (m == i->second->Getcontador())	//Caso seja igual
				Lv.push_back(i->first);		//É inserido aquele elemento na lista
			else
				if (m < i->second->Getcontador()) {}
				else
					Lv.push_back(i->first);
}

bool Grafo::PossivelCaminho(int v1, int v2, int TipoFronteira) {
	int stop = 0;
	int vertice;
	int adicionar;
	list<Aresta*> ArestasAdj;
	int contador = 1;
	if (v1 == v2) {
		cout << "A origem e o destino são o mesmo!" << endl;
		return true;
	}

	if (Search(v1) == 0 || Search(v2) == 0) {
		if (Search(v1) == 0 && Search(v2) == 0)
			cout << "Ambos os vertices nso existem" << endl;
		else if (Search(v1) == 0)
			cout << "O vertice" << v1 << "nao existe" << endl;
		else
			cout << "O vertice" << v2 << "nao existe" << endl;
		return NULL;
	}
	//Criar uma lista de caminhos (list<list<int>>)
	list<list<int>>*PossiveisCaminhos = new list<list<int>>;
	list<int> element;
	element.push_back(v1);
	PossiveisCaminhos->push_back(element);
	while (contador != 0) {
		contador = 0;
		for (auto x = PossiveisCaminhos->begin(); x != PossiveisCaminhos->end();)
		{
			contador = 0;
			auto ultimo = PossiveisCaminhos->end();
			vertice = (*x).back(); //Toma o ultimo valor da lista que estamos a percorrer
			if (vertice != v2) {  //Vai verificar se a Fronteira é do tipo correto, a não ser que esta seja= v1, visto que é a fronteira de inicio, podendo ser de outro tipo(nossa interpretação).
				contador++;
				ArestasAdj = FT->find(vertice)->second->GetFronteiraAdjacente();
				for (auto it = ArestasAdj.begin(); it != ArestasAdj.end(); it++) {
					if ((FT->find((*it)->GetDestino())->second->GetTipo() == TipoFronteira || vertice == v1)) {
						adicionar = 1;
						element.clear();
						element = (*x);
						element.push_back((*it)->GetDestino());
					}
					else
						adicionar = 0;
					//Verificar se não estamos num loop, em que o vertice já se encontra na lista
					if (adicionar == 1) {
						int tamanho = element.size();
						int percorrido = 0;
						for (auto i = element.begin(); i != element.end(); i++) {
							if (percorrido + 1 != tamanho) { //Significa que ainda não chegámos ao ultimo elemento, nao estava a dar com (i !=element.end()) ou (*i!=element.back)
								if ((*it)->GetDestino() == (*i)) { //Significa que está em loop
									adicionar = 0;
								}
							}
							percorrido++;
						}
					}
					if (adicionar == 1) {
						PossiveisCaminhos->push_back(element);
					}
				}
				PossiveisCaminhos->erase(x++);
			}
			else {
				x++;
			}
		}
	}
	//Caso PossiveisCaminhos.size()>0 significa que existem caminhos da origem ao destino, contudo temos de verificar se ocorre a passagem em fronteiras do tipo 2 mais de 10 vezes.
	int contartipofronteira2;
	for (auto it = PossiveisCaminhos->begin(); it != PossiveisCaminhos->end(); it++) {
		contartipofronteira2 = 0;
		for (auto i = it->begin(); i != it->end(); i++) {
			if (FT->find(*i)->second->GetTipo() == 2) {
				contartipofronteira2++;
			}

		}
		if (contartipofronteira2 < 10) {
			delete PossiveisCaminhos;

			return true;
		}
		else {
			delete PossiveisCaminhos;

			return false;
		}

	}
	delete PossiveisCaminhos;
	return false;
}

bool Grafo::LerXML(const string &s) {	// Carrega toda a informa~ção proveniente de um ficheiro para as variáveis pertences ao programa através do tipo XML
	int N_Arestas, N_Fronteiras, ID, Partida, Chegada, Cx, Cy, Tipo, Preco, Origem, Destino;			//Variáveis utilizadas
	string Linha, id, partida, chegada, Nome, cx, cy, tipo, preco, origem, destino, nfronteiras, narestas;
	ifstream  F;	//Declara-se um ficheiro
	Fronteira *Front;
	F.open(s.c_str());	//Abrimos o ficheiro
	if (!F.is_open())	//Em caso de erro retornamos false
		return false;
	getline(F, Linha);	//Obtemos uma linha do ficheiro
	stringstream ss(Linha);
	getline(ss, nfronteiras, '>');	//Delimitamos a informação pretendida entre os caracteres '>' e '<'
	getline(ss, nfronteiras, '<');
	N_Fronteiras = stoi(nfronteiras); //E atribuimos o valor de N_Fronteiras
	//O mesmo ocorre para o número de arestas
	getline(F, Linha);	//Obtemos uma linha do ficheiro
	ss.str(Linha);
	getline(ss, narestas, '>');		//Delimitamos a informação pretendida entre os caracteres '>' e '<'
	getline(ss, narestas, '<');
	N_Arestas = stoi(narestas);	//Atribuimos o valor de N_Arestas

	getline(F, Linha);
	int c = 0;
	//Nesta porção de código procedemos à recolha dos dados das pessoas
	while (getline(F, Linha)) {		//Neste caso vamos obter sempre uma linha, até essa mesma linha corresponder ao '</Pessoas>'
		if (Linha == "</Pessoas>")
			break;
		ss.str(Linha);
		switch (c) {	//Utilizamos um switch para podermos dividir a recolha dos dados e atribuir os valores corretamente
		case 0: {		//No caso de c ser igual a 0, estamos a atribuir um valor ao ID
			getline(ss, id, '>'); //Delimitamos os dados
			getline(ss, id, '<');
			ID = stoi(id);
			c++; break;
		}
		case 1: {		//No caso de c ser igual a 1, estamos a atribuir um valor ao Nome
			getline(ss, Nome, '>');	//Delimitamos os dados
			getline(ss, Nome, '<');
			c++; break;
		}
		case 2: {		//No caso de c ser igual a 2, estamos a atribuir um valor à Partida
			getline(ss, partida, '>');	//Delimitamos os dados
			getline(ss, partida, '<');
			Partida = stoi(partida);
			c++; break;
		}
		case 3: {		//No caso de c ser igual 3, estamos a atribuir um valor a Chegada
			getline(ss, chegada, '>');	//Delimitamos os dados
			getline(ss, chegada, '<');
			Chegada = stoi(chegada);
			c = 0; break;	//Colocamos o c igual a 0 para indicar que foi feita toda a leitura dos dados para uma pessoa
		}
		}
		if (c == 0) {	//Se o c possuir o valor 0
			Pessoa *P = new Pessoa(Partida, Chegada, Nome);		//Criamos um novo objeto da classe Pessoa e atribuimos-lhe o valor obtido pela leitura
			if (!P) return false;
			Lista_Pessoas->insert(pair<int, Pessoa *>(ID, P));	//Inserimos em Lista_Pessoas o objeto Pessoa criado e o seu respetivo ID
		}
	}
	//O mesmo vai ocorrer para a leitura das fronteiras e arestas
	getline(F, Linha);
	c = 0;
	for (int i = 0; i < N_Fronteiras * 4; i++) {	//Procedemos à leitura de uma linha o N_Fronteiras * 4 visto que a classe Fronteira possui 4 atributos que vão ser lidos do ficheiro
		getline(F, Linha);
		ss.str(Linha);
		//Utilizamos o mesmo método que utilizámos para as Pessoas
		switch (c) {
		case 0: {	//No caso de c ter o valor 0 estamos a atribuir o valor do ID
			getline(ss, id, '>');	//Delimitamos os dados
			getline(ss, id, '<');
			ID = stoi(id);
			c++; break;
		}
		case 1: {	//No caso de c ter o valor 1 estamos a atribuir o valor de CX
			getline(ss, cx, '>');	//Delimitamos os dados
			getline(ss, cx, '<');
			Cx = stoi(cx);
			c++; break;
		}
		case 2: {		//No caso de c ter o valor 2 estamos a atribuir o valor de CY
			getline(ss, cy, '>');	//Delimitamos os dados
			getline(ss, cy, '<');
			Cy = stoi(cy);
			c++; break;
		}
		case 3: {		//No caso de c ter o valor 3 estamos a atribuir o tipo
			getline(ss, tipo, '>');	//Delimitamos os dados
			getline(ss, tipo, '<');
			Tipo = stoi(tipo);
			c = 0; break;	//Colocamos c a 0 para indicar que foi feita a totalidade da leitura dos dados para um objeto do tipo Fronteira
		}
		}
		if (c == 0) {	//Se c possuir o valor 0
			switch (Tipo) {
				//Aqui atribuimos o valor do tipo, conforme qual o tipo de fronteira a que pertence
			case 1:Front = new Fronteira_1(Cx, Cy);		//Criamos uma fronteira do tipo 1 com as coordenadas lidas do ficheiro
				if (!F)
					return false;
				FT->insert(pair<int, Fronteira *>(ID, Front));	//Inserimos em FT o ID lido e a Fronteira_1 criada
				break;
			case 2:Front = new Fronteira_2(Cx, Cy);		//Criamos uma fronteira do tipo 2 com as coordenadas lidas do ficheiro
				if (!F)
					return false;
				FT->insert(pair<int, Fronteira *>(ID, Front));	//Inserimos em FT o ID lido e a Fronteira_2 criada
				break;
			case 3:Front = new Fronteira_Oficial(Cx, Cy);	//Criamos uma fronteira do tipo oficial com as coordenadas lidas do ficheiro
				if (!F)
					return false;
				FT->insert(pair<int, Fronteira *>(ID, Front));	//Inserimos em FT o ID lido e a Fronteira_Oficial criada
				break;
			}
		}
	}
	getline(F, Linha);		//Saltamos as linhas correspondentes a </Fronteiras> e <Arestas>
	getline(F, Linha);
	c = 0;
	//O mesmo também ocorre para as arestas
	for (int i = 0; i < N_Arestas * 3; i++) {
		getline(F, Linha);
		ss.str(Linha);
		switch (c) {
		case 0: {
			getline(ss, origem, '>');	//Delimitamos os dados
			getline(ss, origem, '<');
			Origem = stoi(origem);
			c++; break;
		}
		case 1: {
			getline(ss, destino, '>');	//Delimitamos os dados
			getline(ss, destino, '<');
			Destino = stoi(destino);
			c++; break;
		}
		case 2: {
			getline(ss, preco, '>');	//Delimitamos os dados
			getline(ss, preco, '<');
			Preco = stoi(preco);
			c = 0; break;
		}
		}
		if (c == 0) {	//Se o c possuir o valor 0
			Aresta *A = new Aresta(Origem, Destino, Preco);	//Criamos um novo objeto do tipo Aresta com os dados que foram adquiridos do ficheiro
			Lista_Aresta->push_back(A);	//Inserimos-lo na Lista_Aresta
		}
	}
	F.close();
	return true;
}

void Grafo::EscreverXML(const string &s)
{					//Função que permite guardar a informação existente no formato XML
	ofstream F;		//Declara-se um ficheiro para output
	F.open(s);		//Abrimos o ficheiro
	if (!F.is_open())
		return;
	F << "<Numero Fronteiras>" << FT->size() << "</Numero Fronteiras>" << endl;		//Introduzimos o número de fronteiras
	F << "<Numero Arestas>" << Lista_Aresta->size() << "</Numero Arestas>" << endl;	//Introduzimos o número de arestas
	F << "<Pessoas>" << endl;
	for (auto i = Lista_Pessoas->begin(); i != Lista_Pessoas->end(); i++) {		//Relativamente às pessoas, percorremos o map
		F << "\t<ID>" << i->first << "</ID>" << endl;	//E introduzimos o ID
		F << "\t<Nome>" << i->second->GetNome() << "</Nome>" << endl;		//O nome
		F << "\t<Partida>" << i->second->GetPartida() << "</Partida>" << endl;	//A partida
		F << "\t<Chegada>" << i->second->GetChegada() << "</Chegada>" << endl;		//E chegada
	}
	F << "</Pessoas>" << endl;
	F << "<Fronteiras>" << endl;
	for (auto i = FT->begin(); i != FT->end(); i++) {		//Nas fronteiras, semelhante às pessoas, percorremos o map
		F << "\t<ID>" << i->first << "</ID>" << endl;	//Introduzimos o ID
		F << "\t<Coordenada_X>" << i->second->GetCoordX() << "</Coordenada_X>" << endl;		//As coordenadas X
		F << "\t<Coordenada_Y>" << i->second->GetCoordY() << "</Coordenada_Y>" << endl;		//As coordenadas Y
		F << "\t<Tipo>" << i->second->GetTipo() << "</Tipo>" << endl;			//E o tipo de fronteira
	}
	F << "</Fronteiras>" << endl;
	F << "<Arestas>" << endl;
	for (auto i = Lista_Aresta->begin(); i != Lista_Aresta->end(); i++) {			//Nas arestas, percorremos a lista de arestas
		F << "\t<Origem>" << (*i)->GetOrigem() << "</Origem>" << endl;		//E introduzimos a origem
		F << "\t<Destino>" << (*i)->GetDestino() << "</Destino>" << endl;	//O destino
		F << "\t<Preço>" << (*i)->GetPreco() << "</Preço>" << endl;		//E o preço
	}
	F << "</Arestas>" << endl;
	F.close();	//Fechamos o ficheiro
	return;
}

bool Grafo::PossivelCaminho_Independente_Tipo(int v1, int v2) {
	int vertice;
	bool adicionar;
	list<Aresta*> ArestasAdj;
	bool contador = true;
	if (v1 == v2) {
		cout << "A origem e o destino são o mesmo!" << endl;
		return true;
	}
	if (Search(v1) == 0 || Search(v2) == 0) {
		if (Search(v1) == 0 && Search(v2) == 0)
			cout << "Ambos os vertices nao existem" << endl;
		else if (Search(v1) == 0)
			cout << "O vertice" << v1 << "nao existe" << endl;
		else
			cout << "O vertice" << v2 << "nao existe" << endl;
		return NULL;
	}
	//Criar uma lista de caminhos (list<list<int>>)
	list<list<int>>*PossiveisCaminhos = new list<list<int>>;
	list<int> element;
	element.push_back(v1);
	PossiveisCaminhos->push_back(element);
	while (contador != false) {
		contador = false;
		for (auto x = PossiveisCaminhos->begin(); x != PossiveisCaminhos->end();)
		{
			contador = false;
			auto ultimo = PossiveisCaminhos->end();
			vertice = (*x).back(); //Toma o ultimo valor da lista que estamos a percorrer
			if (vertice != v2) {
				contador = true;
				ArestasAdj = FT->find(vertice)->second->GetFronteiraAdjacente();
				for (auto it = ArestasAdj.begin(); it != ArestasAdj.end(); it++) {
					adicionar = true;
					element.clear();
					element = (*x);
					element.push_back((*it)->GetDestino());
					//Verificar se não estamos num loop, em que o vertice já se encontra na lista
					if (adicionar == true) {
						int tamanho = element.size();
						int percorrido = 0;
						for (auto i = element.begin(); i != element.end(); i++) {
							if (percorrido + 1 != tamanho) { //Significa que ainda não chegámos ao ultimo elemento, nao estava a dar com (i !=element.end()) ou (*i!=element.back)
								if ((*it)->GetDestino() == (*i)) { //Significa que está em loop
									adicionar = false;
								}
							}
							percorrido++;
						}
					}

					if (adicionar == true) {
						PossiveisCaminhos->push_back(element);
					}

				}
				PossiveisCaminhos->erase(x++);
			}
			else {
				x++;
			}
		}
	}
	//Caso PossiveisCaminhos.size()>0 significa que existem caminhos da origem ao destino, contudo temos de verificar se ocorre a passagem em fronteiras do tipo 2 mais de 10 vezes.
	int contartipofronteira2;
	for (auto it = PossiveisCaminhos->begin(); it != PossiveisCaminhos->end(); it++) {
		contartipofronteira2 = 0;
		for (auto i = it->begin(); i != it->end(); i++) {
			if (FT->find(*i)->second->GetTipo() == 2) {
				contartipofronteira2++;
			}
		}
		if (contartipofronteira2 < 10) {
			delete PossiveisCaminhos;

			return true;
		}
		else {
			delete PossiveisCaminhos;

			return false;
		}
	}
	delete PossiveisCaminhos;
	return false;
}

void Grafo::SitiosInacessiveisAPartirDe(int V1, list<int> &Lv) {		//Função que verifica quais os caminhos inacessíveis de um vértice, adicionando-os a uma lista de inteiros
	for (auto i = FT->begin(); i != FT->end(); i++)		//Percorre o map relativo às fronteiras
		if (i->first != V1) {		//Se existir algum elemento do map, cujo indice de fronteira seja diferente de V1
			if (!PossivelCaminho_Independente_Tipo(V1, i->first))	//Chamamos o método que verifica se o caminho é possível de V1 até ao i->first, e caso não o seja
				Lv.push_back(i->first);		//Introduzimos o indice da fronteira em Lv
		}
}

list<int> *Grafo::CaminhoMinimo(int v1, int v2, double &custo_total) {


	custo_total = 0.0;

	double custoprovisorio = 0.0;
	int vertice;
	bool adicionar, Continuar = true;
	list<Aresta*> ArestasAdj;


	if (v1 == v2) {
		cout << "A origem e o destino sao o mesmo!" << endl;
		return NULL;
	}



	if (Search(v1) == 0 || Search(v2) == 0) {
		if (Search(v1) == 0 && Search(v2) == 0)
			cout << "Ambos os vertices nso existem" << endl;
		else if (Search(v1) == 0)
			cout << "O vertice" << v1 << "nao existe" << endl;
		else
			cout << "O vertice" << v2 << "nao existe" << endl;
		return NULL;
	}



	//Criar map que relacione os vertices percorridos de x a y (list<int>) com o custo associado ao seu percurso
	map <list<int>, double > *PossiveisCaminhos = new map <list<int>, double>;
	list<int> element;
	list<int> Vertice;
	int novoelemento;
	Vertice.push_back(v1);
	custoprovisorio = FT->find(v1)->second->GetPeso();
	PossiveisCaminhos->insert(pair<list<int>, double>(Vertice, custoprovisorio));

	while (Continuar != false) {
		Continuar = false;
		for (auto x = PossiveisCaminhos->begin(); x != PossiveisCaminhos->end();)
		{
			Continuar = false;

			vertice = (*x).first.back();
			if (vertice != v2) {
				Continuar = true;
				ArestasAdj = FT->find(vertice)->second->GetFronteiraAdjacente();
				for (auto it = ArestasAdj.begin(); it != ArestasAdj.end(); it++) {
					adicionar = true;
					element.clear();
					element = (*x).first;
					novoelemento = (*it)->GetDestino();
					element.push_back(novoelemento);
					custoprovisorio = (*x).second + (*it)->GetPreco() + FT->find(novoelemento)->second->Getcusto();
					//Verificar se o ultimo vertice do element já se encontra no map, caso se encontre comparar custoprovisorio se for maior nao inserir este element no map pois há uma forma mais lenta de chegar ao mesmo.
					for (auto y = PossiveisCaminhos->begin(); y != PossiveisCaminhos->end() && adicionar == true;) {
						auto comparar = (*y).first.back();
						if ((*it)->GetDestino() == comparar && y != x) {  //(y!=x) tem a logica de, nao comparar o mesmo caminho que estamos a usar na funçao em cima

							int contadortipo2atual = 0, contadortipo2antigo = 0;

							for (auto z = y->first.begin(); z != y->first.end(); z++) { //Calcular por quantas fronteiras do tipo 2 passou o caminho que já se encontrava no map PercorrerCaminho
								if (FT->find(*z)->second->GetTipo() == 2)
									contadortipo2antigo++;
							}
							for (auto w = x->first.begin(); w != x->first.end(); w++) { //Calcular por quantas fronteiras do tipo 2 passa o caminho que se pretende colocar no map PercorrerCaminho
								if (FT->find(*w)->second->GetTipo() == 2)
									contadortipo2atual++;
							}
							if (contadortipo2atual >= 10) //Caso o caminho que pretendemos adicionar aos PossiveisCaminhos passe por mais de 10 fronteiras do tipo 2 não o adicionar
								adicionar = false;
							if (contadortipo2antigo >= contadortipo2atual && adicionar == true) { //Se o numero de fronteiras do tipo 2 do caminho antigo for menor que do caminho atual guarda-se este caminho antigo (mesmo que tenha maior custo), uma vez que poderá passar em menos de 10 fronteiras do tipo 3 e o novo não.

								if ((*y).second > custoprovisorio) {//Se o vertice que já se encontra no map tiver custototal maior que o que pretendo adicionar, remover o antigo. caso contrario nao adicionar novo.
									PossiveisCaminhos->erase(y++);
								}
								else if ((*y).second < custoprovisorio) {
									adicionar = false;
									y++;
								}
								//Caso sejam iguais deixar estar os dois.
								else
									y++;
							}
							else
								y++;

						}
						else {
							y++;
						}
					}
					//Verificar se não estamos num loop, em que o vertice já se encontra na lista
					if (adicionar == true) {

						int tamanho = element.size();
						int percorrido = 0;
						for (auto i = element.begin(); i != element.end(); i++) {
							if (percorrido + 1 != tamanho) { //Significa que ainda não chegámos ao ultimo elemento
								if ((*it)->GetDestino() == (*i)) { //Significa que está em loop
									adicionar = false;
								}
							}
							percorrido++;
						}
						if (adicionar == true)
							PossiveisCaminhos->insert(pair<list<int>, double>(element, custoprovisorio));
					}



				}

				PossiveisCaminhos->erase(x++);

			}
			else
				x++;
		}



	}
	//Caso exista somente um caminho minimo este será return, se houver mais que um caminho com o mesmo custo será return o primeiro.
	list<int> *CaminhoMin = new list<int>;
	if (PossiveisCaminhos->empty()) { //Verifica se o map dos caminhos esta vazio
		delete CaminhoMin;			  //Se estiver quer dizer que não ha caminho
		delete PossiveisCaminhos;
		cout << "Não ha caminho entre " << v1 << " e " << v2 << endl;
		return NULL;
	}

	//Deixar o caminho com menor custo total e eliminar os outros.
	for (auto it = PossiveisCaminhos->begin(); it != PossiveisCaminhos->end();) {
		bool removido = false;
		for (auto i = PossiveisCaminhos->begin(); i != PossiveisCaminhos->end() && removido == false; i++) {
			if ((*it).second > (*i).second && i != it) {

				PossiveisCaminhos->erase(it++);
				removido = true;


			}
		}
		if (removido == false)
			it++;

	}
	//Ao fim desta verificaçao permanecem no PossiveisCaminhos, ou o caminho minimo ou todos os caminhos minimos em que o custo total seja o mesmo, pelo que se poderá devolver qualquer um visto terem o mesmo custo.
	if (PossiveisCaminhos->size() >= 2)
		cout << "Existem " << PossiveisCaminhos->size() << "formas de chegar de" << v1 << "a" << v2 << "com o mesmo custo total, sendo uma delas:" << endl;


	element = PossiveisCaminhos->begin()->first;
	for (auto i = element.begin(); i != element.end(); i++)
		CaminhoMin->push_back((*i));
	custo_total = PossiveisCaminhos->begin()->second;
	if (PossiveisCaminhos)
		PossiveisCaminhos->clear();
	delete PossiveisCaminhos;
	return CaminhoMin;
}

list<int> *Grafo::CaminhoMaximo(int v1, int v2, double &custo_total) {


	custo_total = 0.0;
	double custoprovisorio = 0.0;
	int vertice;
	bool adicionar;
	list<Aresta*> ArestasAdj;
	bool Continuar = true;


	if (v1 == v2) {
		cout << "A origem e o destino sao o mesmo!" << endl;
		return NULL;
	}


	if (Search(v1) == 0 || Search(v2) == 0) {
		if (Search(v1) == 0 && Search(v2) == 0)
			cout << "Ambos os vertices nso existem" << endl;
		else if (Search(v1) == 0)
			cout << "O vertice" << v1 << "nao existe" << endl;
		else
			cout << "O vertice" << v2 << "nao existe" << endl;
		return NULL;
	}



	//Criar map que relacione os vertices percorridos de x a y (list<int>) com o custo associado ao seu percurso
	map <list<int>, double > *PossiveisCaminhos = new map <list<int>, double>;
	list<int> element;
	list<int> Vertice;
	int novoelemento;
	Vertice.push_back(v1);
	custoprovisorio = FT->find(v1)->second->GetPeso();
	PossiveisCaminhos->insert(pair<list<int>, double>(Vertice, custoprovisorio));

	while (Continuar != false) {
		Continuar = false;
		for (auto x = PossiveisCaminhos->begin(); x != PossiveisCaminhos->end();)
		{
			Continuar = false;

			vertice = (*x).first.back();
			if (vertice != v2) {
				Continuar = true;
				ArestasAdj = FT->find(vertice)->second->GetFronteiraAdjacente();
				for (auto it = ArestasAdj.begin(); it != ArestasAdj.end(); it++) {
					adicionar = true;
					element.clear();
					element = (*x).first;
					novoelemento = (*it)->GetDestino();
					element.push_back(novoelemento);
					custoprovisorio = (*x).second + (*it)->GetPreco() + FT->find(novoelemento)->second->Getcusto();
					//Verificar se o ultimo vertice do element já se encontra no map, caso se encontre comparar custoprovisorio se for maior nao inserir este element no map pois há uma forma mais lenta de chegar ao mesmo.
					for (auto y = PossiveisCaminhos->begin(); y != PossiveisCaminhos->end() && adicionar == true;) {
						auto comparar = (*y).first.back();
						if ((*it)->GetDestino() == comparar && y != x) {  //(y!=x) tem a logica de, nao comparar o mesmo caminho que estamos a usar na funçao em cima

							int contadortipo2atual = 0, contadortipo2antigo = 0;

							for (auto z = y->first.begin(); z != y->first.end(); z++) { //Calcular por quantas fronteiras do tipo 3 passou o caminho que já se encontrava no map PercorrerCaminho
								if (FT->find(*z)->second->GetTipo() == 2)
									contadortipo2antigo++;
							}
							for (auto w = x->first.begin(); w != x->first.end(); w++) { //Calcular por quantas fronteiras do tipo 3 passa o caminho que se pretende colocar no map PercorrerCaminho
								if (FT->find(*w)->second->GetTipo() == 2)
									contadortipo2atual++;
							}
							if (contadortipo2atual >= 10) //Caso o caminho que pretendemos adicionar aos PossiveisCaminhos passe por mais de 10 fronteiras do tipo 2 não o adicionar
								adicionar = false;
							if (contadortipo2antigo >= contadortipo2atual && adicionar == true) { //Se o numero de fronteiras do tipo 3 do caminho antigo for menor que do caminho atual guarda-se este caminho antigo (mesmo que tenha menor custo), uma vez que poderá passar em menos de 10 fronteiras do tipo 3 e o novo não.

								if ((*y).second < custoprovisorio) {//Se o vertice que já se encontra no map tiver custototal menor que o que pretendo adicionar, remover o antigo. caso contrario nao adicionar novo.
									PossiveisCaminhos->erase(y++);
								}
								else if ((*y).second > custoprovisorio) {
									adicionar = false;
									y++;
								}
								//Caso sejam iguais deixar estar os dois.
								else
									y++;
							}
							else
								y++;
						}
						else {
							y++;
						}
					}
					//Verificar se não estamos num loop, em que o vertice já se encontra na lista
					if (adicionar == true) {

						int tamanho = element.size();
						int percorrido = 0;
						for (auto i = element.begin(); i != element.end(); i++) {
							if (percorrido + 1 != tamanho) { //Significa que ainda não chegámos ao ultimo elemento, nao estava a dar com (i !=element.end()) ou (*i!=element.back)
								if ((*it)->GetDestino() == (*i)) { //Significa que está em loop
									adicionar = 0;
								}
							}
							percorrido++;
						}
						if (adicionar == true)
							PossiveisCaminhos->insert(pair<list<int>, double>(element, custoprovisorio));
					}



				}

				PossiveisCaminhos->erase(x++);

			}
			else
				x++;
		}



	}

	//Deixar o caminho com menor custo total e eliminar os outros.
	for (auto it = PossiveisCaminhos->begin(); it != PossiveisCaminhos->end();) {
		bool removido = false;
		for (auto i = PossiveisCaminhos->begin(); i != PossiveisCaminhos->end() && removido == false; i++) {
			if ((*it).second > (*i).second && i != it) {

				PossiveisCaminhos->erase(it++);
				removido = true;


			}
		}
		if (removido == false)
			it++;

	}
	//Ao fim desta verificaçao permanecem no PossiveisCaminhos, ou o caminho minimo ou todos os caminhos minimos em que o custo total seja o mesmo, pelo que se poderá devolver qualquer um visto terem o mesmo custo.
	if (PossiveisCaminhos->size() >= 2)
		cout << "Existem " << PossiveisCaminhos->size() << "formas de chegar de" << v1 << "a" << v2 << "com o mesmo custo total, sendo uma delas:" << endl;


	list<int> *CaminhoMax = new list<int>;
	if (PossiveisCaminhos->empty()) { //Verifica se o map dos caminhos esta vazio
		delete CaminhoMax;			  //Se estiver quer dizer que não ha caminho
		delete PossiveisCaminhos;
		cout << "Não ha caminho entre " << v1 << " e " << v2 << endl;
		return NULL;
	}
	element = PossiveisCaminhos->begin()->first;
	for (auto i = element.begin(); i != element.end(); i++)
		CaminhoMax->push_back((*i));
	custo_total = PossiveisCaminhos->begin()->second;
	if (PossiveisCaminhos)
		PossiveisCaminhos->clear();
	delete PossiveisCaminhos;
	return CaminhoMax;

}