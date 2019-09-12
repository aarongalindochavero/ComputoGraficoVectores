#include "pch.h"
#include "Escalamiento.h"

Escalamiento::Escalamiento(int sx, int sy)
{
	mat.resize(3);
	for (int i = 0; i < mat.size(); i++) {
		mat[i].resize(3, 0);
	}

	mat[0][0] = sx;
	mat[1][1] = sy;
	mat[2][2] = 1;
}

Escalamiento::~Escalamiento()
{
}

int Escalamiento::setSX(int _sx)
{
	sx = _sx;
	return sx;
}

int Escalamiento::setXY(int _sy)
{
	sy = _sy;
	return sy;
}
