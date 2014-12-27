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

    // ����ȯ �����Ƽ� ���� �Լ�...
    template<typename T>
    bool RegistSocket( SOCKET sock, T key )
    {
        return RegistHandle( (HANDLE)sock, (ULONG_PTR)key );
    }

    BOOL PostEvent( DWORD bytesTransferred, ULONG_PTR key, LPOVERLAPPED ov )
    {
        // ���� ����ó�� �� �� �ִ°� ����.
        // ����ó�� 1. m_iocp�� �׾����� ���
        // ����ó�� 2. �ý��� ���۰� ������ ���̻� queue�� �ȵ� ���...
        return PostQueuedCompletionStatus( m_iocp, bytesTransferred, key, ov );
    }

    BOOL GQCS( DWORD& bytesTransferred, ULONG_PTR& key, LPOVERLAPPED& ov, DWORD milliSec = INFINITE )
    {
        // ���� �� �� �ִ°� ����δ�.
        return GetQueuedCompletionStatus( m_iocp, &bytesTransferred, &key, &ov, milliSec );
    }
};

