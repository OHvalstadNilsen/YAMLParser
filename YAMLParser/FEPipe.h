#pragma once

#include "GenericCrossSection.h"
#include "GenericFE.h"
#include "yaml-cpp/yaml.h"
class FEPipe :
	public GenericCrossSection,
	public GenericFE
{
public:
	FEPipe(YAML::Node yamlNode);
	virtual ~FEPipe();

	//Inherited via Identifiable
	virtual Identifiable::Type getType() override;
	virtual std::string getTypeAsString() override;

	// Inherited via GenericFE
	virtual void printAttributes() override;
	virtual bool setMandatoryValues(YAML::Node & yamlNode) override;
	virtual void setOptionalValues(YAML::Node & yamlNode) override;
	
	double outerDiameter, thickness, shearY, shearZ;
};

