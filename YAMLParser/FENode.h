#pragma once

#include <vector>
#include <string>
#include "yaml-cpp/yaml.h"
#include "GenericFE.h"
#include "Identifiable.h"

class FENode : public Identifiable, GenericFE
{
public:
	FENode(int id, double x, double y, double z, int ix = 0, int iy = 0, int iz = 0, int irx = 0, int iry = 0, int irz = 0, int rotID = 0);
	FENode(YAML::Node yamlnode);
	~FENode();

	Identifiable::Type getType();
	virtual std::string getTypeAsString() override;

	bool assignIndependentAttributes(YAML::Node& yamlNode) override;

	bool setCoordinates(YAML::Node& yamlNode);

	std::vector<std::string> extractYamlKeys(YAML::Node yamlNode);

	void printAttributes();

	//Data fields
	int rotID;
	double x, y, z;
	int ix, iy, iz, irx, iry, irz;
};

