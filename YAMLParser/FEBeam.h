#pragma once

#include "yaml-cpp/yaml.h"

class FEBeam
{
public:
	FEBeam(YAML::Node yamlNode);
	~FEBeam();

	bool setMandatoryValues(YAML::Node yamlNode);
	void setOptionalValues(YAML::Node yamlNode);
	void PrintBeam();

	int id, node1, node2, material, geoID, vecID, eccentricity1, eccentricity2;
};

