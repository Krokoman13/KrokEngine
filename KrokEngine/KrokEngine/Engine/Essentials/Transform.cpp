#include "Transform.hpp"
#include "../Core/Math/Vec2.hpp"

Transform::Transform(Vec2 pPos) : _identity()
{
	SetLocalPosition(pPos);

	//std::cout << _identity;
}

Transform::Transform(float pX, float pY) : Transform(Vec2(pX, pY))
{
}

void Transform::SetLocalPosition(Vec2 pPos)
{
	Vec2 current = _identity.GetPos();
	_identity.Translate(pPos - current);
}

void Transform::SetLocalPosition(float pX, float pY)
{
	SetLocalPosition(Vec2(pX, pY));
}

Vec2 Transform::GetLocalPosition() const
{
	return _identity.GetPos();
}

void Transform::SetGlobalPosition(Vec2 pPos)
{
	Vec2 current = GetGlobalPosition();
	_identity.Translate(pPos - current);
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

void Transform::SetLocalRotation(Vec2 pRot)
{
	SetLocalRotation(pRot.GetAngleRadians());
}

void Transform::SetLocalRotation(float pRadians)
{
	float current = _identity.GetRotRad();
	_identity.Rotate(pRadians - current);
}

float Transform::GetLocalRotationRad() const
{
	return _identity.GetRotRad();
}

void Transform::SetGlobalRotation(Vec2 pRot)
{
	SetGlobalRotation(pRot.GetAngleRadians());
}

void Transform::SetGlobalRotation(float pRadians)
{
	float current = GetGlobalRotationRad();
	_identity.Rotate(pRadians - current);
}

float Transform::GetGlobalRotationRad() const
{
	Matrix3 globalMatrix = GetGlobalMatrix();
	return globalMatrix.GetRotRad();;
}

void Transform::SetLocalScale(Vec2 pScale)
{
	Vec2 current = _identity.GetScale();
	_identity.Scale(Vec2(1/current.x, 1/current.y));
	_identity.Scale(pScale);
}

void Transform::SetLocalScale(float pX, float pY)
{
	SetLocalScale(Vec2(pX, pY));
}

Vec2 Transform::GetLocalScale() const
{
	return _identity.GetScale();
}

void Transform::SetGlobalScale(Vec2 pScale)
{
	Vec2 current = GetGlobalScale();
	_identity.Scale(Vec2(1 / current.x, 1 / current.y));
	_identity.Scale(pScale);
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
	Matrix3 outp = _identity;

	if (_parent == nullptr) return _identity;
	return (Matrix3)(_parent->GetGlobalMatrix() * _identity);
}
