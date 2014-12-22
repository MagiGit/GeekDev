#include "stdafx.h"
#include "cThreadBase.h"

cThreadBase::cThreadBase()
{
}


cThreadBase::~cThreadBase()
{
    Wait();
}

void cThreadBase::Run()
{
    if( m_thread.joinable() == false )
    {
        m_thread = std::move( std::thread( &cThreadBase::Process, this ) );
    }
}

void cThreadBase::Wait()
{
    if( m_thread.joinable() == true )
    {
        m_thread.join();
    }
}

void cThreadBase::Detach()
{
    if( m_thread.joinable() == true )
    {
        m_thread.detach();
    }
}
