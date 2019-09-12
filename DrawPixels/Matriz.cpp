#include "pch.h"
#include "Matriz.h"


Matriz::Matriz()
{
}

Matriz::Matriz(unsigned _rows, unsigned _cols)
{
	mat.resize(_rows);
	for (int i = 0; i < mat.size(); i++) {
		mat[i].resize(_cols, 0);
	}

	rows = _rows;
	cols = _cols;
}


Matriz::Matriz(const Matriz & other)
{
	mat = other.mat;
	cols = other.getCols();
	rows = other.getRows();
}

Matriz::~Matriz()
{
}

unsigned Matriz::getRows() const
{
	return this->rows;
}

unsigned Matriz::getCols() const
{
	return this->cols;
}

Matriz & Matriz::operator=(Matriz other)
{
	if (&other == this)
		return *this;

	unsigned newRows = other.getRows();
	unsigned newCols = other.getCols();

	mat.resize(newRows);

	for (unsigned i = 0; i < mat.size(); i++) {
		mat[i].resize(newCols);
	}
	for (unsigned i = 0; i < newRows; i++) {
		for (unsigned j = 0; j < newCols; j++) {
			mat[i][j] = other(i, j);
		}
	}

	rows = newRows;
	cols = newCols;

	return *this;
}

Matriz Matriz::operator+(Matriz & mtrx)
{
	Matriz matriz(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matriz(i, j) = mat[i][j] + mtrx(i, j);
		}
	}

	return matriz;
}

Matriz Matriz::operator-(Matriz & mtrx)
{
	Matriz matriz(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matriz(i, j) = mat[i][j] - mtrx(i, j);
		}
	}

	return matriz;
}

Matriz Matriz::operator*(Matriz &mtrx)
{
	Matriz matriz(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matriz(i, j) = 0;
		}
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < mtrx.getCols(); j++) {
			for (int k = 0; k < cols; k++) {
				matriz(i, j) += mat[i][j] * mtrx(k, j);
			}
		}
	}

	return matriz;
}

Matriz Matriz::transpuesta()
{
	Matriz matriz(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matriz(i, j) = mat[j][i];
		}
	}

	return matriz;
}

Matriz Matriz::identidad()
{
	Matriz matriz(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (i == j)
				matriz(i, j) = 1;
			else
				matriz(i, j) = 0;
		}
	}
	
	return matriz;
}

Matriz Matriz::operator+(float &number)
{
	Matriz matriz(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matriz(i, j) = mat[i][j] + number;
		}
	}

	return matriz;
}

Matriz Matriz::operator-(float &number)
{
	Matriz matriz(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matriz(i, j) = mat[i][j] - number;
		}
	}

	return matriz;
}

Matriz Matriz::operator*(float &number)
{
	Matriz matriz(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matriz(i, j) = mat[i][j] * number;
		}
	}

	return matriz;
}

Matriz Matriz::operator/(float &number)
{
	Matriz matriz(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matriz(i, j) = mat[i][j] / number;
		}
	}

	return matriz;
}

Vector Matriz::operator*(const Vector &vec1)
{
	Vector vectorResultante(0, 0, 0);

	mat.resize(3);

	for (int i = 0; i < mat.size(); i++) {
		mat[i].resize(3, 0);
	}

	vectorResultante.x = vec1.x*mat[0][0] + vec1.y*mat[0][1] + vec1.z*mat[0][2];
	vectorResultante.y = vec1.x*mat[1][0] + vec1.y*mat[1][1] + vec1.z*mat[1][2];
	vectorResultante.z = vec1.x*mat[2][0] + vec1.y*mat[2][1] + vec1.z*mat[2][2];

	return vectorResultante;
}

float & Matriz::operator()(const unsigned &row, const unsigned &col)
{
	return this->mat[row][col];
}

void Matriz::print()
{
	printf("La matriz es:\n");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cout << mat[i][j] << " ";
		}
		printf("\n");
	}
	printf("\n");
}

void Matriz::modificarMatriz()
{
	int a = 0;
	printf("Ingresa la matriz\n");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cin >> a;
			mat[i][j] = a;
		}
	}
}

void Matriz::vectorEnMatriz(Vector &vec1, Vector &vec2)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			mat[0][0] = vec1.x;
			mat[0][1] = vec1.y;
			mat[1][0] = vec2.x;
			mat[1][1] = vec2.y;
		}
	}
}
