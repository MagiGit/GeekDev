#pragma once
#include <thread>

// 강제종료는 구현하지 않는다.
// thread의 강제 종료시에는 각 객체의 해제(소멸자)를 보장할 수 없다. 
// 즉 자원이 날아가는 경우가 생긴다.( ex. 메모리누수 )
class cThreadBase
{
private:
    std::thread m_thread;

public:
    cThreadBase();
    ~cThreadBase();

    void Run();
    void Wait();
    // 쓰레드 관리 해제
    // 만들어 놓고 끝나든 말든 신경쓰지 않을때...( 필요가 있으려나;;; )
    void Detach();

    virtual void Process() = 0;
};

