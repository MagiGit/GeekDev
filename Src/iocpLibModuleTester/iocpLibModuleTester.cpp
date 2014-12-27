// iocpLibModuleTester.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

void Test_Singleton();
void Test_Thread();

#include "cWSAData.h"
#include "cIocpHandler.h"
#include "iSessionNode.h"
#include "cAcceptor.h"
#include "cWorkThread.h"

int _tmain(int argc, _TCHAR* argv[])
{
    //Test_Singleton();
    //Test_Thread();

    cWSAData ws;
    
    if( g_iocp.Create() == false )
    {
        cout << "IOCP Create() Error!!" << endl;
        return -1;
    }

    cAcceptor acceptor;
    if( acceptor.Init( 30000 ) == false )
    {
        cout << "acceptor Init() Error!!" << endl;
        return -1;
    }

    iSessionNode node;
    if( node.Init( &acceptor ) == false )
    {
        cout << "node Init() Error!!" << endl;
        return -1;
    }

    if( node.AcceptAsync() == false )
    {
        cout << "node AccpetAsync() Error!!" << endl;
        return -1;
    }

    cWorkThread work;
    work.Run();

    work.Wait();

    return 0;
}