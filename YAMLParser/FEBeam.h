#pragma once

#include <map>
#include "yaml-cpp/yaml.h"
#include "FETypes.h"
#include "GenericFE.h"
#include "Identifiable.h"
#include "GenericCrossSection.h"

class FEIsoMaterial; // Hvorfor må denne forward deklareres?
class FEBeam : public Identifiable, GenericFE
{
public:
	FEBeam(YAML::Node yamlNode);
	FEBeam(int id, FENode* node1, FENode* node2, FEIsoMaterial* mat, GenericCrossSection* crossSection);
	~FEBeam();

	Identifiable::Type getType();
	virtual std::string getTypeAsString() override;
	bool setMandatoryValues(YAML::Node& yamlNode);
	void setOptionalValues(YAML::Node& yamlNode);
	bool setNodes(YAML::Node& yamlNode);
	void printAttributes();

	void printAttributes2();

	int node1, node2, material, geoID, vecID, eccentricity1, eccentricity2;

	std::map<std::string, Identifiable> memberElements;

	const FENode *pNode1, *pNode2;
	const FEIsoMaterial *pMaterial;
	const GenericCrossSection *pCrossSection;
};

