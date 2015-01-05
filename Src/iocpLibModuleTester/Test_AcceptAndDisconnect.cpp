#include "stdafx.h"
#include <iostream>
using namespace std;

#include "cWSAData.h"
#include "cIocpHandler.h"
#include "iSessionNode.h"
#include "cAcceptor.h"
#include "cWorkThread.h"

void Test_AcceptAndDisconnect()
{
    cWSAData ws;
    
    if( g_iocp.Create() == false )
    {
        cout << "IOCP Create() Error!!" << endl;
        return ;
    }

    cAcceptor acceptor;
    if( acceptor.Init( 30000 ) == false )
    {
        cout << "acceptor Init() Error!!" << endl;
        return ;
    }

    iSessionNode node;
    if( node.Init( &acceptor ) == false )
    {
        cout << "node Init() Error!!" << endl;
        return ;
    }

    if( node.AcceptAsync() == false )
    {
        cout << "node AccpetAsync() Error!!" << endl;
        return ;
    }

    cWorkThread work;
    work.Run();

    work.Wait();
}