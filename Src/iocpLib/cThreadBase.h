#pragma once
#include <thread>

// ��������� �������� �ʴ´�.
// thread�� ���� ����ÿ��� �� ��ü�� ����(�Ҹ���)�� ������ �� ����. 
// �� �ڿ��� ���ư��� ��찡 �����.( ex. �޸𸮴��� )
class cThreadBase
{
private:
    std::thread m_thread;

public:
    cThreadBase();
    ~cThreadBase();

    void Run();
    void Wait();
    // ������ ���� ����
    // ����� ���� ������ ���� �Ű澲�� ������...( �ʿ䰡 ��������;;; )
    void Detach();

    virtual void Process() = 0;
};

