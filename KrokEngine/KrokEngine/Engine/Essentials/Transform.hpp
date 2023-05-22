#pragma once
#include "../Core/Math/Matrix3.hpp"

struct Vec2;

class Transform
{
public:
	Transform(Vec2 pPos);
	Transform(float pX, float pY);
	//~Transform();

	Matrix3 identity;

protected:
	Transform* _parent;

public:
	void SetParent(Transform* pParent);

	void SetLocalPosition(Vec2 pPos);
	void SetLocalPosition(float pX, float pY);
	Vec2 GetLocalPosition() const;

	void SetGlobalPosition(Vec2 pPos);
	void SetGlobalPosition(float pX, float pY);
	Vec2 GetGlobalPosition() const;

	void SetLocalRotation(Vec2 pRot);
	void SetLocalRotation(float pRadians);
	float GetLocalRotationRad() const;

	void SetGlobalRotation(Vec2 pRot);
	void SetGlobalRotation(float pRadians);
	float GetGlobalRotationRad()const;

	void SetLocalScale(Vec2 pScale);
	void SetLocalScale(float pX, float pY);
	Vec2 GetLocalScale() const;

	void SetGlobalScale(Vec2 pScale);
	void SetGlobalScale(float pX, float pY);
	Vec2 GetGlobalScale() const;

	Matrix3 GetGlobalMatrix() const;
};