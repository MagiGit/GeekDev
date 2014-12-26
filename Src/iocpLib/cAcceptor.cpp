#include "stdafx.h"
#include "cAcceptor.h"
#include "cIocpHandler.h"
#include "iSessionNode.h"


cAcceptor::cAcceptor()
    : m_socket( INVALID_SOCKET )
{
}


cAcceptor::~cAcceptor()
{
}

bool cAcceptor::Init( ushort port, int backlog )
{
    if( IsSocketCreate() != true )
    {
        m_socket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
    }

    if( IsSocketCreate() == false )
    {
        return false;
    }

    SOCKADDR_IN addr;
    ZeroMemory( &addr, sizeof( addr ) );
    addr.sin_family = AF_INET;
    addr.sin_port = htons( port );
    addr.sin_addr.s_addr = INADDR_ANY;
    if( bind( m_socket, (LPSOCKADDR)&addr, sizeof( addr ) ) == SOCKET_ERROR )
    {
        return false;
    }

    // listen함수 호출할때 부터 클라이언트는 접속을 시작한다..(backlog만큼)
    // listen다음엔 바로 accept함수를 호출해줘야 한다.
    if( listen( m_socket, backlog ) == SOCKET_ERROR )
    {
        return false;
    }

    return true;
}

bool AcceptAsync( iSessionNode* session )
{
    return true;
}

void AcceptProcess( iSessionNode* session, DWORD errorCode )
{
}