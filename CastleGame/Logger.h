//Logger for DirectX game

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <string>

class Logger
{
  public:
    static Logger& GetLogger();
    static Logger& GetLogger(std::string);
    void SetLogfile(std::string);
    void Info(std::string);
    void Error(std::string);
  protected:
    Logger();
    ~Logger(); 
  private: 
    static Logger _Logger;
    std::string _NameLogfile;   //Name of logfile
    std::string _NameModule;    //Name of module
};

#endif