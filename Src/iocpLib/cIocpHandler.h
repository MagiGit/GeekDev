#pragma once

#define IOCP    cSingleTon<cIocpHandler>::Get()

class cIocpHandler
{
private:
    HANDLE m_iocp;

public:
    cIocpHandler();
    ~cIocpHandler();

    bool Create( DWORD threadCount = 0 );
    bool IsCreate() { return m_iocp != NULL; }

    bool RegistHandle( HANDLE handle, ULONG_PTR key );

    // 형변환 귀찮아서 만든 함수...
    template<typename T>
    bool RegistSocket( SOCKET sock, T key )
    {
        return RegistHandle( (HANDLE)sock, (ULONG_PTR)key );
    }

    BOOL GQCS( LPDWORD& bytesTransferred, PULONG_PTR& key, LPOVERLAPPED*& ov, DWORD milliSec = INFINITE )
    {
        return GetQueuedCompletionStatus( m_iocp, bytesTransferred, key, ov, milliSec );
    }
};

