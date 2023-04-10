#pragma once

class GameObject;

class GmObjctPtr
{
private:
	GameObject* _pointer;

public:
	GmObjctPtr(GameObject* pPointer);
	~GmObjctPtr();
	GameObject* Get();

	operator GameObject* ();
	GameObject* operator =(GmObjctPtr pOther);
	GameObject* operator ->();	

	void* operator new (size_t size) = delete;
	void* operator new[](std::size_t) = delete;
};

