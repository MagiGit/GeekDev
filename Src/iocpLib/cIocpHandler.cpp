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
    // 이때 실패하면...뭔 짓을 해야할지 모르겠음
    // 디버그일때 메시지만 띄워보자...;
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

        // 각 에러처리( 추후 구현 )
        // 이미 등록된 핸들은 성공 리턴

        return false;
    }

    return true;
}