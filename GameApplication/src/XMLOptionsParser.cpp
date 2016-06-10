#include "XMLOptionsParser.h"
#include "tinyxml.h"

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
  TiXmlDocument doc( m_Filename.c_str());
  if (!doc.LoadFile()) return;

  TiXmlHandle hDoc(&doc);
	TiXmlElement* pCurrentElement;
  TiXmlAttribute* pCurrentAttribute;
  string currentKey;
  string currentValue;

	TiXmlHandle hRoot(0);

  pCurrentElement=hDoc.FirstChildElement().Element();
  if (!pCurrentElement) return;

  //We should always ignore root
  hRoot=TiXmlHandle(pCurrentElement);
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
      currentValue=pCurrentAttribute->ValueStr();

      options.addOption(currentKey,currentValue);
    }
  }
}
