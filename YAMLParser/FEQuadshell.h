#pragma once
#include "GenericFE.h"
#include "yaml-cpp/yaml.h"
#include "Identifiable.h"

class FEQuadshell : public Identifiable, public GenericFE
{
public:
	FEQuadshell(YAML::Node& yamlNode);
	~FEQuadshell();
	virtual std::string getTypeAsString() override;

	bool setMandatoryValues(YAML::Node& yamlNode);
	void setOptionalValues(YAML::Node& yamlNode);
	bool setNodes(YAML::Node & yamlNode);
	void printAttributes();

	int node1, node2, node3, node4, material, geoID;
	int coordID, ecc1, ecc2, ecc3, ecc4;
};

