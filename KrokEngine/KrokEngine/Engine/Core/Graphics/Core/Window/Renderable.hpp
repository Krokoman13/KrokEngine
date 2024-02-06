#pragma once
#include "../../../../Essentials/Transform.hpp"
#include "../../../../Essentials/Component.hpp"

class Renderable : public Component, public Transform
{
private:
	int m_renderLayer = 0;
	int m_previousRenderLayer = 0;

	bool m_visable = false;

public:
	Renderable() {};
	virtual ~Renderable() {};

public:
	virtual void OnLoad() override { SetLayerUnchanged(); };
	virtual void Display(const Matrix3& a_pojectionMatrix) const = 0;

	bool IsVisable() { return m_visable; };
	void OnEnable() { m_visable = true; };
	void OnDisable() { m_visable = false; };

	void SetRenderLayer(int a_renderLayer)
	{
		if (m_renderLayer == a_renderLayer) return;
		m_renderLayer = a_renderLayer;
	};

	int GetLayer() const { return m_renderLayer; };
	int GetPrevLayer() const { return m_previousRenderLayer; };
	bool HasChangedLayer() const { return m_renderLayer != m_previousRenderLayer; };
	void SetLayerUnchanged() { m_previousRenderLayer = m_renderLayer; };

protected:
	virtual void setGameObject(GameObject* a_gameObject) override;
};

