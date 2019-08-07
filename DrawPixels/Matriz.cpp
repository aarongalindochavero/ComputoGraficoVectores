#include "pch.h"
#include "Matriz.h"

Matriz::Matriz()
{
}

Matriz::Matriz(unsigned rows, unsigned cols)
{
	mat.resize(rows);
	for (unsigned i = 0; i < mat.size(); i++)
	{
		mat[i].resize(cols, 0);
	}

	rows = rows;
	cols = cols;
}

//Matriz::Matriz(Matriz & rhs)
//{
//}

Matriz::~Matriz()
{
}

Matriz & Matriz::operator=(Matriz & mtz)
{
	if (&mtz == this)
		return *this;
	unsigned new_rows = mtz.getRows();
	unsigned new_cols = mtz.getCols();
	mat.resize(new_rows);
	for (unsigned i = 0; i < mat.size(); i++)
	{
		mat[i].resize(new_cols);
	}
	for (unsigned i = 0; i < new_rows; i++)
	{
		for (unsigned j = 0; j < new_cols; j++)
		{
			mat[i][j] = mtz(i, j);
		}
	}
	rows = new_rows;
	cols = new_cols;
	return *this;
}

Matriz & Matriz::operator+(Matriz & mtz)
{
	Matriz temp(rows, cols);
	for (unsigned i = 0; i < temp.rows; i++)
	{
		for (unsigned j = 0; j < temp.cols; j++)
		{
			temp(i, j) = mat[i][j] + mtz(i, j);
		}
	}
	return temp;
}

Matriz Matriz::transpose()
{
	Matriz mtz(rows, cols);

	for (unsigned i = 0; i < rows; i++)
	{
		for (unsigned j = 0; j < cols; j++)
		{
			mtz(i, j) = this->mat[j][i];
		}
	}
	return mtz;
}

float & Matriz::operator()(const unsigned & row, const unsigned & col)
{
	return this->mat[row][col];
}

void Matriz::print()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			std::cout << mat[i][j] << " ";
		}
		std::cout << std::endl;
	}
}


unsigned Matriz::getRows()
{
	return rows;
}

unsigned Matriz::getCols()
{
	return cols;
}