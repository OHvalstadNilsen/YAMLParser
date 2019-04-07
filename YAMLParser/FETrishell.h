#pragma once

#include "yaml-cpp/yaml.h"
#include "GenericFE.h"
#include "Identifiable.h"

class FETrishell : public Identifiable, GenericFE
{
public:
	FETrishell(YAML::Node yamlNode);
	~FETrishell();
	
	virtual std::string getTypeAsString() override;

	bool setNodes(YAML::Node yamlNode);
	void setOptionalValues(YAML::Node& yamlNode);
	bool setMandatoryValues(YAML::Node& yamlNode);
	void printAttributes();

	int node1, node2, node3, material, geoID, coordID;
	int eccentricity1, eccentricity2, eccentricity3;
	
	/*TODO: Implement with instances of FE classes, as shown beneath:

	FENode node1, node2, node3;
	FEMaterial material;
	FEEccentricity eccentricity1, eccentricity2, eccentricity3;
	*/
	
};

