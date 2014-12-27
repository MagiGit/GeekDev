#pragma once
class cSocket
{
public:
    static const int addrlen = sizeof(SOCKADDR);

private:
    SOCKET  m_socket;

public:
    cSocket( SOCKET sock = INVALID_SOCKET );
    ~cSocket();

    operator SOCKET() { return m_socket; }

    bool CreateTCP();
    bool CreateUDP();
    bool IsCreate() { return m_socket != INVALID_SOCKET; }

    bool Bind( ushort port );
    bool Bind( char* ip, ushort port );
    bool Bind( SOCKADDR_IN& addr );

    bool Listen( int backlog = SOMAXCONN );

    void Shutdown( int how = SD_BOTH );
    void Close();

    bool SetOption( int optname, const char* optval, int optlen )
    { 
        // level(SOL_SOCKET)을 매개변수로 빼는게 좋을 수도 있지만
        // 여기에서는 SOL_SOCKET말고는 안쓴다.
        return setsockopt( m_socket, SOL_SOCKET, optname, optval, optlen ) != SOCKET_ERROR; 
    }

    int SendAsync( LPWSABUF wBuf, LPOVERLAPPED ov, DWORD& dwSentLen )
    {
        return WSASend( m_socket, wBuf, 1, &dwSentLen, 0, ov, NULL );
    }

    int RecvAsync( LPWSABUF wBuf, LPOVERLAPPED ov, DWORD& dwRecvLen, DWORD&& flag = 0 )
    {
        return WSARecv( m_socket, wBuf, 1, &dwRecvLen, &flag, ov, NULL );
    }
};

