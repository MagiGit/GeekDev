#include "stdafx.h"
#include "cSocket.h"
#include <WS2tcpip.h>


cSocket::cSocket( SOCKET sock )
    : m_socket(sock)
{
}


cSocket::~cSocket()
{
}

bool cSocket::CreateTCP()
{
    if( IsCreate() == false )
    {
        m_socket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
    }

    return IsCreate();
}

bool cSocket::CreateUDP()
{
    if( IsCreate() == false )
    {
        m_socket = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
    }

    return IsCreate();
}

bool cSocket::Bind( ushort port )
{
    SOCKADDR_IN addr;
    ZeroMemory( &addr, addrlen );
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons( port );

    return Bind( addr );
}

bool cSocket::Bind( char* ip, ushort port )
{
    SOCKADDR_IN addr;
    ZeroMemory( &addr, addrlen );
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &addr.sin_addr);
    addr.sin_port = htons( port );

    return Bind( addr );
}

bool cSocket::Bind( SOCKADDR_IN& addr )
{
    if( IsCreate() == false )
    {
        return false;
    }

    if( bind( m_socket, (SOCKADDR*)&addr, addrlen ) == SOCKET_ERROR )
    {
        return false;
    }

    return true;
}

bool cSocket::Listen( int backlog )
{
    if( IsCreate() == false )
    {
        return false;
    }

    if( listen( m_socket, backlog ) == SOCKET_ERROR )
    {
        return false;
    }

    return true;
}

void cSocket::Shutdown( int how )
{
    if( shutdown( m_socket, how ) == SOCKET_ERROR )
    {
        DWORD err = GetLastError();

        std::cout << "shutdown() Error!! : " << err << std::endl;
    }
}

void cSocket::Close()
{
    if( closesocket( m_socket ) == SOCKET_ERROR )
    {
        DWORD err = GetLastError();

        std::cout << "closesocket() Error!! : " << err << std::endl;
    }

    m_socket = INVALID_SOCKET;
}