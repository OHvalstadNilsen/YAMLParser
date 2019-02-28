#pragma once

#include "yaml-cpp/yaml.h"
#include "GenericFE.h"

class FEBeam : GenericFE
{
public:
	FEBeam(YAML::Node yamlNode);
	~FEBeam();

	bool setMandatoryValues(YAML::Node& yamlNode);
	void setOptionalValues(YAML::Node& yamlNode);
	bool setNodes(YAML::Node yamlNode);
	void printAttributes();

	int id, node1, node2, material, geoID, vecID, eccentricity1, eccentricity2;
};

