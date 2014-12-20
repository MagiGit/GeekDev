#include "stdafx.h"

using namespace std;

class cTestSingleton
    : public cSingleTon<cTestSingleton>
{
public:
    int value;

    cTestSingleton()
        : value(100)
    {
        cout << "cTestSingleton()" << endl;
    }

    ~cTestSingleton()
    {
        cout << "~cTestSingleton()" << endl;
    }

    void Print() const
    {
        cout << value << endl;
    }
};

void Test_Singleton()
{
    cTestSingleton::Get().value = 200;

    cout << cTestSingleton::Get().value << endl;

    cTestSingleton::Destroy();

    cout << cTestSingleton::Get().value << endl;

    cTestSingleton::Destroy();
    cTestSingleton::Destroy();
}