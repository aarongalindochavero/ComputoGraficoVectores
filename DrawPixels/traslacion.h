#pragma once
#include "Matriz.h"
class traslacion : public Matriz
{
public:

	void setVX(int);
	void setVY(int);

	traslacion(int vx, int vy);
	~traslacion();

private:
	int vx, vy;
};

