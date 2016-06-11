#ifndef _LOG_H
#define _LOG_H

#include "Common.h"
#include "utils/NonCopyable.h"

#define LOG(level,format,...) Log::get().write(level,format,__VA_ARGS__)
#define CREATELOG(name) Log::get().create(name)
#define CLOSELOG() Log::get().close()
#define FLUSHLOG() Log::get().flush()

enum LogLevel
{
  INFO=0,
  WARNING=1,
  ERROR=2,
};

class Log:public NonCopyable
{
public:
  ~Log();

  void create(const string& filename);
  void write(unsigned int level,const char* format, ...);
  void flush();
  void close();
  void setLogLevel(unsigned int level);

  static Log& get(){
    static Log instance;
    return instance;
  };

private:
  Log();
  unsigned int m_CurrentLevel;
  ofstream m_FileStream;
  queue<string> m_LogMessages;
  int m_MessageBufferSize;
};

#endif
