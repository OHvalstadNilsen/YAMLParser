/** \brief
*	This class defines the thickness for plate/shell elements.
*/
#pragma once
#include "yaml-cpp/yaml.h"
#include "Identifiable.h"
#include "GenericCrossSection.h"

class PLThick :
	public GenericCrossSection
{
public:
	PLThick(YAML::Node& yamlNode);
	~PLThick();
	
	//---------- Functions ----------
	// Inherited via GenericCrossSection
	virtual bool assignIndependentAttributes(YAML::Node & yamlNode) override;
	virtual void printAttributes() override;
	
	//---------- Data fields ----------
	double T;
};

