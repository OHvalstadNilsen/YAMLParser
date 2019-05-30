/** \brief
*	This is the base class for all cross-section classes.
*
* This is the least common multiple for cross-section classes, used when
* reference to a arbitrary cross-section element is required.
*
* This class is abstract.
*/
#pragma once
#include "yaml-cpp/yaml.h"
#include "Identifiable.h"

class GenericCrossSection :
	public Identifiable
{
public:
	/**Print attributes to console*/
	virtual void printAttributes() = 0;

protected:
	/**Setter for independent (dependency level null) attributes*/
	virtual bool assignIndependentAttributes(YAML::Node & yamlNode) = 0;
};

