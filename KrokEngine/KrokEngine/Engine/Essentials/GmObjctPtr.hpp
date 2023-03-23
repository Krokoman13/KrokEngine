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
};

