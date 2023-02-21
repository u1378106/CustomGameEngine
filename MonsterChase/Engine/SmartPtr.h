#pragma once
#include "Log.h"

class MasterList;
template<class T>
class WeakPtr;
template <class T>
class SmartPtr
{
private:
    T* p; // pointer to generic type T
    int* ownerCount; // number of copies
    int* observerCount;

public:
    // Constructor
    SmartPtr(T* _p = nullptr)
    {
        if (p == nullptr)
        {
            // Write 0 - no copies
            //count = 0;
        }

        else
        {
            ownerCount = new int;
            observerCount = new int;
            (*ownerCount) = 1;
            *observerCount = 0;
        }

        p = _p;
        //Log("Constructor");
    }

    // Copy constructor
    SmartPtr(const SmartPtr& obj)
    {
        // A copy is created
        p = obj.p;
        ownerCount = obj.ownerCount;
        observerCount = obj.observerCount;
        if (obj.p != nullptr)
        {
            // Increase count
            (*ownerCount)++;
        }
        //Log("Copy Constructor");
    }
 

    // Copy operator
    SmartPtr operator=(const SmartPtr& obj)
    {
        if (p != nullptr && p != obj.p)
        {
            (*ownerCount)--;
            if (*ownerCount == 0)
            {
                delete p;
                p = nullptr;
                if (*observerCount == 0)
                {
                    delete ownerCount;
                    delete observerCount;
                }
            }
        }
        // A copy is created
        p = obj.p;
        ownerCount = obj.ownerCount;
        observerCount = obj.observerCount;

        (*ownerCount)++;
        //Log("Equal operator");
        return *this;
    }

    // Destructor - destroys the original object,
    // copy objects are not destroyed.
    ~SmartPtr()
    {
        if ((p != nullptr))
        {
            (*ownerCount)--;
            if (*ownerCount == 0)
            {
                delete p;
                p = nullptr;
                if (*observerCount == 0)
                {
                    delete ownerCount;
                    delete observerCount;
                }
            }
        }
        //Log("Destructor");
    }

    template <class T>
    SmartPtr(WeakPtr<T>& other)
    {
        if (other.ownerCount == 0)
        {
            return;
        }
        p = other.weakPtr;
        ownerCount = (other.ownerCount);
        observerCount = (other.observerCount);
        *ownerCount++;
        Log("Constructor from Weak Ptr");
    }

    // Override operator -> access by pointer
    T* operator->()
    {
        return p;
    }


    // Override operator * access by pointer
    T& operator*()
    {
        return *p;
    }

    void Log(std::string infoText) {
        if (p == nullptr) {
            Engine::Log::I(infoText + " - Null Pointer");
        }
        else {
            Engine::Log::I(infoText + " Owners = " + std::to_string(*ownerCount) + " | Observers = " + std::to_string(*observerCount) +
                " | Location = " + std::to_string(reinterpret_cast<int>(p)));
        }
        
    }

    template<class T>
    friend class WeakPtr;
};