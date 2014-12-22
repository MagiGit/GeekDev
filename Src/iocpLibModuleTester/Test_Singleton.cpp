#include "stdafx.h"

using namespace std;

class cTestSingleton
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
    cSingleTon<cTestSingleton>::Get().value = 200;

    cout << cSingleTon<cTestSingleton>::Get().value << endl;

    cSingleTon<cTestSingleton>::Destroy();

    cout << cSingleTon<cTestSingleton>::Get().value << endl;

    cSingleTon<cTestSingleton>::Destroy();
    cSingleTon<cTestSingleton>::Destroy();
}