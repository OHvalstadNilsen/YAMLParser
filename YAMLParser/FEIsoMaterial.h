#pragma once
#include <string>
#include "yaml-cpp/yaml.h"
#include "GenericFE.h"

class FEIsoMaterial : public GenericFE
{
public:
	FEIsoMaterial(YAML::Node& yamlNode);
	~FEIsoMaterial();

	bool setMandatoryValues(YAML::Node& yamlNode);
	void setOptionalValues(YAML::Node& yamlNode);
	void printAttributes();

	int id;
	std::string type;
	double Emod, poisson, yield, density, thermX;
};

