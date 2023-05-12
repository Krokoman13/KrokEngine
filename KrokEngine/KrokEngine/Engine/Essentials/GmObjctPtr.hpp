class GameObject;

class GmObjctPtr
{
private:
	GameObject* _pointer;
	unsigned int* _count;
	bool* _destroyed;

public:
	GmObjctPtr(GameObject* pPointer);
	GmObjctPtr(const GmObjctPtr& pOther);
	~GmObjctPtr();
	GameObject* Get();
	void DeleteGameObject();

	operator GameObject* ();
	bool operator == (GmObjctPtr pOther);
	GmObjctPtr operator =(GmObjctPtr pOther);
	//GameObject* operator =(GmObjctPtr pOther);
	GameObject* operator ->();	

	void* operator new (size_t size) = delete;
};

