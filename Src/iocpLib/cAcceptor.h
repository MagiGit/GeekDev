#pragma once
#include "cSocket.h"

class iSessionNode;

class cAcceptor
{
private:
    cSocket m_socket;

public:
    cAcceptor();
    ~cAcceptor();

    bool Init( ushort port, int backlog = SOMAXCONN );

    bool AcceptAsync( iSessionNode* session );
    void AcceptProcess( iSessionNode* session, DWORD bytesTransferred );
    void AcceptError( iSessionNode* session, DWORD errorCode );

    SOCKET GetSock() { return (SOCKET)m_socket; }
};

