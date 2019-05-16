#pragma once
#include "Identifiable.h"
#include "yaml-cpp/yaml.h"
#include "GenericFE.h"

class FEEccentricity :
	public Identifiable,
	public GenericFE
{
public:
	FEEccentricity(YAML::Node& yamlNode);
	FEEccentricity(int id, double eX, double eY, double eZ);
	virtual ~FEEccentricity();

	// Inherited via Identifiable
	Identifiable::Type getType();
	virtual std::string getTypeAsString() override;

	// Inherited via GenericFE
	virtual bool setMandatoryValues(YAML::Node & yamlNode) override;
	virtual void setOptionalValues(YAML::Node & yamlNode) override;
	virtual void printAttributes() override;
	
	double eX, eY, eZ;
};

