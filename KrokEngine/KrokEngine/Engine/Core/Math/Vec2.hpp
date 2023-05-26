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

	Vec2() : Vec2(0.0f, 0.0f) {}
	Vec2(float pX, float pY) : x(pX), y(pY) {}
	Vec2(const Vec2& other) = default;
	~Vec2() = default;

	Vec2& operator=(const Vec2& other) = default;

	Vec2 operator+(const Vec2& other) const;
	Vec2& operator+=(const Vec2& other);

	Vec2 operator-(const Vec2& other) const;
	friend Vec2 operator-(const Vec2& other);
	Vec2& operator-=(const Vec2& other);

	Vec2 operator*(float scalar) const;
	friend Vec2 operator*(float scalar, const Vec2& vec);
	Vec2& operator*=(float scalar);

	Vec2 operator/(float scalar) const;
	friend Vec2 operator/(float scalar, const Vec2& vec);
	Vec2& operator/=(float scalar);

	bool operator==(const Vec2& other) const;
	bool operator!=(const Vec2& other) const;

	float Length() const;
	float LengthSquared() const;
	Vec2 Normalized() const;
	void Normalize();
	Vec2 Normal();
	void SetLength(float length);
	void Set(float pX, float pY);
	
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
	Vec2 Project(const Vec2& other) const;
	Vec2 Reflected(const Vec2& pNormal, float pBounciness = 1) const;
	void Reflect(Vec2 pNormal, float pBounciness = 1);
	
	static float VectorDotProduct(Vec2 a, Vec2 b);

	static Vec2 Zero();
	static Vec2 Up();
	static Vec2 Down();
	static Vec2 Left();
	static Vec2 Right();

	friend std::ostream& operator << (std::ostream& out, const Vec2& vec);
};
