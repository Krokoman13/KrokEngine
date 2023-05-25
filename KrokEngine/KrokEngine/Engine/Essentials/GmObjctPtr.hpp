#pragma once

class GameObject;

class GmObjctPtr
{
private:
	GameObject* _pointer;
	unsigned int* _count;
	bool* _destroyed;

public:
	GmObjctPtr();
	explicit GmObjctPtr(GameObject* pPointer);
	GmObjctPtr(const GmObjctPtr& pOther);
	~GmObjctPtr();
	bool IsDestroyed() const;
	GameObject* Get() const;
	void DeleteGameObject();

	operator GameObject* ();
	bool operator == (GmObjctPtr pOther) const;
	GmObjctPtr operator =(GmObjctPtr pOther);
	//GameObject* operator =(GmObjctPtr pOther);
	GameObject* operator ->() const;	

	void* operator new (size_t size) = delete;
};

