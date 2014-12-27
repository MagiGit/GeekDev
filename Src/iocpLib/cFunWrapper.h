#pragma once
#include <functional>

class cFunWrapper
{
public:
    virtual void Process( DWORD bytesTransferred ) { };
    virtual void Error( DWORD errorCode ) { };
};

template< typename T>
class cOVCallBackFunDefault
    : public cFunWrapper
{
private:
    typedef void (T::*FUNTYPE)(DWORD);
    
    T*      m_obj;
    FUNTYPE m_processFun;
    FUNTYPE m_errorFun;

public:
    cOVCallBackFunDefault( T* obj, FUNTYPE processFun, FUNTYPE errorFun)
        : m_obj(obj), m_processFun(processFun), m_errorFun(errorFun)
    {
    }

    virtual void Process( DWORD bytesTransferred )
    {
        (m_obj->*m_processFun)( bytesTransferred );
    }

    virtual void Error( DWORD errorCode )
    {
        (m_obj->*m_errorFun)( errorCode );
    }
};

template< typename T, typename ArgType >
class cOVCallBackFunArgs
    : public cFunWrapper
{
private:
    typedef void (T::*FUNTYPE)( ArgType, DWORD );

    T*          m_obj;
    ArgType     m_arg;
    FUNTYPE     m_processFun;
    FUNTYPE     m_errorFun;

public:
    cOVCallBackFunArgs( T* obj, ArgType arg, FUNTYPE processFun, FUNTYPE errorFun )
        : m_obj(obj), m_arg(arg), m_processFun(processFun), m_errorFun(errorFun)
    {
    }

    virtual void Process( DWORD bytesTransferred )
    {
        (m_obj->*m_processFun)( m_arg, bytesTransferred );
    }
    
    virtual void Error( DWORD errorCode )
    {
        (m_obj->*m_errorFun)( m_arg, errorCode );
    }
};

template<typename T>
inline cOVCallBackFunDefault<T>* make_funWrapper( T* obj, void (T::*processFun)(DWORD), void (T::*errorFun)(DWORD) )
{
    return new cOVCallBackFunDefault<T>( obj, processFun, errorFun );
}

template<typename T, typename ArgType>
inline cOVCallBackFunArgs<T, ArgType>* make_funWrapper( T* obj, 
                                                      ArgType arg, 
                                                      void (T::*processFun)(ArgType, DWORD),
                                                      void (T::*errorFun)(ArgType, DWORD) )
{
    return new cOVCallBackFunArgs<T, ArgType>( obj, arg, processFun, errorFun );
}