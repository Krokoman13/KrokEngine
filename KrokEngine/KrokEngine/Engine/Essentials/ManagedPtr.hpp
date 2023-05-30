#pragma once
#include "SlavePtr.hpp"

template <typename T>
class ManagedPtr : public SlavePtr<T>
{
public:
	using SlavePtr<T>::SlavePtr;

	using SlavePtr<T>::_pointer;
	using SlavePtr<T>::_destroyed;
	using SlavePtr<T>::_count;

	SlavePtr<T> GetSlavePtr() const
	{
		SlavePtr<T> slavePtr(_pointer);
		slavePtr._count = _count;
		slavePtr._destroyed = _destroyed;
		return slavePtr;
	}

	void Destroy()
	{
		if (*_destroyed) return;

		(*_destroyed) = true;

		delete _pointer;
		_pointer = nullptr;
	}
};


