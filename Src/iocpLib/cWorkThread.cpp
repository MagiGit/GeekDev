#include "stdafx.h"
#include "cWorkThread.h"
#include "cIocpHandler.h"
#include "cOverlappedEx.h"


cWorkThread::cWorkThread()
{
}


cWorkThread::~cWorkThread()
{
}

void cWorkThread::Process()
{
    DWORD bytesTransferred = 0;
    ULONG_PTR key = 0;
    LPOVERLAPPED ov = nullptr;

    while( true )
    {
        BOOL ret = g_iocp.GQCS( bytesTransferred, key, ov );

        DWORD errorCode = GetLastError();
        cOverlappedEx* ovEx = static_cast<cOverlappedEx*>(ov);
        if( ovEx == nullptr )
        {
            break;
        }

        if( ret == TRUE )
        {
            ovEx->Process( bytesTransferred );
        }
        else
        {
            ovEx->Error( errorCode );
        }
    }
}
