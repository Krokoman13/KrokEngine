#include "Transform.hpp"
#include "../Core/Math/Vec2.hpp"

Transform::Transform(const Vec2& pLocalPosition) : identity()
{
	SetLocalPosition(pLocalPosition);
}

Transform::Transform(const float pX, const float pY) : Transform(Vec2(pX, pY))
{
}

void Transform::SetParent(Transform* pParent)
{
	_parent = pParent;
}

void Transform::SetLocalPosition(const Vec2& pPos)
{
	Vec2 current = identity.GetPos();
	identity.Translate(pPos - current);
}

void Transform::SetLocalPosition(const float pX, const float pY)
{
	SetLocalPosition(Vec2(pX, pY));
}

Vec2 Transform::GetLocalPosition() const
{
	return identity.GetPos();
}

void Transform::GlobalTranslate(const Vec2& pTrans)
{
	identity = Matrix3::TranslateMatrix(pTrans) * identity * InverseModificationMatrix();
}

void Transform::SetGlobalPosition(const Vec2& pPos)
{
	Matrix3 global = GetGlobalMatrix();
	identity = Matrix3::TranslateMatrix(pPos) *
		Matrix3::RotationMatrix(identity.GetRotVec()) *
		Matrix3::ScalingMatrix(global.GetScale()) *
		InverseModificationMatrix();
}

void Transform::SetGlobalPosition(const float pX, const float pY)
{
	SetGlobalPosition(Vec2(pX, pY));
}

Vec2 Transform::GetGlobalPosition() const
{
	Matrix3 globalMatrix = GetGlobalMatrix();
	return globalMatrix.GetPos();;
}

void Transform::SetLocalRotation(const float pRadians)
{
	float current = identity.GetRotRad();
	identity.Rotate(pRadians - current);
}

float Transform::GetLocalRotationRad() const
{
	return identity.GetRotRad();
}

void Transform::SetGlobalRotation(const float pRadians)
{
	identity = Matrix3::TranslateMatrix(identity.GetPos()) *
		Matrix3::RotationMatrix(pRadians) *
		Matrix3::ScalingMatrix(identity.GetScale()) *
		InverseModificationMatrix();
}

float Transform::GetGlobalRotationRad() const
{
	Matrix3 globalMatrix = GetGlobalMatrix();
	return globalMatrix.GetRotRad();;
}

void Transform::SetLocalScale(Vec2 pScale)
{
	if (pScale.x == 0.0f) pScale.x = 0.00000000001f;
	if (pScale.y == 0.0f) pScale.y = 0.00000000001f;

	Vec2 current = identity.GetScale();
	identity.Scale(Vec2(1/current.x * pScale.x, 1/current.y * pScale.y));
}

void Transform::SetLocalScale(const float pUniformScale)
{
	SetLocalScale(Vec2(pUniformScale, pUniformScale));
}

Vec2 Transform::GetLocalScale() const
{
	return identity.GetScale();
}

void Transform::SetGlobalScale(const Vec2& pScale)
{
	identity = Matrix3::TranslateMatrix(identity.GetPos()) *
		Matrix3::RotationMatrix(identity.GetRotVec()) *
		Matrix3::ScalingMatrix(pScale) *
		InverseModificationMatrix();
}

void Transform::SetGlobalScale(const float pUniformScale)
{
	SetGlobalScale(Vec2(pUniformScale, pUniformScale));
}

Vec2 Transform::GetGlobalScale() const
{
	Matrix3 globalMatrix = GetGlobalMatrix();
	return globalMatrix.GetScale();;
}

Matrix3 Transform::GetGlobalMatrix() const
{
	Matrix3 outp = identity;

	if (!_parent) return identity;
	return (Matrix3)(_parent->GetGlobalMatrix() * identity);
}

void Transform::SetGlobalMatrix(const Matrix3& pMatrix)
{
	identity = InverseModificationMatrix() * pMatrix;
}

Matrix3 Transform::InverseModificationMatrix() const
{
	if (!_parent) return Matrix3();
	return (Matrix3)_parent->GetGlobalMatrix().Inverse();
}
