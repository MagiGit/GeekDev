#include "stdafx.h"
#include "cWSAData.h"
#include <assert.h>

int cWSAData::s_refCount = 0;

cWSAData::cWSAData()
{
    if( s_refCount == 0 )
    {
        WSADATA ws;
        if( WSAStartup( MAKEWORD(2, 2), &ws ) != 0 )
        {
            // ���⼭ �����ϸ� ���α׷��� ����� �ǹ̰� ����.
            assert( false && "WSAStartup() error!!" );
            exit(-1);
        }
    }

    ++s_refCount;
}


cWSAData::~cWSAData()
{
    --s_refCount;

    if( s_refCount == 0 )
    {
        if( WSACleanup() == SOCKET_ERROR )
        {
            assert( false && "WSACleanup() error!!" );
            exit(-1);
        }
    }
}
