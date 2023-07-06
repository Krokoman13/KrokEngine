#pragma once
#include "../Core/Math/Matrix3.hpp"

struct Vec2;

class Transform
{
public:
	Transform(const Vec2& pLocalPosition);
	Transform(const float pX, const float pY);

	Matrix3 identity;

protected:
	Transform* _parent;

public:
	void SetParent(Transform* pParent);

	void SetLocalPosition(const Vec2& pPos);
	void SetLocalPosition(const float pX, const float pY);
	Vec2 GetLocalPosition() const;

	void GlobalTranslate(const Vec2& pTrans);
	void SetGlobalPosition(const Vec2& pPos);
	void SetGlobalPosition(const float pX, const float pY);
	Vec2 GetGlobalPosition() const;

	void SetLocalRotation(const float pRadians);
	float GetLocalRotationRad() const;

	void SetGlobalRotation(const float pRadians);
	float GetGlobalRotationRad()const;

	void SetLocalScale(Vec2 pScale);
	void SetLocalScale(const float pUniformScale);
	Vec2 GetLocalScale() const;

	void SetGlobalScale(const Vec2& pScale);
	void SetGlobalScale(const float pUniformScale);
	Vec2 GetGlobalScale() const;

	Matrix3 GetGlobalMatrix() const;
	void SetGlobalMatrix(const Matrix3& pMatrix);
	
	Matrix3 InverseModificationMatrix() const;
};