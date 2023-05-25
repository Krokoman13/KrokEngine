#include "GmObjctPtr.hpp"
#include "GameObject.hpp"
#include <stdexcept>

GmObjctPtr::GmObjctPtr()
{
	_pointer = nullptr;
	_destroyed = new bool(true);
	_count = new unsigned int(1);
}

GmObjctPtr::GmObjctPtr(GameObject* pPointer)
{
	if (pPointer == nullptr) throw std::invalid_argument("Cannot create a GmObjectPtr from a nullpointer");

	_pointer = pPointer;
	_destroyed = new bool(false);
	_count = new unsigned int(1);

	pPointer->SetPtr(*this);
}

GmObjctPtr::GmObjctPtr(const GmObjctPtr& pOther)
{
	this->_pointer = pOther._pointer;
	this->_count = pOther._count;
	this->_destroyed = pOther._destroyed;
}

GmObjctPtr::~GmObjctPtr()
{
	unsigned int  currentCount = *_count;

	if (currentCount < 1)
	{
		if (!*_destroyed) delete _pointer;
		delete _count;
		delete _destroyed;
		return;
	}
}

bool GmObjctPtr::IsDestroyed() const
{
	return *_destroyed;
}

GameObject* GmObjctPtr::Get() const
{
	return _pointer;
}

void GmObjctPtr::DeleteGameObject()
{
	(*_destroyed) = true;
	if (_pointer == nullptr) return;
	delete _pointer;
}

GmObjctPtr::operator GameObject* ()
{
	return _pointer;
}

bool GmObjctPtr::operator==(GmObjctPtr pOther) const
{
	return this->Get() == pOther.Get();
}

GmObjctPtr GmObjctPtr::operator=(GmObjctPtr pOther)
{
	this->_pointer = pOther._pointer;
	this->_count = pOther._count;
	this->_destroyed = pOther._destroyed;
	return *this;
}

GameObject* GmObjctPtr::operator->() const
{
	return _pointer;
}
