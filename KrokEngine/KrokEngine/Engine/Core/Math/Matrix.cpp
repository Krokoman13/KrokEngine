#include "Matrix.hpp"
#include "Vec2.hpp"

Matrix::Matrix(const unsigned int pRows, const unsigned int pColumns) : _elements(pRows * pColumns)
{
	_rowCount = pRows;
	_columnCount = pColumns;
}

const unsigned int Matrix::GetColumns() const
{
	return _columnCount;
}

const unsigned int Matrix::GetRows() const
{
	return _rowCount;
}


Matrix::Matrix(const Matrix& other) : Matrix(other.GetColumns(), other.GetRows())
{
	for (unsigned int y = 0; y < other.GetRows(); y++)
	{
		for (unsigned int x = 0; x < other.GetColumns(); x++)
		{
			this->Set(x, y, other.Get(x, y));
		}
	}
}

Matrix::Matrix(const Vec2& other) : Matrix(1, 2)
{
	Set(0, 0, other.x);
	Set(0, 1, other.y);
}

Matrix::~Matrix()
{
}

Matrix Matrix::Identity(const unsigned int size)
{
	Matrix out(size, size);

	for (unsigned int i = 0; i < size; i++) out.Set(i,i, 1);

	return out;
}

const float Matrix::Get(const unsigned int pColumn, const unsigned int pRow) const
{
	if (pRow >= _rowCount || pColumn >= _columnCount) throw std::out_of_range("Tried to acces value out of range");
	unsigned int i = pRow + pColumn * _rowCount;
	return _elements[i];
}

void Matrix::Set(const unsigned int pColumn, const unsigned int pRow, const float value)
{
	if (pRow >= _rowCount || pColumn >= _columnCount) throw std::out_of_range("Tried to acces value out of range");
	unsigned int i = pRow + pColumn * _rowCount;
	_elements[i] = value;
}

void Matrix::Fill(const float value)
{
	for (unsigned int i = 0; i < _columnCount * _rowCount; i++)
	{
		_elements[i] = value;
	}
}

Matrix Matrix::Transposed() const
{
	Matrix transposed = Matrix(_rowCount, _columnCount);

	for (unsigned int y = 0; y < transposed._rowCount; y++)
	{
		for (unsigned int x = 0; x < transposed._columnCount; x++)
		{
			transposed.Set(x, y, this->Get(y, x));
		}
	}

	return transposed;
}

void Matrix::Transpose()
{
	(*this) = this->Transposed();
}

void Matrix::SetArray(const DynamicFloatArray& pArray)
{
	if (this->GetColumns() * this->GetRows() != pArray.GetSize()) throw std::out_of_range("Invalid size Array");
	_elements = pArray;
}

const DynamicFloatArray Matrix::GetArray() const
{
	return _elements;
}

void Matrix::SwapRows(const unsigned int pRowA, const unsigned int pRowB)
{
	if (pRowA >= _rowCount || pRowB >= _rowCount) throw std::out_of_range("Matrix: Row index out of range.");
	if (pRowA == pRowB) return;

	for (unsigned int i = 0; i < _columnCount; i++)
	{
		float temp = Get(i, pRowA);
		Set(i, pRowA, Get(i, pRowB));
		Set(i, pRowA, temp);
	}
}


Matrix Matrix::SubMatrix(const unsigned int pExRow, const unsigned int pExColumn) const
{
	const unsigned int size = GetRows();
	Matrix submatrix(size - 1, size - 1);

	unsigned int subRow = 0;
	unsigned int subColumn = 0;

	for (unsigned int row = 0; row < size; row++)
	{
		if (row == pExRow) continue;

		subColumn = 0;

		for (unsigned int column = 0; column < size; column++)
		{
			if (column == pExColumn) continue;

			submatrix.Set(subRow, subColumn, Get(row, column));
			subColumn++;
		}

		subRow++;
	}

	return submatrix;
}

Matrix Matrix::ConcatenateVertically(const Matrix& a, const Matrix& b)
{
	if (a._columnCount != b._columnCount)
	{
		throw std::invalid_argument("Matrix: Number of columns must be the same for concatenation.");
	}

	Matrix concatenatedMatrix(a._rowCount + b._rowCount, a._columnCount);

	for (unsigned int y = 0; y < a._rowCount; y++)
	{
		for (unsigned int x = 0; x < a._columnCount; x++)
		{
			concatenatedMatrix.Set(x, y, a.Get(x, y));
		}
	}

	for (unsigned int y = 0; y < b._rowCount; y++)
	{
		for (unsigned int x = 0; x < b._columnCount; x++)
		{
			concatenatedMatrix.Set(x, y + a._rowCount, b.Get(x, y));
		}
	}

	return concatenatedMatrix;
}

Matrix Matrix::ConcatenateHorizontally(const Matrix& a, const Matrix& b)
{
	if (a._rowCount != b._rowCount)
	{
		throw std::invalid_argument("Matrix: Number of columns must be the same for concatenation.");
	}

	Matrix concatenatedMatrix(a._rowCount, a._columnCount + b._columnCount);

	for (unsigned int y = 0; y < a._rowCount; y++)
	{
		for (unsigned int x = 0; x < a._columnCount; x++)
		{
			concatenatedMatrix.Set(x, y, a.Get(x, y));
		}
	}

	for (unsigned int y = 0; y < b._rowCount; y++)
	{
		for (unsigned int x = 0; x < b._columnCount; x++)
		{
			concatenatedMatrix.Set(x + a._columnCount, y, b.Get(x, y));
		}
	}

	return concatenatedMatrix;
}

const float Matrix::Determinant() const
{
	if (_rowCount != _columnCount) throw std::runtime_error("Matrix: Determinant does not exist, matrix is not square.");

	unsigned int n = _rowCount;

	if (n == 1) return Get(0, 0);
	if (n == 2)	return Get(0, 0) * Get(1, 1) - Get(0, 1) * Get(1, 0);

	const unsigned int size = GetRows();

	if (size == 1)
		return Get(0, 0);

	float determinant = 0.0f;
	Matrix submatrix(size - 1, size - 1);

	for (unsigned int i = 0; i < size; i++)
	{
		submatrix = SubMatrix(0, i);
		determinant += (i % 2 == 0 ? 1.0f : -1.0f) * Get(0, i) * submatrix.Determinant();
	}

	return determinant;
}

const Matrix Matrix::Inverse() const
{
	if (_rowCount != _columnCount) throw std::runtime_error("Matrix: Inverse does not exist, matrix is not square.");

	float determinant = Determinant();

	if (determinant == 0)
	{
		throw std::logic_error("Matrix is not invertible.");
	}

	Matrix outp(_rowCount, _columnCount);

	for (unsigned int y = 0; y < _rowCount; y++)
	{
		for (unsigned int x = 0; x < _columnCount; x++)
		{
			Matrix sub = SubMatrix(x, y);
			float cofactor = sub.Determinant();
			cofactor *= ((x + y) % 2 == 0) ? 1 : -1;
			outp.Set(y, x, cofactor / determinant);
		}
	}

	return outp;
}
	

Matrix Matrix::operator=(const Matrix& other)
{
	//if (other.columns != this->columns || other.rows != this->rows) throw std::out_of_range("Invalid size Matrix");
	_columnCount = other._columnCount;
	_rowCount = other._rowCount;
	_elements = other._elements;

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Matrix& dt)
{
	for (unsigned int y = 0; y < dt.GetRows(); y++)
	{
		os << '[';
		unsigned int x = 0;
		while (true)
		{
			os << dt.Get(x, y);
			if (x >= dt.GetColumns() - 1) break;
			os << ',';
			x++;
		}
		os << "]\n";
	}

	return os;
}

Matrix operator*(const Matrix& left, const Matrix& right)
{
	if (right.GetColumns() != left.GetRows())
	{
		throw std::invalid_argument("Invalid size of Matrixes to multiply");
	}

	Matrix out(left.GetColumns(), right.GetRows());

	for (unsigned int y = 0; y < out.GetRows(); y++)
	{
		for (unsigned int x = 0; x < out.GetColumns(); x++)
		{
			float value = 0;
			for (unsigned int i = 0; i < right.GetColumns(); i++)
			{
				float val1 = left.Get(x, i);
				float val2 = right.Get(i, y);
				value += val1 * val2;
			}
			out.Set(x,y, value);
		}
	}

	return out;
}

Matrix operator*=(Matrix& left, const Matrix& right)
{
	left = left * right;
	return left;
}
