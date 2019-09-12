#include "pch.h"
#include "Rotacion.h"

Rotacion::Rotacion(float _angulo)
{
	mat.resize(3);
	for (int i = 0; i < mat.size(); i++) {
		mat[i].resize(3, 0);
	}

	mat[0][0] = std::cos(angulo *3.1416 / 180);
	mat[0][1] = std::sin(angulo *3.1416 / 180);
	mat[1][0] = std::sin(angulo *3.1416 / 180);
	mat[1][1] = std::cos(angulo *3.1416 / 180);
}

Rotacion::~Rotacion()
{
}

float Rotacion::setAngulo(float _angulo)
{
	angulo = _angulo;
	return angulo;
}
