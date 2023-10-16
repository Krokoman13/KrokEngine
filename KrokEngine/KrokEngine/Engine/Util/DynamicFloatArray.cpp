#include "DynamicFloatArray.hpp"
#include <stdexcept>

DynamicFloatArray::DynamicFloatArray(const unsigned int pSize)
{
	_size = pSize;
	_array = new float[pSize];

	for (unsigned int i = 0; i < _size; i++)
	{
		_array[i] = 0;
	}
}

DynamicFloatArray::DynamicFloatArray(const DynamicFloatArray& pOther) : DynamicFloatArray(pOther.GetSize())
{
	for (unsigned int i = 0; i < this->GetSize(); i++)
	{
		_array[i] = pOther._array[i];
	}
}

DynamicFloatArray::~DynamicFloatArray()
{
	delete _array;
}

const unsigned int DynamicFloatArray::GetSize() const
{
	return _size;
}

DynamicFloatArray DynamicFloatArray::operator=(const DynamicFloatArray& pOther)
{
	unsigned int size = pOther.GetSize();
	this->_size = size;

	delete[] this->_array;
	_array = new float[size];

	for (unsigned int i = 0; i < size; i++)
	{
		_array[i] = pOther._array[i];
	}

	return *this;
}

float& DynamicFloatArray::operator[](unsigned int i)
{
	if (i > this->GetSize() - 1) throw std::out_of_range("Cel is outside of the range of the array");
	return _array[i];
}

const float DynamicFloatArray::operator[](unsigned int i) const
{
	if (i > this->GetSize() - 1) throw std::out_of_range("Cel is outside of the range of the array");
	return _array[i];
}
