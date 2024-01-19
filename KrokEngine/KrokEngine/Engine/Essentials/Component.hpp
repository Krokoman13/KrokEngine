#pragma once

class GameObject;

class Component
{
private:
	bool m_enabled = true;

protected:
	GameObject* m_gameObject;

public:
	Component();
	virtual ~Component();

public:
	void SetGameObject(GameObject* a_gameObject);
	GameObject* GetGameObject() const;

	virtual void OnLoad();
	virtual void Update();
	virtual void OnEnable();
	virtual void OnDisable();

	void SetActive(const bool a_enabled = true);
	bool IsActive() const;

protected:
	virtual void setGameObject(GameObject* a_gameObject);
};

