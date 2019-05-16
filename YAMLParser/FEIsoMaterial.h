#pragma once
#include <string>
#include "yaml-cpp/yaml.h"
#include "GenericFE.h"
#include "Identifiable.h"

class FEIsoMaterial : public Identifiable, public GenericFE
{
public:
	FEIsoMaterial(YAML::Node& yamlNode);
	FEIsoMaterial(int id, std::string type, double Emod, double poiss, double density, double thermX);
	~FEIsoMaterial();

	virtual std::string getTypeAsString() override;
	bool setMandatoryValues(YAML::Node& yamlNode);
	void setOptionalValues(YAML::Node& yamlNode);
	void printAttributes();

	std::string type;
	double Emod, poisson, yield, density, thermX;
};

