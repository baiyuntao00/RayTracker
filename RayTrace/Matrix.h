#pragma once
#include "CountData.hpp"
class Matrix
{
public:
	Matrix();
	Matrix(int r, int c);
	~Matrix();
	float GetSum();
	friend Matrix operator +(Matrix &ma, Matrix&m2);
	friend Matrix operator -(Matrix &ma, Matrix&m2);
	friend Matrix operator *(Matrix &ma, Matrix&m2);
	friend Matrix operator *(float a, Matrix&m2);
	float mat[10][10];
public:
	int column/*ÁÐ*/, row/*ÐÐ*/;
};

