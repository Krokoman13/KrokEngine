#pragma once
#include "GmObjctPtr.hpp"

class Component
{
public:
	virtual void SetGameObject(GmObjctPtr pGameObject);
	GmObjctPtr GetGameObject() const;

	virtual void OnLoad();
	virtual void Update();
	virtual void OnEnable();
	virtual void OnDisable();

	void SetActive(bool pEnabled = true);
	bool IsActive() const;

protected:
	GmObjctPtr _gameObject;

private:
	bool _enabled = true;

};

