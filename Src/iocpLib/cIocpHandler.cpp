#include "stdafx.h"
#include "cIocpHandler.h"


cIocpHandler::cIocpHandler()
    : m_iocp(NULL)
{
}


cIocpHandler::~cIocpHandler()
{
}

bool cIocpHandler::Create( DWORD threadCount )
{
    if( IsCreate() == true )
    {
        return true;
    }

    m_iocp = CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, NULL, threadCount );

#ifdef _DEBUG
    // �̶� �����ϸ�...�� ���� �ؾ����� �𸣰���
    // ������϶� �޽����� �������...;
    if( IsCreate() == false )
    {
        TCHAR msg[_MAX_FNAME] = {0};
        StringCchPrintf( msg, _MAX_FNAME, TEXT("iocpHandler Create Error : %d"), GetLastError() );
        
        MessageBox( NULL, msg, TEXT("cIocpHandler::Create"), MB_OK );
    }
#endif
    return IsCreate();
}

bool cIocpHandler::RegistHandle( HANDLE handle, ULONG_PTR key )
{
    if( IsCreate() == false )
    {
        return false;
    }

    HANDLE hRet = CreateIoCompletionPort( handle, m_iocp, key, 0 );
    if( hRet == NULL )
    {
        DWORD errorCode = GetLastError();

        // �� ����ó��( ���� ���� )
        // �̹� ��ϵ� �ڵ��� ���� ����

        return false;
    }

    return true;
}