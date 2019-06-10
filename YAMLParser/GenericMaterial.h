/** \brief
*	This is the base class for all materials classes.
*
* This is the least common multiple for material classes, 
* used when reference to an arbitrary FE type is required.
*
* This class is abstract.
*/
#pragma once
#include "yaml-cpp/yaml.h"
#include "Identifiable.h"

class GenericMaterial :
	public Identifiable
{
public:
	/**Print attributes to console*/
	virtual void printAttributes() = 0;

protected:
	/**Setter for independent (dependency level null) attributes*/
	virtual bool assignIndependentAttributes(YAML::Node& yamlNode) = 0;
};

