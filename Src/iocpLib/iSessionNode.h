#pragma once
#include <memory>
#include "cSocket.h"

class cAcceptor;

class iSessionNode
{
private:
    cSocket                     m_socket;

    cAcceptor*                  m_acceptor;

    std::unique_ptr<OVERLAPPED> m_acceptOv;
    std::unique_ptr<OVERLAPPED> m_recvOv;
    std::unique_ptr<OVERLAPPED> m_disconnectOv;

    bool                        m_regist;

public:
    iSessionNode();
    virtual ~iSessionNode();

    bool Init( cAcceptor* acceptor );
    
    bool AcceptAsync();
    void AfterAccept();
    bool RecvAsync();

    virtual void SendProcess( DWORD bytesTransferred ) { }
    virtual void SendError( DWORD erorrCode ) { }

    void _RecvProcess( DWORD bytesTransferred );
    virtual void RecvProcess( DWORD bytesTransferred ) { }
    virtual void RecvError( DWORD errorCode ) { }
    
    void CloseSession();
    void DisconnectProcess( DWORD bytesTransferred );
    void DisconnectError( DWORD errorCode );

    SOCKET GetSocket() { return (SOCKET)m_socket; }
    LPOVERLAPPED GetAcceptOv() { return m_acceptOv.get(); }

    // юс╫ц
    WSABUF  m_wBuf;
    char    m_recvBuffer[4096];
    DWORD   m_recvFlag;
    char*   GetBuf() { return m_recvBuffer; }
};

