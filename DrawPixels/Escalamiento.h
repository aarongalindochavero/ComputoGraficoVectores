#pragma once
#include "Matriz.h"

class Escalamiento : public Matriz
{
public:

	Escalamiento(int sx, int sy);
	~Escalamiento();

	int setSX(int);
	int setXY(int);

private:
	int sx, sy;
};

