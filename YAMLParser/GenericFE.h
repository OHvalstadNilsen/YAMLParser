#pragma once
#include "yaml-cpp/yaml.h"

class GenericFE {
	/*Interface defining the minimum content of a 
	* FEM element object.
	*
	* All FEM element objects are based on this interface
	*/
public:
	//Console print for debugging:
	virtual void printAttributes() = 0;
	
protected:
	//Setters for attrubute values:
	virtual bool assignIndependentAttributes(YAML::Node& yamlNode) = 0;
	//virtual void setOptionalValues(YAML::Node& yamlNode) = 0;
	
};