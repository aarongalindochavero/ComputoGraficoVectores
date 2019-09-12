#pragma once
#include "Matriz.h"

class Rotacion : public Matriz
{
public:
	Rotacion(float);
	~Rotacion();

	float setAngulo(float);

private:
	float angulo;
};

