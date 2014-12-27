#pragma once

#define g_iocp    cSingleTon<cIocpHandler>::Get()

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

    BOOL PostEvent( DWORD bytesTransferred, ULONG_PTR key, LPOVERLAPPED ov )
    {
        // 딱히 에러처리 할 수 있는게 없다.
        // 에러처리 1. m_iocp가 죽어있을 경우
        // 에러처리 2. 시스템 버퍼가 꽉차서 더이상 queue가 안될 경우...
        return PostQueuedCompletionStatus( m_iocp, bytesTransferred, key, ov );
    }

    BOOL GQCS( DWORD& bytesTransferred, ULONG_PTR& key, LPOVERLAPPED& ov, DWORD milliSec = INFINITE )
    {
        // 역시 할 수 있는게 없어보인다.
        return GetQueuedCompletionStatus( m_iocp, &bytesTransferred, &key, &ov, milliSec );
    }
};

