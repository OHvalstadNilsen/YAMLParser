/** \brief
*	This is the base class for all section classes (NB: Not to be interchanged with GenericCrossSection).
*
* This is the least common multiple for section classes, used when
* reference to a arbitrary section element is required. 
* Sections are required, inter alia, to define composites.
*
* This class is abstract.
*/
#pragma once
#include "yaml-cpp/yaml.h"
#include "Identifiable.h"
class GenericSection :
	public Identifiable
{
public:
	/**Print attributes to console*/
	virtual void printAttributes() = 0;

protected:
	/**Setter for independent (dependency level null) attributes*/
	virtual bool assignIndependentAttributes(YAML::Node & yamlNode) = 0;
};

