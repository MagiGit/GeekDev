#pragma once
#include "cThreadBase.h"

class cWorkThread
    : public cThreadBase
{
public:
    cWorkThread();
    ~cWorkThread();

    virtual void Process();
};

