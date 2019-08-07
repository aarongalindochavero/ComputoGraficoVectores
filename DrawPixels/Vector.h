#pragma once
class Vector
{
public:
	int x, y;
	Vector();
	Vector(int, int);
	Vector operator + (Vector);
	Vector operator - (Vector);
	float operator * (Vector);
	Vector operator * (float);
	Vector operator = (Vector);
	~Vector();
};

