#pragma once
#include "../Core/Math/Matrix3.hpp"

struct Vec2;

class Transform
{
public:
	Transform(Vec2 pLocalPosition);
	Transform(float pX, float pY);

	Matrix3 identity;

protected:
	Transform* _parent;

public:
	void SetParent(Transform* pParent);

	void SetLocalPosition(Vec2 pPos);
	void SetLocalPosition(float pX, float pY);
	Vec2 GetLocalPosition() const;

	void GlobalTranslate(Vec2 pTrans);
	void SetGlobalPosition(Vec2 pPos);
	void SetGlobalPosition(float pX, float pY);
	Vec2 GetGlobalPosition() const;

	void SetLocalRotation(float pRadians);
	float GetLocalRotationRad() const;

	void SetGlobalRotation(float pRadians);
	float GetGlobalRotationRad()const;

	void SetLocalScale(Vec2 pScale);
	void SetLocalScale(float pX, float pY);
	Vec2 GetLocalScale() const;

	void SetGlobalScale(Vec2 pScale);
	void SetGlobalScale(float pX, float pY);
	Vec2 GetGlobalScale() const;

	Matrix3 GetGlobalMatrix() const;
	void SetGlobalMatrix(const Matrix3& pMatrix);
	
	Matrix3 InverseModificationMatrix() const;
};