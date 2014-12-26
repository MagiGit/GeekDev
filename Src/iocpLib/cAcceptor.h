#pragma once

class iSessionNode;

class cAcceptor
{
private:
    SOCKET  m_socket;

public:
    cAcceptor();
    ~cAcceptor();

    bool Init( ushort port, int backlog = SOMAXCONN );

    bool AcceptAsync( iSessionNode* session );
    void AcceptProcess( iSessionNode* session, DWORD errorCode );

    bool IsSocketCreate() { return m_socket == INVALID_SOCKET; }
};

