#pragma once

class GameObject;

class Component
{
public:
	virtual void SetGameObject(GameObject* pGameObject);
	GameObject* GetGameObject() const;

	virtual void OnLoad();
	virtual void Update();
	virtual void OnEnable();
	virtual void OnDisable();

	void SetActive(bool pEnabled = true);
	bool IsActive() const;

	virtual bool IsExclusive();

protected:
	GameObject* _gameObject = nullptr;

private:
	bool _enabled = true;

};

