#pragma once
#include <iostream>

#ifndef  MATRIZ_H
#define MATRIZ_H

#include <vector>
#include "Vector.h"
class Matriz
{
private:
	std::vector<std::vector<float> >mat;
	unsigned rows;
	unsigned cols;

public:
	Matriz();
	Matriz(unsigned rows, unsigned cols);
	/*Matriz(Matriz& rhs);*/
	virtual ~Matriz();

	Matriz& operator= (Matriz&);
	Matriz& operator+ (Matriz&);
	//Matriz& operator- (Matriz&);
	//Matriz& operator* (Matriz&);
	Matriz transpose();

	////multiplicacion por escalar
	//Matriz operator+(float&);
	//Matriz operator-(float&);
	//Matriz operator*(float&);
	//Matriz operator/(float&);

	////multiplicacion por vector
	//Vector operator*(const Vector&);
	float& operator()(const unsigned&, const unsigned&);

	void print();

	

	unsigned getRows();
	unsigned getCols();
};

#endif // ! MATRIZ_H
