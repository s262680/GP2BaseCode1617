#include "Log.h"

Log::Log()
{
  m_CurrentLevel = (unsigned int)(INFO|WARNING|ERROR);
}

Log::~Log()
{

}

void Log::create(const string& filename)
{
  m_FileStream(filename);
  time_t currentTime = time(nullptr);
  m_FileStream<<"Log Created on "<<asctime(currentTime)<<endl;
}

void Log::log(const char* format,...)
{

}

void Log::flush()
{

}

void Log::close()
{

}

void Log::setLogLevel(LogLevel level)
{

}
