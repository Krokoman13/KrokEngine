#pragma once
#include <iostream>

struct Matrix;

/// <summary>
/// 2D Vector. Meant for 2D physics calculations.
/// </summary>
struct Vec2 
{
	float x;
	float y;

	Vec2();
	Vec2(float pX, float pY);
	Vec2(float pX, float pY, bool normalized);
	explicit Vec2(const Matrix& other);

	Vec2& operator =(const Vec2& other);
	Vec2& operator *=(const float& other);

	float GetLength() const;
	Vec2 Normalized() const;
	void Normalize();

	void SetLength(float length);
	void SetXY(float pX, float pY);

	static Vec2 LinInt(Vec2 left, Vec2 right, float interpolater);
	static float Deg2Rad(float degree);
	static float Rad2Deg(float radians);
	static Vec2 GetUnitVectorDeg(float degrees);
	static Vec2 GetUnitVectorRad(float radians);

	void SetAngleDegrees(float degrees);
	void SetAngleRadians(float radians);

	float GetAngleRadians();
	float GetAngleDegrees();
	void RotateRadians(float radians);
	void RotateDegrees(float degrees);
	void RotateAroundDegrees(float degrees, Vec2 around);
	void RotateAroundRadians(float radians, Vec2 around);

	static float normalizeDeg(float degree);

	void RotateTowardsDegrees(float targetDegrees, float stepDegrees);

	float Dot(Vec2 other) const;
	static float VectorDotProduct(Vec2 a, Vec2 b);

	Vec2 Normal();
	Vec2 Reflected(const Vec2& pNormal, float pBounciness = 1) const;
	void Reflect(Vec2 pNormal, float pBounciness = 1);

	friend std::ostream& operator << (std::ostream& out, const Vec2& vec);
};

Vec2 operator +(const Vec2& left, const Vec2& right);
Vec2 operator +=(Vec2& left, const Vec2& right);

Vec2 operator -(const Vec2& left, const Vec2& right);
Vec2 operator-=(Vec2& left, const Vec2& right);

Vec2 operator *(const Vec2& left, const float& right);
Vec2 operator *(const float& left, const Vec2& right);

Vec2 operator *(const Vec2& left, const Vec2& right);
Vec2 operator *=(Vec2& left, const Vec2& right);

Vec2 operator /(const Vec2& left, const float& right);

bool operator ==(const Vec2& left, const Vec2& right);
bool operator !=(const Vec2& left, const Vec2& right);
