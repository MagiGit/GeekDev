#pragma once
#include "cFunWrapper.h"

class cOverlappedEx
    : public OVERLAPPED
{
private:
    cFunWrapper*    m_fun;

public:
    cOverlappedEx();
    ~cOverlappedEx();

    void ClearOV()
    {
        ZeroMemory( static_cast<LPOVERLAPPED>(this), sizeof(OVERLAPPED) );
    }

    void SetFun( cFunWrapper* fun )
    {
        m_fun = fun;
    }

    void Process( DWORD bytesTransferred )
    {
        if( m_fun == nullptr )
        {
            return ;
        }

        m_fun->Process( bytesTransferred );
    }

    void Error( DWORD errorCode )
    {
        if( m_fun == nullptr )
        {
            return ;
        }

        m_fun->Error( errorCode );
    }
};

