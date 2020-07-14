#ifndef __MYLOG4CPP_H__
#define __MYLOG4CPP_H__


#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string>
#include <iostream>
#include <sstream>
#include <log4cpp/SimpleLayout.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <cstdio>


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::to_string;
using std::stringstream;
using namespace log4cpp;


#define prefix(msg) string(" ").append(__FILE__).append("(").append(std::to_string(__LINE__)).append(")").append("-<").append(__FUNCTION__).append(">: \n").append(msg).c_str()

#define LogError(msg,...) mylog::getInst()->error(prefix(msg),##__VA_ARGS__)
#define LogWarn(msg,...) mylog::getInst()->warn(prefix(msg),##__VA_ARGS__)
#define LogDebug(msg,...) mylog::getInst()->debug(prefix(msg),##__VA_ARGS__)
#define LogInfo(msg,...) mylog::getInst()->info(prefix(msg),##__VA_ARGS__)

class mylog
{
public:


    static mylog *getInst();
    static void destroyInst();

    template <typename... Args>
    void warn(const char *msg, Args... args)
    {
        root.warn(msg,args...);
    }
    template <typename... Args>
    void error(const char *msg, Args... args)
    {
        root.error(msg,args...);
    }
    template <typename... Args>
    void debug(const char *msg, Args... args)
    {
        root.debug(msg,args...);

    }
    template <typename... Args>
    void info(const char *msg, Args... args)
    {
        root.info(msg,args...);
    }
    void warn(const char*msg);
    void error(const char*msg);
    void debug(const char*msg);
    void info(const char*msg);



private:
    class autorelease
    {
    public:
        autorelease()
        {
            // cout << "autorelease()" << endl;
        }
        ~autorelease()
        {
            // cout << "~autorelease()" << endl;
            destroyInst();
        }
    };

private:
    mylog();
    ~mylog();
private:
    static mylog *_pinst;
    Category &root;
    static autorelease ar;
};
#endif // !__MYLOG4CPP_H__
