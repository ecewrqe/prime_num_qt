#include "valueerror.h"

ValueError::ValueError(const char *_Message, int res)
    :_Errinfo(res), std::runtime_error(_Message)
{

}
ValueError::ValueError(const std::string& _Message, int res)
    :_Errinfo(res), std::runtime_error(_Message)
{

}
int ValueError::returncode(){
    return _Errinfo;
}

NumSmallError::NumSmallError(const char *_Message, int res)
    :_Errinfo(res), std::runtime_error(_Message)
{

}
NumSmallError::NumSmallError(const std::string& _Message, int res)
    :_Errinfo(res), std::runtime_error(_Message)
{

}
int NumSmallError::returncode(){
    return _Errinfo;
}

NumLargeError::NumLargeError(const char *_Message, int res)
    :_Errinfo(res), std::runtime_error(_Message)
{

}
NumLargeError::NumLargeError(const std::string& _Message, int res)
    :_Errinfo(res), std::runtime_error(_Message){

}

int NumLargeError::returncode(){
    return _Errinfo;
}

PrimeCheckedError::PrimeCheckedError(const char *_Message, int res)
    :_Errinfo(res), std::runtime_error(_Message)
{

}
PrimeCheckedError::PrimeCheckedError(const std::string& _Message, int res)
    :_Errinfo(res), std::runtime_error(_Message)
{

}
int PrimeCheckedError::returncode(){
    return _Errinfo;
}

