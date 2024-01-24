#pragma once
#include <memory>
#include "../../../../Essentials/Component.hpp"
#include "../../../../Core/Math/Shapes/Rectangle.hpp"
#include "../../../../Core/Math/Shapes/Circle.hpp"

class Hoverable : public Component
{
private:
	std::unique_ptr<Shape> m_shape;
	int m_layer = 1;

protected:
	bool m_isOver = false;

public:
	Hoverable(const Circle a_cirlce, const int a_layer = 1) : m_layer(a_layer) { SetShape(a_cirlce); };
	Hoverable(const Rectangle a_rectangle, const int a_layer = 1) : m_layer(a_layer) { SetShape(a_rectangle); };
	virtual ~Hoverable();

public:
	void SetShape(const Circle a_cirlce);
	void SetShape(const Rectangle a_rectangle);

	void SetLayer(const int a_layer) { m_layer = a_layer; };
	int GetLayer() const { return m_layer; };

	bool IsInside(const Vec2 a_point) const;
	void SetHovering(const bool a_isOver);
	bool IsHovering() { return m_isOver; };

	virtual void OnStartHovering();
	virtual void OnStopHovering();

protected:
	virtual void changeHovering(const bool a_isOver);
};

