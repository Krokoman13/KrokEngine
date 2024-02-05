#include "Transform.hpp"

Transform::Transform() : identity(), _parent(nullptr)
{
}

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
	identity.SetPos(pPos);
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
	SetGlobalMatrix(GetGlobalMatrix() * Matrix3::TranslateMatrix(pTrans));
}

void Transform::SetGlobalPosition(const Vec2& pPos)
{
	if (!_parent)
	{
		SetLocalPosition(pPos);
		return;
	}

	const Matrix3 globalparentMatrix = _parent->GetGlobalMatrix();
	const Matrix3 globalMatrix = globalparentMatrix * identity;

	identity = Matrix3(globalparentMatrix.Inverse()) *
		Matrix3::TranslateMatrix(pPos) *
		Matrix3::RotationMatrix(globalMatrix.GetRotVec()) *
		Matrix3::ScalingMatrix(globalMatrix.GetScale());
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
	if (!_parent)
	{
		SetLocalRotation(pRadians);
		return;
	}

	const Matrix3 globalparentMatrix = _parent->GetGlobalMatrix();
	const Matrix3 globalMatrix = globalparentMatrix * identity;

	identity = Matrix3(globalparentMatrix.Inverse()) *
		Matrix3::TranslateMatrix(globalMatrix.GetPos()) *
		Matrix3::RotationMatrix(pRadians) *
		Matrix3::ScalingMatrix(globalMatrix.GetScale());
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

float Transform::GetLocalXScale() const
{
	return identity.GetXAxisScale();
}

float Transform::GetLocalYScale() const
{
	return identity.GetYAxisScale();
}

Vec2 Transform::GetLocalScale() const
{
	return identity.GetScale();
}

void Transform::SetGlobalScale(const Vec2& pScale)
{
	if (!_parent)
	{
		SetLocalScale(pScale);
		return;
	}

	const Matrix3 globalparentMatrix = _parent->GetGlobalMatrix();
	const Matrix3 globalMatrix = globalparentMatrix * identity;

	identity = Matrix3(globalparentMatrix.Inverse()) *
		Matrix3::TranslateMatrix(globalMatrix.GetPos()) *
		Matrix3::RotationMatrix(globalMatrix.GetRotRad()) *
		Matrix3::ScalingMatrix(pScale);
}

void Transform::SetGlobalScale(const float pUniformScale)
{
	SetGlobalScale(Vec2(pUniformScale, pUniformScale));
}

float Transform::GetGlobalXScale() const
{
	Matrix3 globalMatrix = GetGlobalMatrix();
	return globalMatrix.GetXAxisScale();;
}

float Transform::GetGlobalYScale() const
{
	Matrix3 globalMatrix = GetGlobalMatrix();
	return globalMatrix.GetYAxisScale();;
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
	return _parent->GetGlobalMatrix() * identity;
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
