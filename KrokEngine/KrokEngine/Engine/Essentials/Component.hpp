#pragma once
#include "GameObject.hpp"

class Component
{
public:
	void SetGameObject(GameObject* pGameObject);

	virtual void OnLoad();
	virtual void Update();
	virtual void OnEnable();
	virtual void OnDisable();

	void SetActive(bool pEnabled = true);
	bool IsActive() const;

protected:
	GameObject* _gameObject;

private:
	bool _enabled = true;

};

