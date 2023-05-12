#pragma once
#include "../Engine/Core/Graphics/ImageGameObject.hpp"
#include "../Engine/Core/Math/Vec2.hpp"

class MovingObject :
    public ImageGameObject
{
private:
    double i;

public:
    MovingObject(float x, float y);
    virtual void Update() override;
};

