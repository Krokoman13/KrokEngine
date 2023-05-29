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

protected:
	GameObject* _gameObject;

private:
	bool _enabled = true;

};

