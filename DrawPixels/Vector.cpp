#include "pch.h"
#include "Vector.h"


Vector::Vector()
{
	x = y = 0;
}


Vector::Vector(int a, int b)
{
	x = a;
	y = b;
}

Vector Vector::operator+(Vector param)
{
	Vector temp;
	temp.x = x + param.x;
	temp.y = y + param.y;
	return temp;
}

Vector Vector::operator-(Vector param)
{
	Vector temp;
	temp.x = x - param.x;
	temp.y = y - param.y;
	return temp;
}

float Vector::operator*(Vector param)
{
	Vector temp2;
	float temp;
	temp = temp2.x*param.x + temp2.y + param.y;
	return temp;
}

Vector Vector::operator*(float param)
{
	Vector temp;
	temp.x = this->x*param;
	temp.y = this->y*param;
	return temp;
}

Vector Vector::operator=(Vector param)
{
	Vector temp;
	temp.x = param.x;
	temp.y = param.y;
	return temp;
}

Vector::~Vector()
{
}
