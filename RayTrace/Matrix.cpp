#include "stdafx.h"
#include "Matrix.h"

Matrix::Matrix()
{
	column = 1;
	row = 1;
	mat[0][0] = 0;
}

Matrix::Matrix(int r, int c)
:row(r), column(c)
{
	if (row < 10 && column < 10)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				mat[i][j] = 0;
			}
		}
	}
}


Matrix::~Matrix()
{
	column = 0;
	row = 0;
}
float Matrix::GetSum()
{
	float sum = 0.0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			sum += mat[i][j];
		}
	}
	return sum;
}
Matrix operator +(Matrix &m1, Matrix&m2)
{
	Matrix m3;
	int c = m1.column;
	int r = m1.row;
	if (c == m2.column&&r == m2.row)
	{
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				m3.mat[i][j] = m1.mat[i][j] + m2.mat[i][j];
			}
		}
		m3.column = c;
		m3.row = r;
	}
	return  m3;
}
Matrix operator -(Matrix &m1, Matrix&m2)
{
	Matrix m3;
	int c = m1.column;
	int r = m1.row;
	if (c == m2.column&&r == m2.row)
	{
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				m3.mat[i][j] = m1.mat[i][j] - m2.mat[i][j];
			}
		}
		m3.column = c;
		m3.row = r;
	}
	return  m3;
}
Matrix operator *(float a, Matrix&m2)
{
	Matrix m3;
	for (int i = 0; i < m2.column; i++)
	{
		for (int j = 0; j < m2.row; j++)
		{
			m3.mat[i][j] = a*m2.mat[i][j];
		}
	}
	m3.column = m2.column;
	m3.row = m2.row;
	return m3;
}
Matrix operator *(Matrix &m1, Matrix&m2)
{
	Matrix m3;
	int y1 = m1.column;
	int x1 = m1.row;
	int y2 = m2.column;
	int x2 = m2.row;
	if (y1 == x2)
	{
		m3.row = x1, m3.column = y2;
		Matrix m3(x1, y2);
		for (int i = 0; i < x1; i++)
		{
			for (int j = 0; j < y2; j++)
			{
				for (int t = 0; t < y1; t++)
				{
					m3.mat[i][j] += (m1.mat[i][t] * m2.mat[t][j]);
				}
			}
		}
		return  m3;
	}
	return  m3;
}