#include "XMLOptionsParser.h"
#include "tinyxml2.h"

using namespace tinyxml2;

XMLOptionsParser::XMLOptionsParser(const string& filename)
{
  m_Filename=filename;
}

XMLOptionsParser::~XMLOptionsParser()
{

}

void XMLOptionsParser::parse(ProgramOptions &options)
{
  //parse xml file, keep element name and combine with attribute name for key
  //value comes from atrribute value
	XMLDocument doc;
  if (!doc.LoadFile(m_Filename.c_str())) return;

  XMLHandle hDoc(&doc);
  XMLElement* pCurrentElement;
  const XMLAttribute* pCurrentAttribute;
  string currentKey;
  string currentValue;
  XMLHandle hRoot(0);

  pCurrentElement = hDoc.FirstChildElement().ToElement();
  if (!pCurrentElement) return;

  //We should always ignore root
  hRoot=XMLHandle(pCurrentElement);
  //iterate through all elements
  for( pCurrentElement = pCurrentElement->FirstChildElement(); pCurrentElement;
    pCurrentElement = pCurrentElement->NextSiblingElement() )
  {
    //add all attributes
    for (pCurrentAttribute=pCurrentElement->FirstAttribute();pCurrentAttribute;
      pCurrentAttribute=pCurrentAttribute->Next())
    {
      currentKey.clear();
      currentValue.clear();
      currentKey=string(string(pCurrentElement->Value())+string(pCurrentAttribute->Name()));
	  currentValue = pCurrentAttribute->Value();

      options.addOption(currentKey,currentValue);
    }
  }
}
