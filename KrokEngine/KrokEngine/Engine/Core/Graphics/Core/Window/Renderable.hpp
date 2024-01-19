#pragma once
#include "../../../../Essentials/Transform.hpp"
#include "../../../../Essentials/Component.hpp"

class Renderable : public Component, public Transform
{
private:
	int m_renderLayer = 0;
	bool m_layerChanged = false;

public:
	Renderable() {};
	virtual ~Renderable() {};

public:
	virtual void Display(const Matrix3& a_pojectionMatrix) const = 0;

	void SetRenderLayer(int a_renderLayer)
	{
		if (m_renderLayer == a_renderLayer) return;
		m_renderLayer = a_renderLayer;
		m_layerChanged = true;
	};

	int GetLayer() const { return m_renderLayer; };
	bool HasChangedLayer() const { return m_layerChanged; };
	void SetLayerUnchanged() { m_layerChanged = false; };

protected:
	virtual void setGameObject(GameObject* a_gameObject) override;
};

