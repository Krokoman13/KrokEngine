#include "Collider.hpp"
#include "LineCollider.hpp"
#include "CircleCollider.hpp"
#include "../ColliderComponent.hpp"

bool Collider::Colliding(const CircleCollider* pOther) const
{
    return false;
}

bool Collider::Colliding(const LineCollider* pOther) const
{
    return false;
}


bool Collider::Colliding(const Collider* pOther) const
{
    if (const CircleCollider* circle = dynamic_cast<const CircleCollider*>(pOther)) {
        return Colliding(circle);
    }

    if (const LineCollider* line = dynamic_cast<const LineCollider*>(pOther)) {
        return Colliding(line);
    }

    return false;
}

void Collider::SetParent(GameObject* pGameObject)
{
    if (pGameObject == nullptr) return;
}

void Collider::SetColliderComponent(ColliderComponent* pGameObject)
{
    if (_colliderComponent != nullptr) throw std::logic_error("Cannot reassign collider to a diffrent component");
    _colliderComponent = pGameObject;

    SetParent(_colliderComponent->GetGameObject());
}

ColliderComponent* Collider::GetColliderComponent() const
{
    return _colliderComponent;
}

