/** \brief
*	This class is a dummy for cross-section, used when no cross-section is specified in the input file.
*/

#pragma once
#include "GenericCrossSection.h"
class CrossSectionDummy :
	public GenericCrossSection
{
public:
	CrossSectionDummy();
	~CrossSectionDummy();

	//---------- Functions ----------
	Identifiable::Type getType();
	std::string getTypeAsString();

	// Inherited via GenericCrossSection
	virtual bool assignIndependentAttributes(YAML::Node & yamlNode) override;
	virtual void printAttributes() override;
};

