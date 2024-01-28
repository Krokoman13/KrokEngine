#pragma once
#include "../Math/Matrix.hpp"

struct Matrix3 : public Matrix
{
private:
	int m_xFlippedValue = 1;
	int m_yFlippedValue = 1;

public:
	Matrix3();
	explicit Matrix3(const Matrix& other);

public:
	void SetXPos(const float a_x);
	void SetYPos(const float a_y);
	void SetPos(const Vec2 a_pos);
	Vec2 GetPos() const;
	
	float GetXAxisScale() const;
	float GetYAxisScale() const;
	Vec2 GetScale() const;

	Vec2 GetRotVec() const;
	float GetRotRad() const;

	static Matrix3 TranslateMatrix(const Vec2& a_pos);
	static Matrix3 ScalingMatrix(const Vec2& a_scale);
	static Matrix3 RotationMatrix(const Vec2& a_rotation);
	static Matrix3 RotationMatrix(const float a_radians);

	void Translate(const Vec2& a_pos);
	void Scale(const Vec2& a_scale);
	void Rotate(const float a_radians);

	Matrix3 operator=(const Matrix3& a_other);
	Matrix3 operator*(const Matrix3& a_other) const;
};

