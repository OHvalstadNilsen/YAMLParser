#pragma once
#include "GenericFE.h"
#include "yaml-cpp/yaml.h"

class FEQuadshell : public GenericFE
{
public:
	FEQuadshell(YAML::Node& yamlNode);
	~FEQuadshell();
	bool setMandatoryValues(YAML::Node& yamlNode);
	void setOptionalValues(YAML::Node& yamlNode);
	bool setNodes(YAML::Node & yamlNode);
	void printAttributes();

	int id, node1, node2, node3, node4, material, geoID;
	int coordID, ecc1, ecc2, ecc3, ecc4;
};

