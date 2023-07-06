#pragma once
#include "../../Util/DynamicFloatArray.hpp"
#include <iostream>

struct Vec2;

struct  Matrix
{
private:
	unsigned int _columnCount;
	unsigned int _rowCount;
	DynamicFloatArray _elements;

public:
	Matrix(const unsigned int pRows, const unsigned int pColumns);
	Matrix(const Matrix& pOther);
	Matrix(const Vec2& pOther);
	~Matrix();

	const unsigned int GetColumns() const;
	const unsigned int GetRows() const;

	static Matrix Identity(const unsigned int size);

	const float Get(const unsigned int pRow, const unsigned int pColumn) const;
	void Set(const unsigned int pRow, const unsigned int pColumn, const float pValue);
	void Fill(const float pValue);

	Matrix Transposed() const;
	void Transpose();

	void SetArray(const DynamicFloatArray &pArray);
	const DynamicFloatArray GetArray() const;

	void SwapRows(const unsigned int pRowA, const unsigned int pRowB);
	Matrix SubMatrix(const unsigned int pExRow, unsigned int pExColumn) const;
	static Matrix ConcatenateVertically(const Matrix& pA, const Matrix& pB);
	static Matrix ConcatenateHorizontally(const Matrix& pA, const Matrix& pB);
	const float Determinant() const;
	const Matrix Inverse() const;

	Matrix operator=(const Matrix& other);

	friend std::ostream& operator<<(std::ostream& os, const Matrix& dt);
};

Matrix operator*(const Matrix& left, const Matrix& right);
Matrix operator*=(Matrix& left, const Matrix& right);
