#include "Matrix3.hpp"
#include "Vec2.hpp"

Matrix3::Matrix3(): Matrix(Matrix::Identity(3))
{
	//Set(2, 2, 0);
}

Matrix3::Matrix3(const Matrix& pOther) : Matrix(3, 3)
{
	if (pOther.GetColumns() != 3 || pOther.GetRows() != 3) throw std::out_of_range("Invalid size Matrix");
	SetArray(pOther.GetArray());
}

Vec2 Matrix3::GetPos() const
{
	return Vec2(Get(0,2), Get(1, 2));
}

Vec2 Matrix3::GetScale() const
{
	Vec2 xAxis = Vec2(Get(0, 0), Get(1, 0));
	Vec2 yAxis = Vec2(Get(0, 1), Get(1, 1));
	return Vec2(xAxis.GetLength(), yAxis.GetLength());
}

Vec2 Matrix3::GetRotVec() const
{
	Vec2 xAxis = Vec2(Get(0, 0), Get(1, 0));
	return xAxis.Normalized();
}

float Matrix3::GetRotRad() const
{
	return GetRotVec().GetAngleRadians();
}

Matrix3 Matrix3::TranslateMatrix(const Vec2& pPos)
{
	Matrix3 out;
	out.Set(0, 2, pPos.x);
	out.Set(1, 2, pPos.y);
	return out;
}

Matrix3 Matrix3::ScalingMatrix(const Vec2& pScale)
{
	Matrix3 out;
	out.Set(0, 0, pScale.x);
	out.Set(1, 0, 0);
	out.Set(0, 1, 0);
	out.Set(1, 1, pScale.x);
	return out;
}

Matrix3 Matrix3::RotationMatrix(float radians)
{
	Matrix3 out;
	out.Set(0, 0, std::cos(radians));
	out.Set(1, 0, std::sin(radians));
	out.Set(0, 1, -std::sin(radians));
	out.Set(1, 1, std::cos(radians));
	return out;
}

void Matrix3::Translate(const Vec2& pPos)
{
	(*this) = (*this) * TranslateMatrix(pPos);
}

void Matrix3::Scale(const Vec2& pScale)
{
	(*this) = (*this) * ScalingMatrix(pScale);
}

void Matrix3::Rotate(const float pRadians)
{
	(*this) = (*this) * RotationMatrix(pRadians);
}

Matrix3 Matrix3::operator=(const Matrix& pOther)
{
	if (pOther.GetColumns() != 3 || pOther.GetRows() != 3) throw std::out_of_range("Invalid size Matrix");

	for (unsigned int y = 0; y < pOther.GetRows(); y++)
	{
		for (unsigned int x = 0; x < pOther.GetColumns(); x++)
		{
			this->Set(x, y, pOther.Get(x, y));
		}
	}

	return *this;
}
