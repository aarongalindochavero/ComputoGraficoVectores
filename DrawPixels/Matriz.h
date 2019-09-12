#pragma once
#include<vector>
#include "Vector.h"
#include <math.h>
#include <cmath>
#include <iostream>
#ifndef Matriz_H
#define Matriz_H

class Matriz
{
protected:
	std::vector<std::vector<float>> mat;

private:
	unsigned rows;
	unsigned cols;

public:
	Matriz();
	Matriz(unsigned rows, unsigned cols);

	Matriz(const Matriz& rhs);
	virtual ~Matriz();

	unsigned getRows() const;
	unsigned getCols() const;

	Matriz& operator=(Matriz);
	Matriz operator+(Matriz&);
	Matriz operator-(Matriz&);
	Matriz operator*(Matriz&);

	Matriz transpuesta();
	Matriz identidad();

	Matriz operator+(float&);
	Matriz operator-(float&);
	Matriz operator*(float&);
	Matriz operator/(float&);
	Vector operator*(const Vector&);

	float& operator()(const unsigned&, const unsigned&);
	void print();
	void modificarMatriz();
	void vectorEnMatriz(Vector&, Vector&);
};

#endif // !Matriz_H
