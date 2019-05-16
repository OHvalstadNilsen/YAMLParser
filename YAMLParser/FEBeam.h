#pragma once

#include <map>
#include "yaml-cpp/yaml.h"
#include "FETypes.h"
#include "GenericFE.h"
#include "Identifiable.h"
#include "GenericCrossSection.h"

//Forward declarations
class FEIsoMaterial;
class FEEccentricity;

class FEBeam : public Identifiable, GenericFE
{
public:
	FEBeam(YAML::Node yamlNode);
	FEBeam(int id, FENode* node1, FENode* node2, FEIsoMaterial* mat, 
		GenericCrossSection* crossSection, FEEccentricity* ecc1, FEEccentricity* ecc2, FECoordSys* rotID);
	~FEBeam();

	Identifiable::Type getType();
	virtual std::string getTypeAsString() override;
	bool setMandatoryValues(YAML::Node& yamlNode);
	void setOptionalValues(YAML::Node& yamlNode);
	bool setNodes(YAML::Node& yamlNode);
	void printAttributes();

	//int node1, node2, material, geoID, vecID, eccentricity1, eccentricity2;

	std::map<std::string, Identifiable> memberElements;

	const FENode *pNode1, *pNode2;
	const FEIsoMaterial *pMaterial;
	const GenericCrossSection *pCrossSection;
	const FEEccentricity *pEcc1, *pEcc2;
	const FECoordSys *pCoordSys;
};

