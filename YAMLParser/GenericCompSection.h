/** \brief
*	This is the base class for all composite section classes (NB: Not to be interchanged with GenericCrossSection).
*
* This is the least common multiple for composite section classes, used when
* reference to a arbitrary composite section element is required. 
*
* This class is abstract.
*/
#pragma once
#include "yaml-cpp/yaml.h"
#include "Identifiable.h"
class GenericCompSection :
	public Identifiable
{
public:
	/**Print attributes to console*/
	virtual void printAttributes() = 0;

protected:
	/**Setter for independent (dependency level null) attributes*/
	virtual bool assignIndependentAttributes(YAML::Node & yamlNode) = 0;
};

