/** \brief
*	This is the base class for all cross-section classes.
*
* This is the least common multiple for cross-section classes, used when
* reference to a arbitrary cross-section element is required.
*/
#pragma once
#include "yaml-cpp/yaml.h"
#include "Identifiable.h"

class GenericCrossSection :
	public Identifiable
{
public:
	GenericCrossSection();
	GenericCrossSection(int id);
	~GenericCrossSection();
	virtual void printAttributes() = 0;

protected:
	virtual bool assignIndependentAttributes(YAML::Node & yamlNode) = 0;
};

