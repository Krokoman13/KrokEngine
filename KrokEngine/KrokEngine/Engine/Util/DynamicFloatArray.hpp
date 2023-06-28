#pragma once

struct DynamicFloatArray
{
public:
	DynamicFloatArray(const unsigned int pSize);
	DynamicFloatArray(const DynamicFloatArray& pOther);
	~DynamicFloatArray();

	const unsigned int GetSize() const;

	DynamicFloatArray operator=(const DynamicFloatArray& pOther);
	float& operator[](unsigned int i);

	const float operator[](unsigned int i)const;

private:
	unsigned int _size;
	float* _array;
};

