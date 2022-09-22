#include <exception>
/**
 * prime number exception classes
 *
 * @author			euewrqe
 * @version        v1.1
 *
 */

#include<stdexcept>
#include<string>
#ifndef VALUEERROR_H
#define VALUEERROR_H


class ValueError : public std::runtime_error
{
public:
    ValueError(const char *_Message, int res=1);
    ValueError(const std::string& _Message, int res=1);
    int returncode();
private:
    int _Errinfo;
};

class NumSmallError : public std::runtime_error
{
public:
    NumSmallError(const char *_Message, int res=1);
    NumSmallError(const std::string& _Message, int res=1);
    int returncode();
private:
    int _Errinfo;
};

class PrimeCheckedError : public std::runtime_error
{
public:
    PrimeCheckedError(const char *_Message, int res=1);
    PrimeCheckedError(const std::string& _Message, int res=1);
    int returncode();
private:
    int _Errinfo;
};

#endif // VALUEERROR_H
