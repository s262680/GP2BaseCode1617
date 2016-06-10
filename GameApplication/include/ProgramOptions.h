#ifndef _PROGRAM_OPTIONS_H
#define _PROGRAM_OPTIONS_H

#include "Common.h"

class ProgramOptions
{
public:
  ProgramOptions();
  ~ProgramOptions();

  void addOption(const string& name, const string& value);
  const string& getOption(const string& name);
  float getOptionAsFloat(const string& name);
  int getOptionAsInt(const string& name);
  bool getOptionAsBool(const string& name);
private:
  map<string,string> m_Options;
};
#endif
