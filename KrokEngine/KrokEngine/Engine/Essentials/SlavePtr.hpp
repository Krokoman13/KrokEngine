#pragma once

template<typename T>
class SlavePtr
{
protected:
	T* _pointer;
	unsigned int* _count;
	bool* _destroyed;

public:
	//SlavePtr()
	//	: _pointer(nullptr), _count(new unsigned int(1)), _destroyed(new bool(true)) {}

	SlavePtr(T* pPointer, unsigned int* pCount, bool* pDestroyed) 
		: _pointer(pPointer), _count(pCount), _destroyed(pDestroyed) 
	{
		(*_count) = (*_count + 1);
		if (pDestroyed) pPointer = nullptr;
	}

	explicit SlavePtr(T* pPointer)
		: _pointer(pPointer), _count(new unsigned int(1)), _destroyed(new bool(false))
	{
		if (_pointer == nullptr)
			throw std::invalid_argument("Cannot create a CoPtr from a null pointer");
	}

	SlavePtr(const SlavePtr& pOther)
		: _pointer(pOther._pointer), _count(pOther._count), _destroyed(pOther._destroyed)
	{
		(*_count) = (*_count) + 1;;
	}

	~SlavePtr()
	{
		if (_count == nullptr) return;

		(*_count) = (*_count) - 1;

		if (*_count > 0) return;


		delete _count;
		_count = nullptr;

		if (!*_destroyed)
		{
			(*_destroyed) = true;
			delete _pointer;
		}

		_pointer = nullptr;
		delete _destroyed;
		_destroyed = nullptr;
	}

	bool IsDestroyed() const
	{
		if (_destroyed == nullptr) return true;
		return *_destroyed;
	}

	T* Get() const
	{
		return _pointer;
	}

	//const bool* GetDestroyedPtr() const { return _destroyed; }
	//const unsigned int* GetCountPtr() const { return _count; }

	operator T* () const
	{
		return _pointer;
	}

	bool operator==(const SlavePtr<T>& pOther) const
	{
		return _pointer == pOther._pointer;
	}

	SlavePtr& operator=(const SlavePtr<T>& pOther)
	{
		if (*this == pOther) return *this;

		if (_count != nullptr)
		{
			(*_count) = (*_count) - 1;

			if ((*_count) == 0)
			{
				delete _count;
				_count = nullptr;

				if (!*_destroyed)
				{
					(*_destroyed) = true;
					delete _pointer;
				}

				_pointer = nullptr;
				delete _destroyed;
				_destroyed = nullptr;
			}
		}

		_pointer = pOther._pointer;
		_count = pOther._count;
		_destroyed = pOther._destroyed;

		(*_count) = (*_count) + 1;
		return *this;
	}

	T* operator->() const
	{
		return _pointer;
	}

	//template<typename Y>
	//SlavePtr<Y> TryCast()
	//{
	//	static_assert(std::is_base_of<T, Y>::value, "Y must be a derived class of Component");

	//	Y* pointer = dynamic_cast<Y*>(_pointer);
	//	if (pointer == nullptr) return SlavePtr<Y>();
	//	SlavePtr<Y> outp(pointer, *_count, *_destroyed);
	//	return outp;
	//}

	void* operator new(size_t size) = delete;
};