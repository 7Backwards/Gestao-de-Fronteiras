#include "Fronteira_2.h"


Fronteira_2::Fronteira_2(int cx, int cy)
	:Fronteira(cx, cy)
{
}


Fronteira_2::~Fronteira_2(void)
{
}

int Fronteira_2::GetTipo()
{
	return 2;
}

int Fronteira_2::GetPeso()
{
	return 1;
}

void Fronteira_2::Mostrar() {
	Fronteira::Mostrar();
	cout << "Tipo: 2" << endl << endl;
}

int Fronteira_2::Getcusto() {
	return 10;
}