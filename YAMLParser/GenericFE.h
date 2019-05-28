/**This is the base class for all finite elements.
* This is the least common multiple for FE classes, used when
* reference to an arbitrary FE type is required.
*
* This class is abstract.
*/
#pragma once
#include "yaml-cpp/yaml.h"

class GenericFE {
	/*Interface defining the minimum content of a 
	* FEM element object.
	*
	* All FEM element objects are based on this interface
	*/
public:
	/**Print attributes to console*/
	virtual void printAttributes() = 0;
	
protected:
	/**Setter for independent (dependency level null) attributes*/
	virtual bool assignIndependentAttributes(YAML::Node& yamlNode) = 0;	
};