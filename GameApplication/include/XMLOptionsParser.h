#ifndef _XML_OPTIONS_PARSER_H
#define _XML_OPTIONS_PARSER_H

#include "Common.h"
#include "OptionParser.h"

class XMLOptionsParser:public OptionParser
{
public:
  XMLOptionsParser(const string& filename);
  ~XMLOptionsParser();

  void parse(ProgramOptions &options);
private:
  string m_Filename;
};

#endif
