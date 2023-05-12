#pragma once

struct DynamicFloatArray
{
public:
	DynamicFloatArray(const unsigned int pSize);
	DynamicFloatArray(const DynamicFloatArray& pOther);
	~DynamicFloatArray();

	//void Set(const unsigned int pCel, const float pValue);
	//float Get(const unsigned int pCel) const;

	const unsigned int GetSize() const;

	DynamicFloatArray operator=(const DynamicFloatArray& pOther);
	float& operator[](unsigned int i);

	const float operator[](unsigned int i)const;

private:
	unsigned int _size;
	float* _array;
};

