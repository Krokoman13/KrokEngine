#pragma once
#include "../../Util/DynamicFloatArray.hpp"
#include <iostream>

struct Vec2;

struct  Matrix
{
private:
	unsigned int _columns;
	unsigned int _rows;
	DynamicFloatArray _array;

public:
	Matrix(const unsigned int pRows, const unsigned int pColumns);
	Matrix(const Matrix& pOther);
	Matrix(const Vec2& pOther);
	~Matrix();

	const unsigned int GetColumns() const;
	const unsigned int GetRows() const;

	static Matrix Identity(unsigned int size);

	const float Get(const unsigned int pRow, const unsigned int pColumn) const;
	void Set(const unsigned int pRow, const unsigned int pColumn, const float pValue);
	void Fill(const float pValue);

	Matrix Transposed() const;
	void Transpose();

	void SetArray(const DynamicFloatArray &pArray);
	const DynamicFloatArray GetArray() const;

	Matrix operator=(const Matrix& other);

	friend std::ostream& operator<<(std::ostream& os, const Matrix& dt);
};

Matrix operator*(const Matrix& left, const Matrix& right);
