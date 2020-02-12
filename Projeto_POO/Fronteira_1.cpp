#include "Fronteira_1.h"


Fronteira_1::Fronteira_1(int cx, int cy)
	:Fronteira(cx, cy)
{
}


Fronteira_1::~Fronteira_1(void)
{
}

int Fronteira_1::GetTipo()
{
	return 1;
}

void Fronteira_1::Mostrar() {
	Fronteira::Mostrar();
	cout << "Tipo: 1" << endl << endl;
}

int Fronteira_1::Getcusto() {
	return 10;
}