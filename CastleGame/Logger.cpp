#include "Logger.h"
#include <fstream>

using namespace std;

Logger Logger::_Logger;

Logger& Logger::GetLogger()
{
    _Logger._NameModule = "";
    return _Logger;
}

Logger& Logger::GetLogger(string nameModule)
{
    _Logger._NameModule = nameModule;
    return _Logger;
}

void Logger::SetLogfile(string NameLogfile)
{
    _Logger._NameLogfile = NameLogfile;
    return;
}

void Logger::Info(string message)
{
    fstream fLog(_NameLogfile.c_str(), ios::out | ios::app);
    fLog<<"--------------------"<<_NameModule<<"--------------------"<<endl;
    fLog<<"Info : "<<message<<endl<<endl;
    fLog.close();
    return;
}

void Logger::Error(string message)
{
    fstream fLog(_NameLogfile.c_str(), ios::out | ios::app);
    fLog<<"--------------------"<<_NameModule<<"--------------------"<<endl;
    fLog<<"Error : "<<message<<endl<<endl;
    fLog.close();
    return;
}

Logger::Logger() : _NameLogfile("LogGame.txt") { }

Logger::~Logger() { }

