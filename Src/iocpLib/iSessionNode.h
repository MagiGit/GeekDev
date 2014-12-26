#pragma once
#include <memory>

class iSessionNode
{
private:
    SOCKET  m_socket;

    std::unique_ptr<OVERLAPPED> m_acceptOv;
    std::unique_ptr<OVERLAPPED> m_recvOv;

    
public:
    iSessionNode();
    ~iSessionNode();

    virtual void SendProcess( DWORD bytesTransferred, DWORD errorCode );
    virtual void RecvProcess( DWORD bytesTransferred, DWORD errorCode );
};

