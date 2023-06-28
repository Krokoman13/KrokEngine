#include "Transform.hpp"
#include "../Core/Math/Vec2.hpp"

Transform::Transform(Vec2 pLocalPosition) : identity()
{
	SetLocalPosition(pLocalPosition);
}

Transform::Transform(float pX, float pY) : Transform(Vec2(pX, pY))
{
}

void Transform::SetParent(Transform* pParent)
{
	_parent = pParent;
}

void Transform::SetLocalPosition(Vec2 pPos)
{
	Vec2 current = identity.GetPos();
	identity.Translate(pPos - current);
}

void Transform::SetLocalPosition(float pX, float pY)
{
	SetLocalPosition(Vec2(pX, pY));
}

Vec2 Transform::GetLocalPosition() const
{
	return identity.GetPos();
}

void Transform::GlobalTranslate(Vec2 pTrans)
{
	identity = Matrix3::TranslateMatrix(pTrans) * identity * InverseModificationMatrix();
}

void Transform::SetGlobalPosition(Vec2 pPos)
{
	identity = Matrix3::TranslateMatrix(pPos) *
		Matrix3::ScalingMatrix(identity.GetScale()) *
		Matrix3::RotationMatrix(identity.GetRotVec()) *
		InverseModificationMatrix();
}

void Transform::SetGlobalPosition(float pX, float pY)
{
	SetGlobalPosition(Vec2(pX, pY));
}

Vec2 Transform::GetGlobalPosition() const
{
	Matrix3 globalMatrix = GetGlobalMatrix();
	return globalMatrix.GetPos();;
}

void Transform::SetLocalRotation(float pRadians)
{
	float current = identity.GetRotRad();
	identity.Rotate(pRadians - current);
}

float Transform::GetLocalRotationRad() const
{
	return identity.GetRotRad();
}

void Transform::SetGlobalRotation(float pRadians)
{
	identity = Matrix3::TranslateMatrix(identity.GetPos()) *
		Matrix3::ScalingMatrix(identity.GetScale()) *
		Matrix3::RotationMatrix(pRadians) *
		InverseModificationMatrix();
}

float Transform::GetGlobalRotationRad() const
{
	Matrix3 globalMatrix = GetGlobalMatrix();
	return globalMatrix.GetRotRad();;
}

void Transform::SetLocalScale(Vec2 pScale)
{
	Vec2 current = identity.GetScale();
	identity.Scale(Vec2(1/current.x * pScale.x, 1/current.y * pScale.y));
}

void Transform::SetLocalScale(float pX, float pY)
{
	SetLocalScale(Vec2(pX, pY));
}

Vec2 Transform::GetLocalScale() const
{
	return identity.GetScale();
}

void Transform::SetGlobalScale(Vec2 pScale)
{
	identity = Matrix3::TranslateMatrix(identity.GetPos()) *
		Matrix3::ScalingMatrix(pScale) *
		Matrix3::RotationMatrix(identity.GetRotVec()) *
		InverseModificationMatrix();
}

void Transform::SetGlobalScale(float pX, float pY)
{
	SetGlobalScale(Vec2(pX, pY));
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
