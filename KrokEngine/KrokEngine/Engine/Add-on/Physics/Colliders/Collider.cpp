#include "Collider.hpp"
#include "LineCollider.hpp"
#include "CircleCollider.hpp"
#include "../Components/ColliderComponent.hpp"

void Collider::SetParent(Transform* pParent)
{
    if (pParent == nullptr) return;

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

