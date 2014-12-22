#pragma once
#include <memory>

// Not ThreadSafe - �Ű� ����...
template< typename T >
class cSingleTon
    : public T
{
private:
    static std::unique_ptr<T> m_instance;

public:
    static T&   Get()
    {
        if( m_instance == nullptr )
        {
            m_instance.reset( new T() );
        }
        return *m_instance;
    }

    static void Destroy()
    {
        m_instance.reset( nullptr );
    }
};

template< typename T >
std::unique_ptr<T>  cSingleTon<T>::m_instance( nullptr );