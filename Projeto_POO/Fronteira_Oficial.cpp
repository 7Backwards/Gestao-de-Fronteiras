#include "Fronteira_Oficial.h"


Fronteira_Oficial::Fronteira_Oficial(int cx, int cy)
	:Fronteira(cx, cy)
{
}


Fronteira_Oficial::~Fronteira_Oficial(void)
{
}

int Fronteira_Oficial::GetTipo()
{
	return 3;
}

void Fronteira_Oficial::Mostrar() {
	Fronteira::Mostrar();
	cout << "Tipo: Oficial" << endl << endl;
}