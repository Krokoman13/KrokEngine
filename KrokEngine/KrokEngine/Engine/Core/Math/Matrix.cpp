#include "Matrix.hpp"
#include "Vec2.hpp"

const unsigned int Matrix::GetColumns() const
{
	return _columns;
}

const unsigned int Matrix::GetRows() const
{
	return _rows;
}

Matrix::Matrix(const unsigned int pX, const unsigned int pY) : _array(pX* pY)
{
	this->_rows = pX;
	this->_columns = pY;
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

Matrix Matrix::Identity(unsigned int size)
{
	Matrix out(size, size);
	out.Fill(0);

	for (unsigned int i = 0; i < size; i++) out.Set(i,i, 1);

	return out;
}

const float Matrix::Get(const unsigned int pColumn, const unsigned int pRow) const
{
	if (pRow > _rows - 1 || pColumn > _columns - 1) throw std::out_of_range("Tried to acces value out of range");
	unsigned int i = pRow + pColumn * _rows;
	return _array[i];
}

void Matrix::Set(const unsigned int pColumn, const unsigned int pRow, const float value)
{
	if (pRow > _rows - 1 || pColumn > _columns - 1) throw std::out_of_range("Tried to acces value out of range");
	unsigned int i = pRow + pColumn * _rows;
	_array[i] = value;
}

void Matrix::Fill(const float value)
{
	for (unsigned int i = 0; i < _columns * _rows; i++)
	{
		_array[i] = value;
	}
}

Matrix Matrix::Transposed() const
{
	Matrix transposed = Matrix(_rows, _columns);

	for (unsigned int y = 0; y < transposed._rows; y++)
	{
		for (unsigned int x = 0; x < transposed._columns; x++)
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
	_array = pArray;
}

const DynamicFloatArray Matrix::GetArray() const
{
	return _array;
}

Matrix Matrix::operator=(const Matrix& other)
{
	//if (other.columns != this->columns || other.rows != this->rows) throw std::out_of_range("Invalid size Matrix");
	this->_columns = other._columns;
	this->_rows = other._rows;
	this->_array = other._array;

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
	if (right.GetColumns() != left.GetRows()) throw std::invalid_argument("Invalid size of Matrixes to multiply");

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
