#ifndef _LOG_H
#define _LOG_H

#include "Common.h"
#include "utils/NonCopyable.h"

enum LogLevel
{
  INFO=1,
  WARNING=2,
  ERROR=3,
}

//enumeration types (both scoped and unscoped) can have overloaded operators
ostream& operator<<(std::ostream& os, LogLevel level)
{
    switch(level)
    {
        case INFO   : os << "INFO";    break;
        case WARNING: os << "WARNING"; break;
        case ERROR : os << "ERROR";  break;
        default    : os.setstate(std::ios_base::failbit);
    }
    return os;
}

class Log:public NonCopyable
{
public:
  ~Log();

  void create(const string& filename);
  void log(const char* format,...);
  void flush();
  void close();
  void setLogLevel(LogLevel level);
private:
  Log();
  unsigned int m_CurrentLevel;
  ofstream m_FileStream;
  queue<string> m_LogMessages;
}

#endif
