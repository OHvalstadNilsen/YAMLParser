#pragma once

#include "yaml-cpp/yaml.h"
#include "FETypes.h"

class FETrishell
{
public:
	FETrishell(YAML::Node yamlNode);
	~FETrishell();

	bool setMandatoryValues(YAML::Node yamlNode);
	void setOptionalValues(YAML::Node yamlNode);
	void PrintTrishell();

	int id, node1, node2, node3, material, geoID, coordID;
	int eccentricity1, eccentricity2, eccentricity3;
	
	/*TODO: Implement with instances of FE classes, as shown beneath:

	FENode node1, node2, node3;
	FEMaterial material;
	FEEccentricity eccentricity1, eccentricity2, eccentricity3;
	*/
	
};

