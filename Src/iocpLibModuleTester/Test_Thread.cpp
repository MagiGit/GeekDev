#include "stdafx.h"
#include "cThreadBase.h"
using namespace std;

class cTestThreadA : public cThreadBase
{
private:
    int m_value;
public:
    cTestThreadA( int v ) : m_value(v) {}

    void Process()
    {
        for( int i = 0 ; i < 10 ; i++ )
        {
            cout << std::this_thread::get_id() << " : a : " << i << " : " << m_value << endl;
        }
    }
};

class cTestThreadB : public cThreadBase
{
private:
    int m_value;
public:
    cTestThreadB( int v ) : m_value(v) {}

    void Process()
    {
        for( int i = 0 ; i < 5 ; i++ )
        {
            cout << std::this_thread::get_id() << " : b : " << i << " : " << m_value << endl;
        }
    }
};



void Test_Thread()
{
    cTestThreadA a(50);
    cTestThreadB b(30);
    
    a.Run();
    a.Run();
    b.Run();
    a.Wait();
    // �����尡 ������ �ٽ� ���� �� �ִ�?....���ƾ��ϳ�?...�ϴ� ����
    a.Run();
}