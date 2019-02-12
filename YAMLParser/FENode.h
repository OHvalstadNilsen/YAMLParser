#pragma once

#include <vector>
#include <string>
#include "yaml-cpp/yaml.h"

class FENode
{
public:
	FENode(int id, double x, double y, double z, int ix = 0, int iy = 0, int iz = 0, int irx = 0, int iry = 0, int irz = 0, int rotID = 0);
	FENode(YAML::Node yamlnode);
	~FENode();

	bool setMandatoryValues(YAML::Node yamlNode);

	void setOptionalValues(YAML::Node yamlNode);

	std::vector<std::string> extractYamlKeys(YAML::Node yamlNode);

	void PrintNode();

	int id, rotID;
	double x, y, z;
	int ix, iy, iz, irx, iry, irz;
};

