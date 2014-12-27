#include "stdafx.h"
#include "iSessionNode.h"
#include "cAcceptor.h"
#include "cOverlappedEx.h"
#include "cIocpHandler.h"

#include <iostream>
using namespace std;

iSessionNode::iSessionNode()
    : m_acceptor(nullptr), m_acceptOv(new cOverlappedEx), m_recvOv(new cOverlappedEx), m_disconnectOv(new cOverlappedEx), m_regist(false)
{
    ZeroMemory( &m_wBuf, sizeof(m_wBuf) );
    ZeroMemory( m_recvBuffer, sizeof(m_recvBuffer) );
    m_recvFlag = 0;
}

iSessionNode::~iSessionNode()
{
    
}

bool iSessionNode::Init( cAcceptor* acceptor )
{
    //if( m_socket.CreateTCP() == false )
    //{
    //    return false;
    //}
    m_socket.CreateTCP();
    m_acceptor = acceptor;

    static_cast<cOverlappedEx*>(m_acceptOv.get())->SetFun( make_funWrapper( m_acceptor, this, &cAcceptor::AcceptProcess, &cAcceptor::AcceptError ) );
    static_cast<cOverlappedEx*>(m_recvOv.get())->SetFun( make_funWrapper( this, &iSessionNode::_RecvProcess, &iSessionNode::RecvError ) );
    static_cast<cOverlappedEx*>(m_disconnectOv.get())->SetFun( make_funWrapper(this, &iSessionNode::DisconnectProcess, &iSessionNode::DisconnectError ) );

    return true;
}

void iSessionNode::_RecvProcess( DWORD bytesTransferred )
{
    if( bytesTransferred == 0 )
    {
        CloseSession();
        return ;
    }
    
    RecvProcess( bytesTransferred );
}

bool iSessionNode::AcceptAsync()
{
    if( m_acceptor == nullptr )
    {
        return false;
    }

    return m_acceptor->AcceptAsync( this );
}

void iSessionNode::AfterAccept()
{
    if( m_regist == false )
    {
        if( g_iocp.RegistSocket( m_socket, this ) == false )
        {
            DWORD error = GetLastError();
            cout << "RegistSocket() Error!! : " << error << endl;
            return ;
        }

        m_regist = true;
    }

    // listen socket의 QOS설정을 물려 받는다는데 무슨 말이지...
    // 한번만 해 줘야 하는건지...매번 해줘야하는건지...
    SOCKET listenSocket = m_acceptor->GetSock();
    if( m_socket.SetOption( SO_UPDATE_ACCEPT_CONTEXT, (const char*)&listenSocket, sizeof(SOCKET) ) == false )
    {
        DWORD err = GetLastError();
        cout << "SetOption(SO_UPDATE_ACCEPT_CONTEXT) Error!!" << endl;
        return ;
    }
}

bool iSessionNode::RecvAsync()
{
    m_wBuf.len = 4096;
    m_wBuf.buf = m_recvBuffer;
    
    DWORD bytesRecvd = 0;
    ZeroMemory( m_recvOv.get(), sizeof(OVERLAPPED) );

    int len = m_socket.RecvAsync( &m_wBuf, m_recvOv.get(), bytesRecvd, std::move( m_recvFlag ) );
    
    DWORD error = GetLastError();
    if( len == SOCKET_ERROR
        && error != ERROR_IO_PENDING )
    {
        cout << "RecvAsync() Error!! : " << error << endl;
        CloseSession();
        return false;
    }

    return true;
}

void iSessionNode::CloseSession()
{
    LINGER li;
    li.l_onoff = 1;
    li.l_linger = 0;

    if( m_socket.SetOption( SO_LINGER, (const char*)&li, sizeof(li) ) == false )
    {
        DWORD err = GetLastError();
        cout << "SetOption(SO_LINGER) Error!! : " << err << endl;
        return ;
    }

    m_socket.Shutdown();

    ZeroMemory( m_disconnectOv.get(), sizeof(OVERLAPPED) );
    TransmitFile( m_socket, NULL, NULL, NULL, m_disconnectOv.get(), NULL, TF_DISCONNECT | TF_REUSE_SOCKET );
}

void iSessionNode::DisconnectProcess( DWORD bytesTransferred )
{
    AcceptAsync();
}

void iSessionNode::DisconnectError( DWORD errorCode )
{
    m_socket.Close();

    m_socket.CreateTCP();
    m_regist = false;
}