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
	bool assignIndependentAttributes(YAML::Node& yamlNode) override;
	void printAttributes();

	//Data fields
	std::string type;
	double Emod, poisson, yield, density, thermX;
};

