#include "GmObjctPtr.hpp"
#include "GameObject.hpp"

GmObjctPtr::GmObjctPtr(GameObject* pPointer)
{
	_pointer = pPointer;
}

GmObjctPtr::~GmObjctPtr()
{
	if (_pointer->GetParent() != nullptr) return;
	delete _pointer;
}

GameObject* GmObjctPtr::Get()
{
	return _pointer;
}

GmObjctPtr::operator GameObject* ()
{
	return _pointer;
}

GameObject* GmObjctPtr::operator=(GmObjctPtr other)
{
	return other.Get();
}

GameObject* GmObjctPtr::operator->()
{
	return _pointer;
}
