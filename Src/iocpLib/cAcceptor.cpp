#include "stdafx.h"
#include "cAcceptor.h"
#include "cIocpHandler.h"
#include "iSessionNode.h"
#include <assert.h>


cAcceptor::cAcceptor()
{
}


cAcceptor::~cAcceptor()
{
}

bool cAcceptor::Init( ushort port, int backlog )
{
    if( m_socket.CreateTCP() == false
        || m_socket.Bind( port ) == false )
    {
        return false;
    }

    // listen함수 호출할때 부터 클라이언트는 접속을 시작한다..(backlog만큼)
    // listen다음엔 바로 accept함수를 호출해줘야 한다.
    // AcceptEx에서는 SO_CONDITIONAL_ACCEPT 옵션을 사용하여 accept를 막는다.

    bool on = true;
    if( m_socket.SetOption( SO_CONDITIONAL_ACCEPT, (char*)&on, sizeof(on) ) == false
        || m_socket.Listen( backlog ) == false )
    {
        return false;
    }

    if( g_iocp.RegistSocket( m_socket, this ) == false )
    {
        return false;
    }
  
    return true;
}

bool cAcceptor::AcceptAsync( iSessionNode* session )
{
    if( session == nullptr )
    {
        return false;
    }

    DWORD temp = 0;
    ZeroMemory( session->GetAcceptOv(), sizeof(OVERLAPPED) );

    BOOL ret = AcceptEx( m_socket, 
                         session->GetSocket(), 
                         session->GetBuf(),
                         0,
                         cSocket::addrlen+16,
                         cSocket::addrlen+16,
                         &temp,
                         session->GetAcceptOv() );

    DWORD error = GetLastError();
    if( ret == FALSE 
        && error != ERROR_IO_PENDING )
    {
        return false;
    }

    return true;
}

void cAcceptor::AcceptProcess( iSessionNode* session, DWORD bytesTransferred )
{
    assert( session );
    session->AfterAccept();
    session->RecvAsync();
}

void cAcceptor::AcceptError( iSessionNode* session, DWORD errorCode )
{
    std::cout << "AcceptError!! : " << errorCode << std::endl;
}