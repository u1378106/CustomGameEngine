#pragma once

template <class T>
class SmartPtr;
template<class T>
class WeakPtr
{
public:
	WeakPtr()
	{
		ownerCount = 0;
		observerCount = 0;
		weakP = nullptr;
	}


	template <class T>
	Weak_Ptr(SmartPtr<T>& other)
	{
		if (other.p)
		{
			weakP = other.p;
			observerCount = other.observerCount;
			ownerCount = other.ownerCount;
			(*observerCount)++;
		}
		else if (!(other.p))
		{
			weakP = nullptr;
			ownerCount = nullptr;
			observerCount = nullptr;
		}
	}

	//Copy Constructor
	WeakPtr(const WeakPtr& i_owner) :
		weakP = i_owner.p;
	ownerCount = obj.ownerCount;
	observerCount = obj.observerCount;
	pPtr(i_owner.pPtr)
	{
		if (observerCount != 0 && ownerCount != 0)
		{
			assert(observerCount > 0 || ownerCount > 0);
			(*observerCount)++;
		}
		else
		{
			assert(weakP == nullptr);
		}
	}


	~WeakPtr()
	{
		(*observerCount)--;
		if (*observerCount == 0)
		{
			if (*ownerCount == 0)
			{
				delete ownerCount;
				delete observerCount;
			}
		}
	}

	WeakPtr& operator=(const WeakPtr& i_other)
	{
		if (weakP != i_other.weakP)
		{
			ReleaseObservership();

			weakP = i_other.weakP;

			observerCount++;
		}

		return *this;

	}

	inline bool operator==(const WeakPtr& i_other)
	{
		return weakP == i_other.weakP;
	}


	void ReleaseObservership()
	{
		assert(observerCount > 0);
		if (observerCount == 0)
		{
			delete ownerCount;
			delete observerCount;
			ownerCount = null;
			observerCount = null;

			weakP = nullptr;
		}
		else
			assert(weakP == nullptr)
	}

	template<class T>
	inline SmartPtr<T> AcquireOwnership()
	{
		return SmartPtr<T>(*this);
	}


	template<class T>
	friend class SmartPtr;


private:
	T* weakP = 0;
	int* ownerCount = 0;
	int* observerCount = 0;
};


